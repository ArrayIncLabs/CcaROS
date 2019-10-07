#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include "geometry_msgs/Point.h"
#include "geometry_msgs/PoseStamped.h"
#include <visualization_msgs/Marker.h>
#include "std_msgs/Char.h"
#include "std_msgs/String.h"

ros::Publisher state_pub, marker_pub;
int st, an, la, cp, i;
float gx, gy;
float rx, ry, rxp, ryp;
float sl;
float odl, odr;
char dir;

void track_path()
{
    visualization_msgs::Marker line_strip;
    line_strip.header.frame_id = "/map";
    line_strip.header.stamp = ros::Time::now();
    line_strip.ns = "points_and_lines";
    line_strip.action = visualization_msgs::Marker::ADD;
    line_strip.pose.orientation.w = 1.0;

    line_strip.id = i++;
    line_strip.type = visualization_msgs::Marker::LINE_STRIP;

    // LINE_STRIP/LINE_LIST markers use only the x component of scale, for the line width
    line_strip.scale.x = 0.05;



    // Color of line strip
    if(st==0)
    {
    	line_strip.color.g = 1.0;
    }
    else
    {
    	line_strip.color.r = 1.0;
    }
    line_strip.color.a = 1.0;

    geometry_msgs::Point p1;
    p1.x = rx;
    p1.y = ry;
    line_strip.points.push_back(p1);

    geometry_msgs::Point p2;
    p2.x = rxp;
    p2.y = ryp;
    line_strip.points.push_back(p2);

    marker_pub.publish(line_strip);
    rxp = rx;
    ryp = ry;
}


void wall_follow()
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
	if(nav.x == 1.0f && odr<1.25f)
	{
		nav.x = -1.0f;
	}
	if(nav.x == -1.0f && odl<1.25f)
	{
		nav.x = 1.0f;
	}
	if(nav.x!=0.0f)
	{
		float angle;
		if(an>90)
		{
			angle = (float)abs(180-(an));
		}
		else
		{
			angle = (float)abs(an);
		}
		if(angle>5)
		{
			angle = angle/3;
		}
		nav.y = angle;
	}
	state_pub.publish(nav);
}

void least_angle()
{
	geometry_msgs::Point nav;
	if(st==1)
	{
		if(an<=60)
		{
			nav.x=1.0f;
		}
		else if(an>=121)
		{
			nav.x=-1.0f;
		}
		else
		{
			if(dir=='e')
			{
				if(ry<=gy)
				{
					nav.x = -1.0f;
				}
				else
				{
					nav.x = 1.0f;
				}
			}
			if(dir=='w')
			{
				if(ry<=gy)
				{
					nav.x = 1.0f;
				}
				else
				{
					nav.x = -1.0f;
				}
			}
			if(dir=='n')
			{
				if(rx>=gx)
				{
					nav.x = 1.0f;
				}
				else
				{
					nav.x = -1.0f;
				}
			}
			if(dir=='s')
			{
				if(rx>=gx)
				{
					nav.x = -1.0f;
				}
				else
				{
					nav.x = 1.0f;
				}
			}
		}
	}
	else
	{
		nav.x=0.0f;
	}
	if(nav.x == 1.0f && odr<1.25f)
	{
		nav.x = -1.0f;
	}
	if(nav.x == -1.0f && odl<1.25f)
	{
		nav.x = 1.0f;
	}
	if(nav.x!=0.0f)
	{
		float angle;
		if(an>=121)
		{
			angle = (float)abs(180-(an));
		}
		else if(an<=60)
		{
			angle = (float)abs(an);
		}
		else
		{
			if(nav.x==1.0f)
			{
				angle = (float)abs(60+(60-(an-60)));
			}
			else
			{
				angle = (float)abs(an);
			}
		}
		if(angle>5)
		{
			angle = angle/3;
		}
		nav.y = angle;
	}
	state_pub.publish(nav);
}

void center_point()
{
	geometry_msgs::Point nav;
	if(st==1)
	{
		if(an<=60)
		{
			nav.x=1.0f;
		}
		else if(an>=121)
		{
			nav.x=-1.0f;
		}
		else
		{
			if(dir=='e')
			{
				if(ry<=0.0f)
				{
					nav.x = -1.0f;
				}
				else
				{
					nav.x = 1.0f;
				}
			}
			if(dir=='w')
			{
				if(ry<=0.0f)
				{
					nav.x = 1.0f;
				}
				else
				{
					nav.x = -1.0f;
				}
			}
			if(dir=='n')
			{
				if(rx>=0.0f)
				{
					nav.x = 1.0f;
				}
				else
				{
					nav.x = -1.0f;
				}
			}
			if(dir=='s')
			{
				if(rx>=0.0f)
				{
					nav.x = -1.0f;
				}
				else
				{
					nav.x = 1.0f;
				}
			}
		}
	}
	else
	{
		nav.x=0.0f;
	}
	if(nav.x == 1.0f && odr<1.25f)
	{
		nav.x = -1.0f;
	}
	if(nav.x == -1.0f && odl<1.25f)
	{
		nav.x = 1.0f;
	}	
	if(nav.x!=0.0f)
	{
		float angle;
		if(an>=121)
		{
			angle = (float)abs(180-(an));
		}
		else if(an<=60)
		{
			angle = (float)abs(an);
		}
		else
		{
			if(nav.x==1.0f)
			{
				angle = (float)abs(60+(60-(an-60)));
			}
			else
			{
				angle = (float)abs(an);
			}
		}
		if(angle>5)
		{
			angle = angle/3;
		}
		nav.y = angle;
	}
	state_pub.publish(nav);
}
void msg_publisher()
{
	if(gx==0 && gy==0)
	{
		wall_follow();
	}
	else if(fabs(rx-gx)<=0.75f && fabs(ry-gy)<=0.75f)
	{
		geometry_msgs::Point nav;
		nav.x=10.0f;
		gx=0.0f;
		gy=0.0f;
		state_pub.publish(nav);
	}
	else
	{
		if(la==1 && cp==0)
		{
			least_angle();
		}
		else if(la==0 && cp==1)
		{
			center_point();
		}
		else
		{
			wall_follow();
		}
	}
}

void rposCallback(const geometry_msgs::Point::ConstPtr& msg)
{
	rx = msg->x;
	ry = msg->y;
	msg_publisher();
	track_path();
	
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

void navStratCallback(const geometry_msgs::Point::ConstPtr& msg)
{
	la = int(msg->x);
	cp = int(msg->y);
}

void obstaclesCallback(const sensor_msgs::LaserScan::ConstPtr& msg)
{
    st = 0;
    an = 0;
    odl = 0.0f;
    odr = 0.0f;
    sl=1.5f;	
    for(int i=10; i<(int)msg->ranges.size()-10; i++){
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
    rx=0.0f, ry = 0.0f, gx=0.0f, gy=0.0f, i=0, rxp=0.0f, ryp = 0.0f;
    ros::NodeHandle v;
    marker_pub = v.advertise<visualization_msgs::Marker>("visualization_marker", 10);
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
    ros::NodeHandle n4;
    ros::Subscriber sub_strat = n4.subscribe<geometry_msgs::Point>("nav_strategy_pub", 1000, navStratCallback);
    ros::spin();
    return 0;
}



