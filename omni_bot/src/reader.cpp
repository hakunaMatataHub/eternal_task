#include <readNode.h>	

int main(int argc, char** argv)
{

	ros::init(argc, argv, "readNode");

    //std::cout<<"i am here8"<<std::endl;

	Parser parser1;

	//std::cout<<"i am here9"<<std::endl;

	parser1.mainLoop();

	return 0;
}