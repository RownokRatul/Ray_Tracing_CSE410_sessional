#ifndef _VECTOR_HEADER_
#define _VECTOR_HEADER_

#include <iostream>
#include <cstdio>
#include <cmath>
#include "../config.h"
#include "../camera/camera.h"
#include "point3d.h"

using namespace std;


Point3d normalize(Point3d k) {
    GLfloat l = sqrt(k.x*k.x + k.y*k.y + k.z*k.z);
    return Point3d(k.x/l, k.y/l, k.z/l);
}

Point3d scaleVector(Point3d v, GLfloat k) {
    return Point3d(v.x*k, v.y*k, v.z*k);
}

Point3d cross_product(Point3d a, Point3d b) {
    Point3d c;
    c.x = a.y*b.z - a.z*b.y;
    c.y = -a.x*b.z + a.z*b.x;
    c.z = a.x*b.y - a.y*b.x;
    return c;
}

GLfloat dot_product(Point3d a, Point3d b) {
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

Point3d addVector(Point3d a, Point3d b) {
    return Point3d(a.x+b.x, a.y+b.y, a.z+b.z);
}

Point3d subtractVector(Point3d a, Point3d b) {
    return Point3d(a.x-b.x, a.y-b.y, a.z-b.z);
}

Point3d Rodrigues_formula(Point3d v, Point3d k, GLfloat theta) {
    Point3d v_rot;
    Point3d normalized_k = normalize(k);
    Point3d p1 = scaleVector(v, cos(theta));
    Point3d p2 = scaleVector(cross_product(normalized_k, v), sin(theta));
    Point3d p3 = scaleVector(normalized_k, dot_product(normalized_k, v)*(1-cos(theta)));
    v_rot = addVector(p1, p2);
    v_rot = addVector(v_rot, p3);
    return v_rot;
}

GLfloat distanceBetweenPoints(Point3d a, Point3d b) {
    return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y) + (a.z-b.z)*(a.z-b.z));
}


#endif