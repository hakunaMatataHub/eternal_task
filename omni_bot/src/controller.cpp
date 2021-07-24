#include <controlNode.h>	

int main(int argc, char** argv)
{

	ros::init(argc, argv, "controlNode");

    //std::cout<<"i am here8"<<std::endl;

	Controller controller1;

	//std::cout<<"i am here9"<<std::endl;

	controller1.mainLoop();

	return 0;
}