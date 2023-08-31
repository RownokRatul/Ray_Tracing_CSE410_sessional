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

        
        Intersection(bool f) {
            point = Point3d(0, 0, 0);
            normal = Point3d(0, 0, 0);
            color = Color(0, 0, 0);
            t = 99999999;
            intersects = f;
        }


        Intersection(Point3d p, Point3d n, Color c, GLfloat t, bool f) {
            point = p;
            normal = n;
            color = c;
            this->t = t;
            intersects = f;
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