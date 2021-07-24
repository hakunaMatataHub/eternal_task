#include <ros/ros.h>
#include "omni_bot/sensorMsg.h"
#include <string>

class Controller
{
public:


	ros::NodeHandle nh;
	ros::Subscriber sensorMsgs_sub;
    
    double angle;
    std::string direction1;
    std::string direction2;

    std::vector<int> setAngle;
    std::vector<int> setDistance;
	double s1;
	double s2;
	double dist_s1_s2;
	double dist_m1_m2;
	double dist_m3_m4;
	double wheelD;
	double ppr;
	bool emulate;
	bool outputready;

	void sensorMsgs_callback(const omni_bot::sensorMsg::ConstPtr& msg);

	Controller();
	void loadParams();
	void mainLoop();


	//other helper node

};