#ifndef _camera_header_
#define _camera_header_

#include<iostream>
#include<GL/glut.h>
#include "point3d.h"
#include "vector.h"


class Camera {

    public:

        point3d eye;
        point3d centre;
        point3d up;
        point3d right;

        Camera(point3d e, point3d c, point3d u) {
            eye = e;
            centre = c;
            up = u;
            right = cross_product(eyeToCentreVector(), up);
        }

        point3d eyeToCentreVector() {
            return point3d(centre.x-eye.x, centre.y-eye.y, centre.z-eye.z);
        }

        Camera() {

        }

};

#endif