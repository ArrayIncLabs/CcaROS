#include "ros/ros.h"
#include "std_msgs/String.h"
#include <tf/transform_listener.h>
#include "geometry_msgs/Point.h"
#include<iostream>
#include<fstream>

int main(int argc, char **argv)
{
	ros::init(argc, argv, "robo_pos");
	ros::NodeHandle n;
	ros::Publisher pub = n.advertise<geometry_msgs::Point>("robo_pos", 1000);
	tf::TransformListener listener;
	ros::Rate rate(1);
	geometry_msgs::Point pos;
	while(n.ok())
	{
		tf::StampedTransform transform;
		try{
			listener.lookupTransform("/map", "/base_link", ros::Time(0), transform);
			pos.x=transform.getOrigin().x();
			pos.y=transform.getOrigin().y();
			pub.publish(pos);
		}
		catch(tf::TransformException ex){
			ROS_ERROR("Exception in robo_pos: %s", ex.what());		
		}
		ros::spinOnce();
		rate.sleep();
	}
	ROS_ERROR("Closing robo_pos");
	return 0;

}


/*
cr-lab-tu@crlabtu-HP-Z800-Workstation:~$ rosrun tf tf_echo /map /base_link
At time 1416300476.280
- Translation: [0.000, 0.000, 0.000]
- Rotation: in Quaternion [0.000, 0.000, 0.000, 1.000]
            in RPY [0.000, -0.000, 0.000]




*/
