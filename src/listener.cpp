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
