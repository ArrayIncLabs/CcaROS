#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include "std_msgs/Int8.h"
#include "geometry_msgs/Twist.h"

ros::Publisher vel_pub;
int t=0,f=1;
void turnRobot()
{
	if(t==1)
	{
		geometry_msgs::Twist msg1;
		msg1.linear.x = 0.5;
		msg1.linear.y = 0.0;
		msg1.linear.z = 0.0;
		msg1.angular.x = 0.0;
		msg1.angular.y = 0.0;
		msg1.angular.z = -1.5;
		vel_pub.publish(msg1);
	}
	else if(t==-1)
	{
		geometry_msgs::Twist msg1;
		msg1.linear.x = 0.5;
		msg1.linear.y = 0.0;
		msg1.linear.z = 0.0;
		msg1.angular.x = 0.0;
		msg1.angular.y = 0.0;
		msg1.angular.z = 1.5;
		vel_pub.publish(msg1);
	}
}

void negotiatorCallback(const geometry_msgs::Twist::ConstPtr& msg)
{
	if(f==0){
		vel_pub.publish(msg);
	}

}


void switcherCallback(const std_msgs::Int8::ConstPtr& msg)
{
	if(msg->data==0){
		f=0;
	}
	else{
		f=1;
		t=msg->data;
		turnRobot();
	}
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "switcher");
    ros::NodeHandle p;
    vel_pub = p.advertise<geometry_msgs::Twist>("cmd_vel",1000);
    ros::NodeHandle n;
    ros::Subscriber sub = n.subscribe<std_msgs::Int8>("robotState", 1000, switcherCallback);
    ros::NodeHandle vel_sub;
    ros::Subscriber tele_cmd_vel_sub = vel_sub.subscribe<geometry_msgs::Twist>("tele_cmd_vel", 1000, negotiatorCallback);
    ros::spin();
    return 0;
}

