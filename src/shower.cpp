#include <ros/ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Char.h>
#include <vector>
#include <sstream>
#include <stdexcept>

class Receiver {
	char m_mode = 'a';

	std::vector<std::string> tokenize(std::string s){
		using namespace std;
		istringstream iss(s);

		return {istream_iterator<string>{iss}, istream_iterator<string>{}};
	}

public:
	void commandCallback(const std_msgs::Char::ConstPtr &msg){
		switch (msg->data) {
		case 'a':
		case 'n':
		case 'e':
		case 'c':
			m_mode = msg->data;
			break;
		default:
			ROS_INFO("Unknown command '%c'", msg->data);
			m_mode = 'a';
		}
	}

	void dataCallback(const std_msgs::String::ConstPtr &msg){
		auto tokens = tokenize(msg->data);
		char idx = -1;
		switch(m_mode){
		case 'a':
			ROS_INFO("Received message: \"%s\"", msg->data.c_str());
			break;
		case 'n':
			idx = 0;
			break;
		case 'e':
			idx = 1;
			break;
		case 'c':
			idx = 2;
			break;
		}

		if (idx != -1) {
			try {
				ROS_INFO("Received data: \"%s\"", tokens.at(idx).c_str());
			} catch (std::out_of_range &e){
				ROS_INFO("BAD FORMATTED MESSEGE");
			}
		}
	}


};

int main(int argc, char **argv){
	ROS_INFO("I'm shower_node");

	ros::init(argc, argv, "shower_node");

	ros::NodeHandle nodeHandler;

	Receiver rec;

	auto dataSub = nodeHandler.subscribe("data", 1000, &Receiver::dataCallback, &rec);
	auto commandSub = nodeHandler.subscribe("commands", 1000, &Receiver::commandCallback, &rec);

	ros::spin();
}
