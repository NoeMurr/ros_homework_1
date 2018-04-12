#include <ros/ros.h>
#include <std_msgs/Char.h>
#include <iostream>


int main(int argc, char **argv){
	ROS_INFO("I'm key_reader_node");	

	ros::init(argc, argv, "key_reader_node");

	ros::NodeHandle nodeHandler;

	auto publisher = nodeHandler.advertise<std_msgs::Char>("commands", 1000);

	char choice = '\0';
	do {
		std::cout << "what part of message do you want to see?\n";
		std::cout << "\ta -> all message\n\tn -> name\n\te -> age\n";
		std::cout << "\tc -> course\n> " << std::flush;

		std::cin >> choice;

		switch (choice) {
		case 'a':
		case 'n':
		case 'e':
		case 'c': {
			std_msgs::Char msg;
			msg.data = choice;
			publisher.publish(msg);
			break;
		}
		case 'q': break;
		default:
			std::cerr << "UNKNOWN CHOICE!!!" << std::endl;
		}
	} while (choice != 'q');
}
