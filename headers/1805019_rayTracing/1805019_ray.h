#ifndef _ray_header_
#define _ray_header_

#include <GL/glut.h>
#include <iostream>
#include "../1805019_vector/1805019_point3d.h"
#include "../1805019_vector/1805019_vectorUtil.h"

using namespace std;

class Ray {

    public:

        Point3d origin;
        Point3d direction;

        Ray(Point3d origin, Point3d direction) {
            this->origin = origin;
            this->direction = normalize(direction);
        }

        Point3d getPointAtaDistance(GLfloat t) {
            return addVector(origin, scaleVector(direction, t));
        }

        Point3d getReflectedRay(Point3d normal) {
            Point3d reflected = subtractVector(direction, scaleVector(normal, 2.0f*dot_product(direction, normal)));
            return normalize(reflected);
        }

        void print() {
            cout << "origin: ";
            origin.print();
            cout << "direction: ";
            direction.print();
        }

};


#endif