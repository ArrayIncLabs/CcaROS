#include <stdio.h>
#include <unistd.h>
#include <termios.h>

int main()
{
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
			// New code found, check if is part of arrow key sequence
			if(skc == 65)
			{
				printf("----Up Arrow key pressed\n");
			}
			else if(skc == 66)
			{
				printf("----Down Arrow key pressed\n");
			}
			else if(skc == 67)
			{
				printf("----Right Arrow key pressed\n");
			}
			else if(skc == 68)
			{
				printf("----Left Arrow key pressed\n");
			}

		    }
    		    // Restore getchar() normal wait for new codes
		    tcsetattr(STDIN_FILENO, TCSANOW, &ots);
		}
	    }
	    else
	    {
		printf("---Escape pressed..\n");
		break;
	    }
	    // Restore getchar() normal wait for new codes
	    tcsetattr(STDIN_FILENO, TCSANOW, &original_ts);
	 }

    }

    /* restore the former settings */
    tcsetattr(STDIN_FILENO,TCSANOW,&old_tio);

    return 0;
}
