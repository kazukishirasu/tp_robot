cmake_minimum_required(VERSION 3.0.2)
project(tp_robot)

find_package(catkin REQUIRED COMPONENTS
    roscpp
    roslib
    geometry_msgs
    waypoint_manager_msgs
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES tp_robot
#  CATKIN_DEPENDS other_catkin_pkg
#  DEPENDS system_lib
)

include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(tp_robot_node src/tp_robot_node.cpp)

target_link_libraries(tp_robot_node yaml-cpp ${catkin_LIBRARIES})