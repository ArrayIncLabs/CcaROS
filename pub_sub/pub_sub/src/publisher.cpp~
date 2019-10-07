#include "ros/ros.h"
#include "std_msgs/Int8.h"

int main(int argc, char **argv)
{

  ros::init(argc, argv, "talker");
  ros::NodeHandle n;
  ros::Publisher chatter_pub = n.advertise<std_msgs::Int8>("chatter", 1000);
  ros::Rate loop_rate(10);
  int x;
  while (ros::ok())
  {
    std_msgs::Int8 msg;
	printf("\nEnter value: ");
	scanf("%d", &x);
	msg.data = x;
    chatter_pub.publish(msg);
    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}
