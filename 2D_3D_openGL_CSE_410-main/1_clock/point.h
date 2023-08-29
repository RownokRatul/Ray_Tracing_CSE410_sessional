#ifndef _point_class_header_
#define _point_class_header_

#include<GL/glut.h>

class point {

    public:

        GLfloat x;
        GLfloat y;

        point(GLfloat a, GLfloat b) {
            x = a;
            y = b;
        }

        point() {

        }
};

#endif