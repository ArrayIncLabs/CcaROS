#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include "pub_sub/state.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Point.h"
#include "geometry_msgs/PoseStamped.h"
#include <tf/transform_listener.h>
#include "std_msgs/Int8.h"
#include "std_msgs/Char.h"

ros::Publisher state_pub;
int st, an;
float gx, gy;
float rx, ry;
float sl;
float odl, odr;
char dir;

void msg_publisher()
{
	std_msgs::Int8 nav;
	if(st==1)
	{
		if(an<=60)
		{
			nav.data=1;
		}
		else if(an>=121)
		{
			nav.data=-1;
		}
		else
		{
			if(dir=='e')
			{
				if(ry<=0.0f)
				{
					nav.data = -1;
				}
				else
				{
					nav.data = 1;
				}
			}
			if(dir=='w')
			{
				if(ry<=0.0f)
				{
					nav.data = 1;
				}
				else
				{
					nav.data = -1;
				}
			}
			if(dir=='n')
			{
				if(rx>=0.0f)
				{
					nav.data = 1;
				}
				else
				{
					nav.data = -1;
				}
			}
			if(dir=='s')
			{
				if(rx>=0.0f)
				{
					nav.data = -1;
				}
				else
				{
					nav.data = 1;
				}
			}
		}
	}
	else
	{
		nav.data=0;
	}
	if(nav.data == 1 && odr<1.25f)
	{
		nav.data = -1;
	}
	if(nav.data == -1 && odl<1.25f)
	{
		nav.data = 1;
	}
	state_pub.publish(nav);
}

void rposCallback(const geometry_msgs::Point::ConstPtr& msg)
{
	rx = msg->x;
	ry = msg->y;
	msg_publisher();
}

void rdirCallback(const std_msgs::Char::ConstPtr& msg)
{
	dir = msg->data;
}

void goalCallback(const geometry_msgs::PoseStamped::ConstPtr& msg)
{
	gx = msg->pose.position.x;
	gy = msg->pose.position.y;
	msg_publisher();
}
void obstaclesCallback(const sensor_msgs::LaserScan::ConstPtr& msg)
{
    st = 0;
    an = 0;
    odl = 0.0f;
    odr = 0.0f;
    sl=1.5f;	
    for(int i=0; i<(int)msg->ranges.size(); i++){
	if(sl>msg->ranges[i]){
		sl = (float)msg->ranges[i];
		an = i;
	}
    }		
    if(sl<1.25f){
	st = 1;
    }
    odl = (float)msg->ranges[35];
    odr = (float)msg->ranges[145];
    msg_publisher();
}


int main(int argc, char **argv)
{
    ros::init(argc, argv, "obstacles");
    rx=0.0f, ry = 0.0f, gx=0.0f, gy=0.0f;
    ros::NodeHandle p;
    state_pub = p.advertise<std_msgs::Int8>("robotState",1000);
    ros::NodeHandle n;
    ros::Subscriber sub = n.subscribe<sensor_msgs::LaserScan>("scan", 1000, obstaclesCallback);
    ros::NodeHandle n1;
    ros::Subscriber sub_goal = n1.subscribe<geometry_msgs::PoseStamped>("move_base_simple/goal", 1000, goalCallback);
    ros::NodeHandle n2;
    ros::Subscriber sub_rpos = n2.subscribe<geometry_msgs::Point>("robo_pos", 1000, rposCallback);
    ros::NodeHandle n3;
    ros::Subscriber sub_rdir = n3.subscribe<std_msgs::Char>("robo_dir", 1000, rdirCallback);
    ros::spin();
    return 0;
}



