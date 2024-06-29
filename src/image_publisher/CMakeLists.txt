cmake_minimum_required(VERSION 3.0.2)
project(image_publisher)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  sensor_msgs
  cv_bridge
  image_transport
)

find_package(OpenCV REQUIRED)

catkin_package()

include_directories(
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
)

add_executable(image_publisher_node src/image_publisher.cpp)
target_link_libraries(image_publisher_node ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})