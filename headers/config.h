#ifndef _config_header_
#define _config_header_

#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <memory>
#include "camera/camera.h"
#include "draw3d/objects.h"
#include "rayTracing/lightSources/pointLight.h"
#include "rayTracing/lightSources/spotLight.h"

#define PI 2*acos(0.0)
#define SCALE_SUBDIVISION 16
#define SPHERE_SUBDIVISION 6
#define CYLINDER_SUBDIVISION 100
#define EPSILON 0.0005
#define CENTRE_OF_MASS 1.0/3.0
#define DEL 0.08
#define INF 20
#define MAX_T 1000


Camera camera(Point3d(200, 0, 60), Point3d(0.1, 0.1, 60), Point3d(0, 0, 1));

GLfloat xz_plane_rotation = 0.0;

GLfloat near_plane = 0.0f;
GLfloat far_plane = 0.0f;
GLfloat fovy = 20.0f;
GLfloat aspect_ratio = 1.0f;

int level_of_recursion = 1;
int number_of_pixels = 100;
int number_of_objects = 0;

int normal_mapping_debug = 0;

// scene objects
vector<Object*> objects;
vector<PointLight> pointLights;
vector<SpotLight> spotLights;


#endif
