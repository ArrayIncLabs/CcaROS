#include "ros/ros.h"
#include "geometry_msgs/Point.h"
#include "geometry_msgs/PoseStamped.h"

ros::Publisher pub;
float gx, gy, rx, ry, dstgp, dstop;

float pythagorus(float a, float b)
{
	return sqrt((a*a)+(b*b));
}
void rposCallback(const geometry_msgs::Point::ConstPtr& msg)
{
	rx = msg->x;
	ry = msg->y;
	geometry_msgs::Point p;
	if(gx!=0.0f && gy!=0.0f)
        {
		float delta_la, delta_cp;
		float dx = fabs(gx-rx);
		float dy = fabs(gy-ry);
		float dstgc = pythagorus(dx, dy);
		float dstoc = pythagorus(rx, ry);
		delta_cp = fabs(dstoc-dstop);
		delta_la = fabs(dstgc-dstgp);
		if(dstgc<dstgp)
		{
			if(delta_la>delta_cp)
			{
				p.x = 1.0f;
				p.y = 0.0f;
			}
			else
			{
				p.x = 0.0f;
				p.y = 1.0f;	
			}
		}
		else if(dstgc==dstgp)
		{
			p.x = 0.0f;
			p.y = 0.0f;
		}
		else
		{
			if(delta_la>delta_cp)
			{
				p.x = 0.0f;
				p.y = 1.0f;
			}
			else
			{
				p.x = 1.0f;
				p.y = 0.0f;	
			}
		}
		dstgp = dstgc;
		dstop = dstoc;
	}
	else
	{
		p.x = 0.0f;
		p.y = 0.0f;
	}
	pub.publish(p);
}


void goalCallback (const geometry_msgs::PoseStamped::ConstPtr& msg)
{
	gx = msg->pose.position.x;
	gy = msg->pose.position.y;
	float dx = fabs(rx-gx);
	float dy = fabs(ry-gy);
	dstgp = pythagorus(dx, dy);
}



int main(int argc, char **argv)
{
    ros::init(argc, argv, "strat_pub");
    gx=0.0f, gy = 0.0f, rx=0.0f, ry = 0.0f, dstgp=0.0f;
    ros::NodeHandle n1, n2, p;
    pub = p.advertise<geometry_msgs::Point>("nav_strategy_pub",1000);
    ros::Subscriber sub = n1.subscribe<geometry_msgs::Point>("robo_pos", 1000, rposCallback); 
    ros::Subscriber sub_goal = n2.subscribe<geometry_msgs::PoseStamped>("move_base_simple/goal", 1000, goalCallback);
    ros::spin();
    return 0;
}



//==============BACKUP FOR RPOSCALLBACK=====================//
/*void rposCallback(const geometry_msgs::Point::ConstPtr& msg)
{
	rx = msg->x;
	ry = msg->y;
	geometry_msgs::Point p;
	if(gx!=0.0f && gy!=0.0f)
	{
		//==========checking for x axis====================//
		if(dxp>fabs(rx-gx))
		{
			//printf("goal-distance X is decreasing\n");
			p.x = -1.0f;
		}
		else if(dxp<fabs(rx-gx))
		{
			//printf("goal-distance X is increasing\n");
			p.x = 1.0f;
		}
		else
		{
			//printf("goal-distance X is stable\n");
			p.x = 0.0f;
		}
		//==========checking for y axis====================//
		if(dyp>fabs(ry-gy))
		{
			//printf("goal-distance y is decreasing\n");
			p.y = -1.0f;
		}
		else if(dyp<fabs(ry-gy))
		{
			//printf("goal-distance y is increasing\n");
			p.y = 1.0f;
		}
		else
		{
			//printf("goal-distance y is stable\n");
			p.y = 0.0f;
		}
	}
	else
	{
		//printf("outside else...\n");
		p.x = 0.0f;
		p.y = 0.0f;
	}
	dxp = fabs(rx-gx);
	dyp = fabs(ry-gy);
	pub.publish(p);

}*/
