#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include "std_msgs/Int8.h"
#include "geometry_msgs/Twist.h"
#include "geometry_msgs/Point.h"

ros::Publisher vel_pub;
int t=0,f=1;
int flag;
void turnRobot(float s)
{
	geometry_msgs::Twist msg1;
	if(t==1)
	{
		msg1.linear.x = 0.0;
		msg1.linear.y = 0.0;
		msg1.linear.z = 0.0;
		msg1.angular.x = 0.0;
		msg1.angular.y = 0.0;
		msg1.angular.z = -1.0;
		vel_pub.publish(msg1);
	}
	else if(t==-1)
	{
		msg1.linear.x = 0.0;
		msg1.linear.y = 0.0;
		msg1.linear.z = 0.0;
		msg1.angular.x = 0.0;
		msg1.angular.y = 0.0;
		msg1.angular.z = 1.0;
		vel_pub.publish(msg1);
	}
	ros::Duration(s).sleep();
	msg1.linear.x = 0.5;
	msg1.linear.y = 0.0;
	msg1.linear.z = 0.0;
	msg1.angular.x = 0.0;
	msg1.angular.y = 0.0;
	msg1.angular.z = 0.0;
	vel_pub.publish(msg1);
}

void negotiatorCallback(const geometry_msgs::Twist::ConstPtr& msg)
{
	if(f==0)
	{
		vel_pub.publish(msg);
	}

}


void switcherCallback(const geometry_msgs::Point::ConstPtr& msg)
{
	if(msg->x==0.0f){
		f=0;
	}
	else{
		flag++;
		printf("to %d\n", flag);
		f=1;
		t=(int)msg->x;
		//float tt = (2.275/360)*msg->y;
		float tt = (2.35/360)*msg->y;			//try to increase flag value by 1 ans observe
		if(flag==1)
		{
			turnRobot(tt);
		}
		else if(flag==3)
		{
			flag = 0;
		}
		//turnRobot(tt);
	}
}

int main(int argc, char **argv)
{
	flag = 0;
    ros::init(argc, argv, "switcher");
    ros::NodeHandle p;
    vel_pub = p.advertise<geometry_msgs::Twist>("cmd_vel",1000);
    ros::NodeHandle n;
    ros::Subscriber sub = n.subscribe<geometry_msgs::Point>("robotState", 0, switcherCallback);
    ros::NodeHandle vel_sub;
    ros::Subscriber tele_cmd_vel_sub = vel_sub.subscribe<geometry_msgs::Twist>("tele_cmd_vel", 1000, negotiatorCallback);
    ros::spin();
    return 0;
}

