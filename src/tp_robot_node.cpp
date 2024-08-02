#include "tp_robot/tp_robot_node.h"

namespace tp_robot {

tp_robot_node::tp_robot_node() : pnh_("~")
{
    ROS_INFO("Start tp_robot_node");
    read_yaml();
    wp_sub_ = nh_.subscribe("/waypoint_manager/waypoint", 1, &tp_robot_node::cb_wp, this);
    pose_pub_ = nh_.advertise<geometry_msgs::PoseWithCovarianceStamped>("/initialpose", 1, this);
}

tp_robot_node::~tp_robot_node()
{
}

void tp_robot_node::cb_wp(const waypoint_manager_msgs::Waypoint::ConstPtr &msg)
{
    static int index = 0;
    static std::string old_id;
    if (wp_list.size() - 1 >= index)
    {
        std::string id = wp_list[index];
        if (msg->identity == id && msg->identity != old_id)
        {
            send_pose(msg->pose);
            index++;
        }
    }
    old_id = msg->identity;
}

void tp_robot_node::read_yaml()
{
    pnh_.param("file_path", file_path_, std::string(ros::package::getPath("tp_robot") += "/config/test.yaml"));
    ROS_INFO("Load %s", file_path_.c_str());
    YAML::Node config = YAML::LoadFile(file_path_);
    for (const auto& node:config["waypoints"])
    {
        std::string id = node["waypoint_id"].as<std::string>();
        wp_list.push_back(id);
    }
}

void tp_robot_node::send_pose(geometry_msgs::Pose pose)
{
    geometry_msgs::PoseWithCovarianceStamped msg;
    msg.pose.pose = pose;
    pose_pub_.publish(msg);
    ROS_INFO("Teleport to x:%lf, y:%lf", msg.pose.pose.position.x, msg.pose.pose.position.y);
}
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "tp_robot_node");
    tp_robot::tp_robot_node tr;
    ros::spin();
    return 0;
}