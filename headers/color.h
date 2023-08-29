#ifndef _color_header_
#define _color_header_

#include <GL/glut.h>
#include <iostream>

using namespace std;

// color should be in between 0-1
class Color {

    public: 

        GLfloat r;
        GLfloat g;
        GLfloat b;

        Color() {
            r = g = b = 1.0f;
        }

        Color(GLfloat red, GLfloat green, GLfloat blue) {
            r = red;
            g = green;
            b = blue;
        }

        void print() {
            cout << "(" << r << "," << g << "," << b << ")\n";
        }
        
};

#endif