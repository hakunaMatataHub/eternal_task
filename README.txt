# Edit path to input and output files in readernode.cpp and controllerNode.cpp respectively.

# The calculated angle made by the robot with the wall is always acute (<90). And o make it parallel to the wall the robot rotates in the direction by that acute angle magnitude about its cener. For example in reference to th figure, if s1>s2 the robot rotates in clockwise direction and if s2>s1 the robot rotates in anti-clockwise sense. The reported angle is in degrees.

assumption:: when the robot rotates anticlockwise about its center as viewed from the top view, the direction in which each of its wheel rotates(assuming no slipping omniwheel) is considered as positive.

#once the robot is made parallel with wall, using trignometry we calculate the distance from the wall. And based on present distance of the "center of the robot" from the wall is >30 or <30 we command the robot to move forward or backward respectively. (In either of the case the front and back wheels do not rotate, and the side wheels only rotate. The sign specifies correct direction of rotation of the side wheels.)
