#ifndef _point3d_header_
#define _point3d_header_

#include <GL/glut.h>
#include <iostream>
#include <cmath>

using namespace std;

class Point3d {
    
    public:

        GLfloat x;
        GLfloat y;
        GLfloat z;

        Point3d(GLfloat a, GLfloat b, GLfloat c) {
            x = a;
            y = b;
            z = c;
        }

        Point3d() {
            
        }

        void normalize() {
            GLfloat mag = sqrt(x*x + y*y + z*z);
            this->x /= mag;
            this->y /= mag;
            this->z /= mag;
        }

        void print() {
            cout << "(" << x << "," << y << "," << z << ")\n";
        }

};


#endif