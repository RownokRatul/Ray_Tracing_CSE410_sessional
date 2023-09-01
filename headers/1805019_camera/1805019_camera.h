#ifndef _camera_header_
#define _camera_header_

#include <iostream>
#include <GL/glut.h>
#include "../1805019_vector/1805019_point3d.h"
#include "../1805019_vector/1805019_vectorUtil.h"

using namespace std;

class Camera {

    public:

        Point3d eye;
        Point3d centre;
        Point3d up;
        Point3d right;

        Camera(Point3d e, Point3d c, Point3d u) {
            eye = e;
            centre = c;
            up = u;
            right = cross_product(eyeToCentreVector(), up);
        }

        Point3d eyeToCentreVector() {
            return Point3d(centre.x-eye.x, centre.y-eye.y, centre.z-eye.z);
        }

        Camera() {

        }

        void print() {
            cout << "eye: ";
            eye.print();
            cout << "centre: ";
            centre.print();
            cout << "up: ";
            up.print();
            cout << "right: ";
            right.print();
        }

};

#endif