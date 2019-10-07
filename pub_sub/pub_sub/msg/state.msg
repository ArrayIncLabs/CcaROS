# A representation of state of robot in terms of its direction, relative position of obstacles(angle), and its state(safe of close)

int8 state			#state of the robot (safe, close or unsafe)
int8 obstacle_angle			#angle of obstacle in which it is located.
#------------------------------------------------------------------------------
float64 goal_x			#position of the goal.
float64 goal_y

#------------------------------------------------------------------------------
float64 robo_x			#position of the robot.
float64 robo_y

String robo_nav_direction	#direction of the robot in which it is moving
