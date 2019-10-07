#include "ros/ros.h"
#include "std_msgs/Int8.h"
#include "geometry_msgs/Twist.h"
/**
 * This tutorial demonstrates the use of timer callbacks.


		geometry_msgs::Twist msg1;
		msg1.linear.x = 0.0;
		msg1.linear.y = 0.0;
		msg1.linear.z = 0.0;
		msg1.angular.x = 0.0;
		msg1.angular.y = 0.0;
		msg1.angular.z = 1.0;

		ros::Duration(2.35).sleep();		//Taken time in one rotation
 */

ros::Publisher vel_pub;
void test(float x)
{
	printf("turning robot...\n");
	geometry_msgs::Twist msg1;
	msg1.linear.x = 0.0;
	msg1.linear.y = 0.0;
	msg1.linear.z = 0.0;
	msg1.angular.x = 0.0;
	msg1.angular.y = 0.0;
	msg1.angular.z = 1.0;
	vel_pub.publish(msg1);
	ros::Duration(x).sleep();

	msg1.linear.x = 0.5;
	msg1.linear.y = 0.0;
	msg1.linear.z = 0.0;
	msg1.angular.x = 0.0;
	msg1.angular.y = 0.0;
	msg1.angular.z = 0.0;
	vel_pub.publish(msg1);

	printf("Exiting\n");
}

void chatterCallback(const std_msgs::Int8::ConstPtr& msg)
{
	ROS_INFO("chatterCallBack::  Requested angle: %d", msg->data);
	float f = (2.36/360)*msg->data;
	test(f);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "timer");
  ros::NodeHandle p;
  vel_pub = p.advertise<geometry_msgs::Twist>("cmd_vel",1000);
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("chatter", 1000, chatterCallback);
  ros::spin();
  return 0;
}
