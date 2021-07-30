#include <controlNode.h>
#include <iostream>
#include <fstream>
#include <math.h>

Controller::Controller()
{
	loadParams();
	setAngle = {0,0,0,0};
	setDistance = {0,0,0,0};
	sensorMsgs_sub = nh.subscribe("sensorMsgs",1,&Controller::sensorMsgs_callback, this);
	angle =0;
	direction1= "cloackwise";
	direction2 = "forward";
	outputready = false;



}

void Controller::sensorMsgs_callback(const omni_bot::sensorMsg::ConstPtr& msg)
{
	s1 = msg->s1;
	s2 = msg->s2;

	std::cout<<"recieved" <<s1<<"  "<<s2<< std::endl;

	angle = asin(abs(s1-s2)/dist_s1_s2);
	if(s1>s2)
		direction1 ="clockwise";
	if(s2>s1)
		direction1 = "counterclockwise";
	double pulse = (((dist_s1_s2*0.5)*angle)/(3.14*wheelD))*ppr;

	if(s1>s2)
	{
		setAngle[0] = -(int)pulse;
		setAngle[1] = -(int)pulse;
		setAngle[2] = -(int)pulse;
		setAngle[3] = -(int)pulse;
	}
	

	if(s2>s1)
	{
		setAngle[0] = (int)pulse;
		setAngle[1] = (int)pulse;
		setAngle[2] = (int)pulse;
		setAngle[3] = (int)pulse;
	}

  double dist2Wall = std::min(s1,s2) + (dist_s1_s2*0.5)*sin(angle) + (dist_m1_m2*0.5)*cos(angle);
  if(dist2Wall>30)
  {
    double pulse = abs(((dist2Wall-30)/wheelD)*2000);
    setDistance[0] =0;
    setDistance[1] =0;
    setDistance[2] = -(int)pulse;
    setDistance[3] = (int)pulse;
    direction2 = "forward";
  }

  if(dist2Wall<=30)
  {
    double pulse = abs(((dist2Wall-30)/(3.14*wheelD))*2000);
    setDistance[0] =0;
    setDistance[1] =0;
    setDistance[2] = (int)pulse;
    setDistance[3] = -(int)pulse;
    direction2 ="backward";
  }
  
  outputready = true;

}

void Controller::loadParams()
{
  nh.getParam("/dist_s1_s2", dist_s1_s2);
  nh.getParam("/dist_m1_m2", dist_m1_m2);
  nh.getParam("/dist_m3_m4", dist_m3_m4);
  nh.getParam("/ppr", ppr);
  nh.getParam("/emulate", emulate);
  nh.getParam("/wheelD", wheelD);
}

void Controller::mainLoop()
{

  ros::Rate loop_rate(100);

  std::ofstream myfile;
  myfile.open("/home/hakunamatata/eternal_ws/src/omni_bot/output.txt");

  while(ros::ok()) 
  {
    
    
    if(outputready)
    {
    	std::cout<<"recieved sensor values"<< "\n"<<std::endl;
    	outputready = false;

    	angle = (angle/(3.14))*180;
    	//ros::Duration(5.0).sleep() ;

    	std::cout<< angle << "," << setAngle[0] << "," << setAngle[1] << "," << setAngle[2] << "," << setAngle[3] << "," << direction1 << "," << setDistance[0] << "," << setDistance[1] << "," << setDistance[2] << "," << setDistance[3] << "," << direction2<< "\n"<<std::endl;
    	
    	myfile<< angle << "," << setAngle[0] << "," << setAngle[1] << "," << setAngle[2] << "," << setAngle[3] << "," << direction1 << "," << setDistance[0] << "," << setDistance[1] << "," << setDistance[2] << "," << setDistance[3] << "," << direction2<< "\n";
    }
    
    

    loop_rate.sleep();
    ros::spinOnce();
  	
  }

  myfile.close();
}