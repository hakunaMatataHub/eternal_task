#include <readNode.h>
#include <iostream>
#include <fstream>
#include <string>

Parser::Parser()
{
  sensorMsgs_pub = nh.advertise<omni_bot::sensorMsg>("sensorMsgs", 10);
}

void Parser::parseAndpublish(std::string& line)
{
       std::vector<std::string>   result;     

       std::stringstream          lineStream(line);
       std::string                cell;

       while(std::getline(lineStream,cell, ','))
       {
           result.push_back(cell);
       }
       // This checks for a trailing comma with no data after it.
       if (!lineStream && cell.empty())
       {
           // If there was a trailing comma then add an empty element.
           result.push_back("");
       }


	omni_bot::sensorMsg msg;
	msg.s1 = std::stod(result[0]);
	msg.s2 = std::stod(result[1]);		

	std::cout<<"sensor values are"<< msg.s1<<"  "<<msg.s2<<std::endl;
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																													

	result.clear();

	sensorMsgs_pub.publish(msg);

	//ros::Duration(5.0).sleep() ;
}

void Parser::mainLoop()
{

	  ros::Rate loop_rate(100);

	  std::string line;
	  std::ifstream myfile ("/home/hakunamatata/eternal_ws/src/omni_bot/input.txt");

	  if (myfile.is_open())
	  {

	  	
           while(ros::ok())
           {

			  while(ros::ok() && getline (myfile,line) ) 
			  {
			    ros::Duration(5.0).sleep() ;
			    
			    parseAndpublish(line);      
			    loop_rate.sleep();
			    ros::spinOnce();
			  	
			  }

			   myfile.close();

		   }

	  }

	  else std::cout << "Unable to open file"; 

	
}
