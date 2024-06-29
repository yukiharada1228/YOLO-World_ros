#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>
#include <image_transport/image_transport.h>
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

int main(int argc, char** argv)
{
    ros::init(argc, argv, "image_publisher");
    ros::NodeHandle nh("~");

    // パラメータの取得
    std::string image_dir;
    nh.param<std::string>("image_dir", image_dir, "/path/to/your/image_directory");
    std::string topic_name;
    nh.param<std::string>("topic", topic_name, "/image_topic");
    double hz;
    nh.param("hz", hz, 1.0);

    image_transport::ImageTransport it(nh);
    image_transport::Publisher pub = it.advertise(topic_name, 1);

    std::vector<std::string> image_files;
    for (fs::directory_iterator itr(image_dir); itr != fs::directory_iterator(); ++itr) {
        if (fs::is_regular_file(itr->path())) {
            image_files.push_back(itr->path().string());
        }
    }

    if (image_files.empty()) {
        ROS_ERROR("No images found in the specified directory.");
        return 1;
    }

    ros::Rate loop_rate(hz);

    size_t index = 0;
    while (ros::ok()) {
        cv::Mat image = cv::imread(image_files[index], cv::IMREAD_COLOR);
        if (!image.empty()) {
            sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", image).toImageMsg();
            pub.publish(msg);
            ROS_INFO("Published %s", image_files[index].c_str());
        } else {
            ROS_ERROR("Failed to read %s", image_files[index].c_str());
        }
        index = (index + 1) % image_files.size();
        loop_rate.sleep();
    }

    return 0;
}