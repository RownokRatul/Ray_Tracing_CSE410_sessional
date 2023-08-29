#ifndef _2Dpendulum_header_
#define _2Dpendulum_header_

#include<GL/glut.h>
#include<iostream>
#include<math.h>
#include<ctime>
#include "point.h"
#include "draw.h"
#include "config.h"

using namespace std;

class SecondPendulum {

    public:

        GLfloat w;
        GLfloat T; 
        GLfloat L;
        GLfloat A;
        GLfloat t;
        GLfloat phi;
        GLfloat theta;

        SecondPendulum(GLfloat amp, GLfloat phase) {
            w = 0;
            T = 2.0;
            L = g/(PI*PI);
            A = amp;
            t = 0;
            this->phi = phase;
            theta = 0;
        }

        point bobPosition(GLfloat time) {
            theta = A * sin(2*time + phi);
            return point(L*sin(theta)/pendulum_length_scale, -L*cos(theta)/pendulum_length_scale);
        }

        void drawBob() {
            t += (PI/100)/2;
            // cout << t << endl;
            point bob = bobPosition(t);
            // cout << bob.x << " " << bob.y << "\n";
            drawLine(point(0, 0), bob);
            glPushMatrix();
            {
                drawFilledCircle(0.02, 10);
                glTranslatef(bob.x, bob.y, 0);
                drawFilledCircle(pendulum_bob_radius, steps_to_draw);
            }
            glPopMatrix();
        }

};


#endif