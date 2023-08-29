#ifndef _VECTOR_HEADER_
#define _VECTOR_HEADER_

#include<iostream>
#include<cstdio>
#include<cmath>
#include "config.h"
#include "camera.h"
#include "point3d.h"

using namespace std;

point3d normalize(point3d k) {
    GLfloat l = sqrt(k.x*k.x + k.y*k.y + k.z*k.z);
    return point3d(k.x/l, k.y/l, k.z/l);
}

point3d scaleVector(point3d v, GLfloat k) {
    return point3d(v.x*k, v.y*k, v.z*k);
}

point3d cross_product(point3d a, point3d b) {
    point3d c;
    // printf("%f %f %f\n%f %f %f\n", a.x, a.y, a.z, b.x, b.y, b.z);
    c.x = a.y*b.z - a.z*b.y;
    c.y = -a.x*b.z + a.z*b.x;
    c.z = a.x*b.y - a.y*b.x;
    return c;
}

GLfloat dot_product(point3d a, point3d b) {
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

point3d addVector(point3d a, point3d b) {
    return point3d(a.x+b.x, a.y+b.y, a.z+b.z);
}

point3d Rodrigues_formula(point3d v, point3d k, GLfloat theta) {
    point3d v_rot;
    point3d normalized_k = normalize(k);
    point3d p1 = scaleVector(v, cos(theta));
    point3d p2 = scaleVector(cross_product(normalized_k, v), sin(theta));
    point3d p3 = scaleVector(normalized_k, dot_product(normalized_k, v)*(1-cos(theta)));
    v_rot = addVector(p1, p2);
    v_rot = addVector(v_rot, p3);
    return v_rot;
}

#endif