cmake_minimum_required(VERSION 2.8.3)
project(archie_command_node)


find_package(catkin REQUIRED COMPONENTS roscpp rospy trajectory_msgs std_msgs sensor_msgs)


catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES tst1
#  CATKIN_DEPENDS roscpp rospy std_msg trajectory_msgs
#  DEPENDS system_lib
)


include_directories(
  include ${catkin_INCLUDE_DIRS}
# include
  ${catkin_INCLUDE_DIRS}
)


add_executable(archie_command_sub
  src/archie_command_sub.cpp
)
add_dependencies(archie_command_sub ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(archie_command_sub
  ${catkin_LIBRARIES}
)

add_executable(archie_command_pub
  src/archie_command_pub.cpp
)
add_dependencies(archie_command_pub ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(archie_command_pub
  ${catkin_LIBRARIES}
)

add_executable(archie_command_pub_sub
  src/archie_command_pub_sub.cpp
)
add_dependencies(archie_command_pub_sub ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(archie_command_pub_sub
  ${catkin_LIBRARIES}
)

add_executable(arduino_test_floats_pub
  src/arduino_test_floats_pub.cpp
)
add_dependencies(arduino_test_floats_pub ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(arduino_test_floats_pub
  ${catkin_LIBRARIES}
)

add_executable(arduino_test_array_pub
  src/arduino_test_array_pub.cpp
)
add_dependencies(arduino_test_array_pub ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(arduino_test_array_pub
  ${catkin_LIBRARIES}
)