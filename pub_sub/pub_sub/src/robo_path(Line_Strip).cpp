#include <ros/ros.h>
#include <visualization_msgs/Marker.h>

#include <cmath>

int main( int argc, char** argv )
{
  ros::init(argc, argv, "points_and_lines");
  ros::NodeHandle n;
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 10);

  ros::Rate r(30);

  int i=0;
  while (ros::ok())
  {

    visualization_msgs::Marker line_strip;
    line_strip.header.frame_id = "/my_frame";
    line_strip.header.stamp = ros::Time::now();
    line_strip.ns = "points_and_lines";
    line_strip.action = visualization_msgs::Marker::ADD;
    line_strip.pose.orientation.w = 1.0;



    line_strip.id = i++;

    line_strip.type = visualization_msgs::Marker::LINE_STRIP;

    // LINE_STRIP/LINE_LIST markers use only the x component of scale, for the line width
    line_strip.scale.x = 0.1;



    // Line strip is blue
    line_strip.color.b = 1.0;
    line_strip.color.a = 1.0;

    geometry_msgs::Point p1;
    float x, y;
    printf("Enter point cordinates: \n");
    scanf("%f", &x);
    scanf("%f", &y);
    //scanf("%f", &z);
    p1.x = x;
    p1.y = y;
    line_strip.points.push_back(p1);

    geometry_msgs::Point p2;
    printf("Enter point cordinates: \n");
    scanf("%f", &x);
    scanf("%f", &y);
    //scanf("%f", &z);
    p2.x = x;
    p2.y = y;
    line_strip.points.push_back(p2);

    marker_pub.publish(line_strip);
    r.sleep();
  }
}
