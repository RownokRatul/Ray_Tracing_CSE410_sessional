#ifndef _point_light_header_
#define _point_light_header_

#include <GL/glut.h>
#include "../../1805019_vector/1805019_point3d.h"
#include "../../1805019_color.h"

class PointLight {

    public:

        Point3d position;
        Color color;
        GLfloat falloff;

        PointLight(Point3d a, Color c, GLfloat fall) {
            position = a;
            color = c;
            falloff = fall;
        }


        void draw() {
            glPushMatrix();
            {
                glTranslatef(position.x, position.y, position.z);
                glColor3f(color.r, color.g, color.b);
                glutSolidSphere(5, 10, 10);
            }
            glPopMatrix();
        }

};


#endif
