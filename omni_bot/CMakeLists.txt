cmake_minimum_required(VERSION 2.8.3)
project(omni_bot)
set(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS}")
find_package(catkin REQUIRED COMPONENTS std_msgs geometry_msgs turtlesim roscpp message_generation)


add_message_files(
  FILES
  sensorMsg.msg
)

generate_messages(
  DEPENDENCIES
  std_msgs
)

catkin_package(INCLUDE_DIRS include CATKIN_DEPENDS roscpp std_msgs geometry_msgs turtlesim message_runtime)

include_directories(include  ${catkin_INCLUDE_DIRS})



add_executable(controlNode src/controller src/controlNode.cpp)
target_link_libraries(controlNode ${catkin_LIBRARIES})
add_executable(readNode src/reader.cpp src/readNode.cpp)
target_link_libraries(readNode ${catkin_LIBRARIES})

