#include <ros/ros.h>
#include "omni_bot/sensorMsg.h"

class Parser
{
public:

	ros::NodeHandle nh;
	ros::Publisher sensorMsgs_pub;

	

	Parser();

	void parseAndpublish(std::string& line);
	void mainLoop();


	//other helper node

};