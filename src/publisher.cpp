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
