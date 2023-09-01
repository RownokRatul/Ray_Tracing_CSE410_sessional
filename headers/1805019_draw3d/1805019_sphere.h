#ifndef _sphere_header_
#define _sphere_header_

#include <GL/glut.h>
#include <iostream>
#include "1805019_objects.h"

using namespace std;


class Sphere : public Object {

        vector<vector<Point3d> > generateSphereFace(int subdivision) {
            int points = pow(2, subdivision) + 1;
            vector<vector<Point3d> > vertices;
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
                    vertices[i][j] = Point3d(v[0], v[1], v[2]);
                }
            }
            return vertices;
        }

        void drawCubeSphereFace(GLfloat radius) {
            vector<vector<Point3d> > vertices = generateSphereFace(SPHERE_SUBDIVISION);
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

    public:

        Point3d centre;
        GLfloat radius;

        Sphere(Point3d c, GLfloat r, Color col, GLfloat ac, GLfloat dc, GLfloat sc, GLfloat rc, GLfloat sh) : Object(ac, dc, sc, rc, sh) {
            centre = c;
            radius = r;
            this->setColor(col);
        }

        Sphere() {
            centre = Point3d(0, 0, 0);
            radius = 0;
            this->setColor(Color(0, 0, 0));
        }

        void draw() {
            // cout << "Drawing Sphere" << endl;
            glPushMatrix();
            {
                glTranslatef(centre.x, centre.y, centre.z);
                glColor3f(color.r, color.g, color.b);
                for(int i=0;i<4;i++) {
                    drawCubeSphereFace(radius);
                    glRotatef(90, 0, 0, 1);
                }
                glRotatef(90, 0, 1, 0);
                drawCubeSphereFace(radius);
                glRotatef(180, 0, 1, 0);
                drawCubeSphereFace(radius);
            }
            glPopMatrix();
        }


        Intersection getIntersectionPoint(Ray ray) {
            GLfloat a = 1;
            GLfloat b = 2*dot_product(ray.direction, subtractVector(ray.origin, centre));
            GLfloat c = dot_product(subtractVector(ray.origin, centre), subtractVector(ray.origin, centre)) - radius*radius;
            GLfloat d = b*b - 4*a*c;
            if(d < 0) {
                return Intersection(false);
            }
            GLfloat t1 = (-b + sqrt(d))/(2*a);
            GLfloat t2 = (-b - sqrt(d))/(2*a);
            GLfloat t = min(t1, t2);
            if(t < 0) {
                t = max(t1, t2);
            }
            if(t < 0) {
                return Intersection(false);
            }
            // cout << "sphere intersected!\n";
            Point3d intersection_point = ray.getPointAtaDistance(t);
            Point3d normal = normalize(subtractVector(intersection_point, centre));
            return Intersection(intersection_point, normal, color, t, shininess, true, ambient_coefficient, diffuse_coefficient, reflection_coefficient, specular_coefficient);
        }


        void print() {
            cout << "--------Sphere--------" << endl;
            cout << "Centre: ";
            centre.print();
            cout << "Radius: " << radius << endl;
            cout << "Ambient Coefficient: " << ambient_coefficient << endl;
            cout << "Diffuse Coefficient: " << diffuse_coefficient << endl;
            cout << "Specular Coefficient: " << specular_coefficient << endl;
            cout << "Reflection Coefficient: " << reflection_coefficient << endl;
            cout << "Color: ";
            color.print();
            cout << "-------------------" << endl;
        }

};


#endif