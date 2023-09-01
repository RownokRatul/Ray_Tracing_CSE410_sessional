#ifndef _basic_shapes_header_
#define _basic_shapes_header_

#include <GL/glut.h>
#include <cmath>
#include "../1805019_vector/1805019_point3d.h"

using namespace std;


void drawLine(Point3d a, Point3d b) {
    glBegin(GL_LINES);
    {
        glVertex3f(a.x, a.y, a.z);
        glVertex3f(b.x, b.y, b.z);
    }
    glEnd();
}


void drawTriangle(Point3d a, Point3d b, Point3d c) {
    glBegin(GL_TRIANGLES);
    {
        glVertex3f(a.x, a.y, a.z);
        glVertex3f(b.x, b.y, b.z);
        glVertex3f(c.x, c.y, c.z);
    }
    glEnd();
}


void drawQuad(Point3d a, Point3d b, Point3d c, Point3d d) {
    glBegin(GL_QUADS);
    {
        glVertex3f(a.x, a.y, a.z);
        glVertex3f(b.x, b.y, b.z);
        glVertex3f(c.x, c.y, c.z);
        glVertex3f(d.x, d.y, d.z);
    }
    glEnd();
}


void drawPolygon(vector<Point3d> v) {
    glBegin(GL_POLYGON);
    {
        for (int i = 0; i < v.size(); i++) {
            glVertex3f(v[i].x, v[i].y, v[i].z);
        }
    }
    glEnd();
}


void drawCylinder(double height, double radius, int segments) {
    double tempx = radius, tempy = 0;
    double currx, curry;
    glBegin(GL_QUADS);
        for (int i = 1; i <= segments; i++) {
            double theta = i * 2.0 * M_PI / segments;
            currx = radius * cos(theta);
            curry = radius * sin(theta);

            GLfloat c = (2+cos(theta))/3;
            glColor3f(1, 1, 0);
            glVertex3f(currx, curry, height/2);
            glVertex3f(currx, curry, -height/2);

            glVertex3f(tempx, tempy, -height/2);
            glVertex3f(tempx, tempy, height/2);

            tempx = currx;
            tempy = curry;
        }
    glEnd();
}




#endif