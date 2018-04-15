/*
MIT License

Copyright (c) 2018 Noè Murr

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
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
		std::cout << "\tc -> course\n\tq ->quit\n> " << std::flush;

		std::cin >> choice;

		switch (choice) {
		case 'a':
		case 'n':
		case 'e':
		case 'c': {
			std::cout << "sending "<< choice << std::endl;
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
