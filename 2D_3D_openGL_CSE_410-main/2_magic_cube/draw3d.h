#ifndef _draw3d_header_
#define _draw3d_header_

#include<GL/glut.h>
#include<iostream>
#include<cmath>
#include <vector>
#include "point3d.h"
#include "camera.h"
#include "config.h"

using namespace std;

void drawLine(point3d a, point3d b) {
    glBegin(GL_LINES);
    {
        glVertex3f(a.x, a.y, a.z);
        glVertex3f(b.x, b.y, b.z);
    }
    glEnd();
}

void drawTriangle(point3d a, point3d b, point3d c) {
    glBegin(GL_TRIANGLES);
    {
        glVertex3f(a.x, a.y, a.z);
        glVertex3f(b.x, b.y, b.z);
        glVertex3f(c.x, c.y, c.z);
    }
    glEnd();
}

void drawBasicTriangle() {
    GLfloat scaleFactor = currentTriangleScale*1.0/SCALE_SUBDIVISION;
    // (1/3 , 1/3, 1/3 ) -> (1, 0, 0) in SUBDIVISION STEPS
    GLfloat a = CENTRE_OF_MASS + ((1.0-CENTRE_OF_MASS)*scaleFactor);
    GLfloat b = CENTRE_OF_MASS + ((0.0-CENTRE_OF_MASS)*scaleFactor);
    // printf("%f %f %f\n", scaleFactor, a ,b);
    drawTriangle(point3d(a, b, b), point3d(b, a, b), point3d(b, b, a));
}

void drawQuad(point3d a, point3d b, point3d c, point3d d) {
    glBegin(GL_QUADS);
    {
        glVertex3f(a.x, a.y, a.z);
        glVertex3f(b.x, b.y, b.z);
        glVertex3f(c.x, c.y, c.z);
        glVertex3f(d.x, d.y, d.z);
    }
    glEnd();
}

void drawAxes() {
    glColor3f(1, 0, 0);
    drawLine(point3d(0, 0, 0), point3d(2, 0, 0));
    glColor3f(0, 1, 0);
    drawLine(point3d(0, 0, 0), point3d(0, 2, 0));
    glColor3f(0, 0, 1);
    drawLine(point3d(0, 0, 0), point3d(0, 0, 2));
}

vector<vector<point3d> > generateSphereFace(int subdivision) {
    int points = pow(2, subdivision) + 1;
    vector<vector<point3d> > vertices;
    vertices.resize(points);
    for(int i=0;i<points;i++) {
        vertices[i].resize(points);
    }
    GLfloat n1[3];
    GLfloat n2[3];
    GLfloat v[3];
    GLfloat longitudinal;
    GLfloat latitudinal;

    for(int i=0;i<points;i++) {
        latitudinal = (PI/180.0) * (45.0 - 90.0*i/(points-1.0));
        n2[0] = -sin(latitudinal);
        n2[1] = cos(latitudinal);
        n2[2] = 0.0;

        for(int j=0;j<points;j++) {
            longitudinal = (PI/180.0) * (-45.0 + 90.0*j/(points-1.0));
            n1[0] = -sin(longitudinal);
            n1[1] = 0.0;
            n1[2] = -cos(longitudinal);

            // cross product
            v[0] = n1[1]*n2[2] - n1[2]*n2[1];
            v[1] = n1[2]*n2[0] - n1[0]*n2[2];
            v[2] = n1[0]*n2[1] - n1[1]*n2[0];

            GLfloat normalizingFactor = sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
            for(int k=0;k<3;k++) {
                v[k] /= normalizingFactor;
            }
            vertices[i][j] = point3d(v[0], v[1], v[2]);
        }
    }
    return vertices;
}

void drawCubeSphereFace(GLfloat radius) {
    vector<vector<point3d> > vertices = generateSphereFace(SPHERE_SUBDIVISION);
    int sz = vertices.size();
    glPushMatrix();
        glScalef(radius, radius, radius);
        for(int i=0;i<sz-1;i++) {
            for(int j=0;j<sz-1;j++) {
                drawQuad(vertices[i][j], vertices[i+1][j], vertices[i+1][j+1], vertices[i][j+1]);
            }
        }
    glPopMatrix();
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