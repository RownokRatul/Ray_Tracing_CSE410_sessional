#ifndef _plane_header_
#define _plane_header_

#include <GL/glut.h>
#include <iostream>
#include "../1805019_vector/1805019_point3d.h"
#include "../1805019_rayTracing/1805019_ray.h"
#include "../1805019_vector/1805019_vectorUtil.h"

using namespace std;


class Plane {

    public: 

        // a normal is given and D value is given
        Point3d n;
        GLfloat D;
        

        Plane(Point3d n, GLfloat D) {
            this->n = n;
            this->D = D;
        }

        Plane(Point3d p1, Point3d p2, Point3d p3) {
            Point3d v1 = subtractVector(p2, p1);
            Point3d v2 = subtractVector(p3, p1);
            this->n = normalize(cross_product(v1, v2));
            this->D = dot_product(this->n, p1);
        }

        Plane(vector<Point3d> face) {
            Point3d v1 = subtractVector(face[1], face[0]);
            Point3d v2 = subtractVector(face[2], face[0]);
            this->n = normalize(cross_product(v1, v2));
            this->D = dot_product(this->n, face[0]);
        }

        GLfloat intersect(Ray ray) {
            GLfloat denom = dot_product(n, ray.direction);
            if(denom == 0) {
                return -1.0f;
            }
            GLfloat t = (D - dot_product(n, ray.origin)) / denom;
            return t;
        }

        Point3d getNormal() {
            return n;
        }

};


#endif