#ifndef _spot_light_header_
#define _spot_light_header_

#include <GL/glut.h>
#include "../../1805019_vector/1805019_point3d.h"
#include "../../1805019_color.h"

class SpotLight {

    public:

        Point3d position;
        Point3d look;
        Color color;
        GLfloat cutoff;
        GLfloat falloff;

        SpotLight(Point3d a, Point3d d, Color c, GLfloat cut, GLfloat fall) {
            position = a;
            look = d;
            color = c;
            cutoff = cut;
            falloff = fall;
        }

        void draw() {
            glPushMatrix();
            {
                glTranslatef(position.x, position.y, position.z);
                glColor3f(color.r, color.g, color.b);
                // glutSolidSphere(5, 10, 10);
                glutSolidCone(5, 10, 10, 10);
            }
            glPopMatrix();
        }

};


#endif
