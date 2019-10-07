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
char obs;

void msg_publisher()
{
	geometry_msgs::Point nav;
	if(st==1)
	{
		if(an<=90)
		{
			nav.x=1.0f;
		}
		else
		{
			nav.x=-1.0f;
		}
	}
	else
	{
		nav.x=0.0f;
	}
	if(nav.x == 1.0f && odr<0.75f)
	{
		nav.x = -1.0f;
	}
	if(nav.x == -1.0f && odl<0.75f)
	{
		nav.x = 1.0f;
	}
	if(nav.x!=0.0f)
	{
		if(an>90)
		{
			nav.y = (float)abs(180-(an));
		}
		else
		{
			nav.y = (float)abs(an);
		}
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
    sl=1.15f;	
    for(int i=0; i<(int)msg->ranges.size(); i++){
	if(sl>msg->ranges[i]){
		sl = (float)msg->ranges[i];
		an = i;
	}
    }		
    if(sl<1.10f){
	st = 1;
    }
    if(an<91)
    {
	obs = 'l';
    }
    else
    {
	obs = 'r';
    }
    odl = (float)msg->ranges[35];
    odr = (float)msg->ranges[145];
    msg_publisher();
}


int main(int argc, char **argv)
{
    ros::init(argc, argv, "obstacles");
    rx=0.0f, ry = 0.0f, gx=0.0f, gy=0.0f, obs = 'l';
    ros::NodeHandle p;
    state_pub = p.advertise<geometry_msgs::Point>("robotState",1000);
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


/*

else
{
	if(dir=='e')
	{
		if(ry<=0.0f)
		{
			nav.x = -1;
		}
		else
		{
			nav.x = 1;
		}
	}
	if(dir=='w')
	{
		if(ry<=0.0f)
		{
			nav.x = 1;
		}
		else
		{
			nav.x = -1;
		}
	}
	if(dir=='n')
	{
		if(rx>=0.0f)
		{
			nav.x = 1;
		}
		else
		{
			nav.x = -1;
		}
	}
	if(dir=='s')
	{
		if(rx>=0.0f)
		{
			nav.v = -1;
		}
		else
		{
			nav.v = 1;
		}
	}
}

*/
