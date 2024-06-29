cmake_minimum_required(VERSION 3.0.2)
project(yolo_launch)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  sensor_msgs
  image_transport
  cv_bridge
  std_msgs
  image_view
)

catkin_package()

include_directories(
  ${catkin_INCLUDE_DIRS}
)