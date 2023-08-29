#ifndef _point3_header_
#define _point3_header_

#include<GL/glut.h>
#include<iostream>

class point3d {
    
    public:

        GLfloat x;
        GLfloat y;
        GLfloat z;

        point3d(GLfloat a, GLfloat b, GLfloat c) {
            x = a;
            y = b;
            z = c;
        }

        point3d() {
            
        }

        void normalize() {
            GLfloat mag = sqrt(x*x + y*y + z*z);
            this->x /= mag;
            this->y /= mag;
            this->z /= mag;
        }

        void print() {
            std::cout << "(" << x << "," << y << "," << z << ")\n";
        }

};


#endif