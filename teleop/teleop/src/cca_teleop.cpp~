#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include <stdio.h>
#include <unistd.h>
#include <termios.h>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "cca_teleop");
    ros::NodeHandle p;
    ros::Publisher vel_pub = p.advertise<geometry_msgs::Twist>("cmd_vel",1000);
	printf("\n\n***************************************************************\n");
	printf("\n                  Use Arrow Keys to Navigate                   \n");
	printf("\n***************************************************************\n");
	printf("\n                       Press Esc to Exit                       \n");
	printf("\n***************************************************************\n");
    int flag=0;
//    ros::Rate loop_rate(10);
    struct termios old_tio, new_tio;
    unsigned char c;

    /* get the terminal settings for stdin */
    tcgetattr(STDIN_FILENO,&old_tio);

    /* we want to keep the old setting to restore them at the end */
    new_tio=old_tio;

    /* disable canonical mode (buffered i/o) and local echo */
    new_tio.c_lflag &=(~ICANON & ~ECHO);

    /* set the new settings immediately */
    tcsetattr(STDIN_FILENO,TCSANOW,&new_tio);

    while(1)
    {
         c=getchar();
	 if(c == 27)
	 {
	    struct termios original_ts, nowait_ts;
	    unsigned int SpecialKeyCode;

	    // Configure getchar() to return immediately
	    tcgetattr(STDIN_FILENO, &original_ts);
	    nowait_ts = original_ts;
	    nowait_ts.c_lflag &= ~ISIG;
	    nowait_ts.c_cc[VMIN]  = 0;
	    nowait_ts.c_cc[VTIME] = 0;
	    tcsetattr(STDIN_FILENO, TCSANOW, &nowait_ts);


	    // to receive additional sequence codes
	    // Check if additional code is available after 27
	    if((SpecialKeyCode = getchar()) != EOF)
	    {
		// New code found, check if is part of arrow key sequence
		if(SpecialKeyCode == 91)
		{
		    // Sequence code found, now next code will inform us
		    struct termios ots, nts;
		    unsigned int skc;

		    // Configure getchar() to return immediately
		    tcgetattr(STDIN_FILENO, &ots);
		    nts = ots;
		    nts.c_lflag &= ~ISIG;
		    nts.c_cc[VMIN]  = 0;
		    nts.c_cc[VTIME] = 0;
		    tcsetattr(STDIN_FILENO, TCSANOW, &nts);
		    // to receive additional sequence codes
		    // Check if additional code is available after 91
		    if((skc = getchar()) != EOF)
		    {
			geometry_msgs::Twist nav;
			// New code found, check if is part of arrow key sequence
			if(skc == 65)
			{
				if(flag==0 || flag==1)
				{
					nav.linear.x = 0.5;
					flag = 1;
				}
				else if(flag==-1)
				{
					flag=0;
				}
			}
			else if(skc == 66)
			{
				if(flag==0 || flag==-1)
				{
					nav.linear.x = -0.5;
					flag=-1;
				}
				else if(flag==1)
				{
					flag=0;
				}
			}
			else if(skc == 67)
			{
				if(flag==0 || flag==1)
				{
					flag = 1;
					nav.linear.x = 0.5;
					nav.angular.z = -1.0;
				}
				else if(flag==-1)
				{
					nav.linear.x = -0.5;
				}
			}
			else if(skc == 68)
			{
				if(flag==0 || flag==1)
				{
					flag = 1;
					nav.linear.x = 0.5;
					nav.angular.z = 1.0;
				}
				else if(flag==-1)
				{
					nav.linear.x = -0.5;
				}
			}
			vel_pub.publish(nav);
		    }
    		    // Restore getchar() normal wait for new codes
		    tcsetattr(STDIN_FILENO, TCSANOW, &ots);
		}
	    }
	    else
	    {
		break;
	    }
	    // Restore getchar() normal wait for new codes
	    tcsetattr(STDIN_FILENO, TCSANOW, &original_ts);
	 }

    }

    /* restore the former settings */
    tcsetattr(STDIN_FILENO,TCSANOW,&old_tio);
    geometry_msgs::Twist nav;
    vel_pub.publish(nav);
    return 0;
}
