#include <ros/ros.h>
#include <visualization_msgs/Marker.h>

#include <cmath>

int main( int argc, char** argv )
{
  ros::init(argc, argv, "points_and_lines");
  ros::NodeHandle n;
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 10);

  ros::Rate r(10);
  int i=0;

  while (ros::ok())
  {

    visualization_msgs::Marker points;
    points.header.frame_id = "/my_frame";
    points.header.stamp = ros::Time::now();
    points.ns = "points_and_lines";
    points.action = visualization_msgs::Marker::ADD;
    points.pose.orientation.w = 1.0;
    points.id = i++;
    points.type = visualization_msgs::Marker::POINTS;

    // POINTS markers use x and y scale for width/height respectively
    points.scale.x = 0.2;
    points.scale.y = 0.2;


    // Points are green
    points.color.g = 1.0f;
    points.color.a = 1.0;

    //Setting the lifetime of marker
    points.lifetime = ros::Duration();

    // Create the vertices for the points and lines
    geometry_msgs::Point p;
    float x, y;
    printf("Enter point cordinates: \n");
    scanf("%f", &x);
    scanf("%f", &y);
    p.x = x;
    p.y = y;

    points.points.push_back(p);
    marker_pub.publish(points);
    r.sleep();
  }
}
