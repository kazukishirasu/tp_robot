#ifndef TP_ROBOT_NODE_H__
#define TP_ROBOT_NODE_H__

#include <ros/ros.h>
#include <ros/package.h>
#include <string>
#include <vector>
#include <yaml-cpp/yaml.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <waypoint_manager_msgs/Waypoint.h>

namespace tp_robot {

class tp_robot_node
{
public:
    tp_robot_node();
    ~tp_robot_node();
    void cb_wp(const waypoint_manager_msgs::Waypoint::ConstPtr &msg);
    void read_yaml();
    void send_pose(geometry_msgs::Pose);
private:
    ros::NodeHandle nh_;
    ros::NodeHandle pnh_;
    ros::Subscriber wp_sub_;
    ros::Publisher pose_pub_;
    std::string file_path_;
    std::vector<std::string> wp_list;
};

}
#endif