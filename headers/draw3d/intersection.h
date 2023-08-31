#ifndef _intersection_header_
#define _intersection_header_

#include <GL/glut.h>
#include <iostream>
#include "../vector/point3d.h"
#include "../color.h"
#include "plane.h"

using namespace std;


class Intersection {

    public:

        Point3d point;
        Point3d normal;
        Color color;
        GLfloat t;
        bool intersects;
        GLfloat shininess;
        GLfloat ambient_coefficient;
        GLfloat diffuse_coefficient;
        GLfloat reflection_coefficient;
        GLfloat specular_coefficient;

        
        Intersection(bool f) {
            point = Point3d(0, 0, 0);
            normal = Point3d(0, 0, 0);
            color = Color(0, 0, 0);
            t = 99999999;
            intersects = f;
            shininess = 0;
            ambient_coefficient = 0;
            diffuse_coefficient = 0;
            reflection_coefficient = 0;
            specular_coefficient = 0;
        }


        Intersection(Point3d p, Point3d n, Color c, GLfloat t, GLfloat shine, bool f, GLfloat ac, GLfloat dc, GLfloat rc, GLfloat sc) {
            point = p;
            normal = n;
            color = c;
            this->t = t;
            intersects = f;
            shininess = shine;
            ambient_coefficient = ac;
            diffuse_coefficient = dc;
            reflection_coefficient = rc;
            specular_coefficient = sc;
        }

        void print() {
            cout << "Intersection: " << endl;
            cout << "Point: ";
            point.print();
            cout << "Normal: ";
            normal.print();
            cout << "Color: ";
            color.print();
            cout << "t: " << t << endl;
            cout << "Intersects: " << intersects << endl;
        }

};


#endif 