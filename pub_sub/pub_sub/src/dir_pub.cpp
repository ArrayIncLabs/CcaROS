#include "ros/ros.h"
#include "std_msgs/Char.h"
#include "geometry_msgs/Point.h"

ros::Publisher pub;
float rx, ry, rxp, ryp;

void rdirCallback(const geometry_msgs::Point::ConstPtr& msg)
{
	rx = msg->x;
	ry = msg->y;
	if(rxp==0.0f || ryp==0.0f)
	{
		rxp = msg->x;
		ryp = msg->y;
	}
	std_msgs::Char dir;
	if(rx>rxp && ry>ryp)
	{
		if((rx-rxp)>(ry-ryp))
		{
			dir.data = 'w';
		}
		else
		{
			dir.data = 'n';
		}

	}
	else if((rx<rxp && ry<ryp))
	{
		if((rxp-rx)>(ryp-ry))
		{
			dir.data = 'e';
		}
		else
		{
			dir.data = 's';
		}
	}
	else if((rx>rxp && ry<ryp))
	{
		if((rx-rxp)>(ryp-ry))
		{
			dir.data = 'w';
		}
		else
		{
			dir.data = 's';
		}
	}
	else if((rx<rxp && ry>ryp))
	{
		if((rxp-rx)>(ry-ryp))
		{
			dir.data = 'e';
		}
		else
		{
			dir.data = 'n';
		}
	}
	else
	{
		dir.data = 'x';
	}
	rxp = rx;
	ryp = ry;
	pub.publish(dir);
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "dir_pub");
    rx=0.0f, ry = 0.0f, rxp=0.0f, ryp = 0.0f;
    ros::NodeHandle n, p;
    pub = p.advertise<std_msgs::Char>("robo_dir",1000);
    ros::Subscriber sub = n.subscribe<geometry_msgs::Point>("robo_pos", 1000, rdirCallback); 
    ros::spin();
    return 0;
}
