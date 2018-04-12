#include <ros/ros.h>
#include <std_msgs/String.h>
#include <vector>

int main(int argc, char **argv){

	std::vector<std::string> data {
		"Mirko 22 informatica",
		"Noè 23 informatica",
		"Simone 22 Bioinformatica",
		"Caterina 20 Biologia"
	};
	
	ROS_INFO("I'm publisher_node");

	ros::init(argc, argv, "publisher_node");

	ros::NodeHandle nodeHandle;

	auto publisher = nodeHandle.advertise<std_msgs::String>("data", 1000);

	ros::Rate loopRate(1); // 1 Hz the frequency is in Hz

	while(ros::ok()){
		for(const auto &s : data){
			ROS_INFO("SENDING: %s", s.c_str());
			std_msgs::String msg;
			msg.data = s;
			publisher.publish(msg);

			ros::spinOnce();
			loopRate.sleep();
		}
	}
}
