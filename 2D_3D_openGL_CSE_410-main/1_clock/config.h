#ifndef _config_header_
#define _config_header_

#include<GL/glut.h>
#include "point.h"

#define PI (2*acos(0.0))
#define g 9.81

GLfloat outer_radius = 0.45;
GLfloat inner_radius = 0.4;
int steps_to_draw = 50;
GLfloat hand_length = 0.2;
GLfloat hand_width = 0.015;
point dial_centre(0.0, 0.4);

GLfloat pendulum_amplitude = 0.3;
GLfloat pendulum_initial_phase = 0.0;
GLfloat pendulum_length_scale = 1.5;
GLfloat pendulum_bob_radius = 0.12;

#endif