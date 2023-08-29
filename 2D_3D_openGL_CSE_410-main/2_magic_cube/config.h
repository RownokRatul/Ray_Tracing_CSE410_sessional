#ifndef _config_header_
#define _config_header_

#include<GL/glut.h>
#include<iostream>
#include <cmath>
#include "camera.h"

#define PI 2*acos(0.0)
#define SCALE_SUBDIVISION 16
#define SPHERE_SUBDIVISION 6
#define CYLINDER_SUBDIVISION 100
#define EPSILON 0.0005
#define CENTRE_OF_MASS 1.0/3.0
#define DEL 0.08

Camera camera(point3d(4, 4, 4), point3d(0.1, 0.1, 0.1), point3d(0, 1, 0));

GLfloat xz_plane_rotation = 0.0;

GLfloat dihedral_angle = 70.5287794;
GLfloat sphere_base_radius = sqrt(3.0*CENTRE_OF_MASS*CENTRE_OF_MASS);

GLfloat cylinder_base_radius = sphere_base_radius;
GLfloat cylinder_base_height = sqrt(2); // (1, 0, 0) - (0, 1, 0)

int currentTriangleScale = 16;
int currentSphereScale = 16;
int currentCylinderScale = 16;


#endif
