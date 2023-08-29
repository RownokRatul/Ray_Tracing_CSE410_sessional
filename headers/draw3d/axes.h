#ifndef _axes_header_
#define _axes_header_


#include "basicShapes.h"


void drawAxes() {
    // cout << "Drawing Axes" << endl;
    glColor3f(1, 0, 0);
    drawLine(Point3d(0, 0, 0), Point3d(100, 0, 0));
    glColor3f(0, 1, 0);
    drawLine(Point3d(0, 0, 0), Point3d(0, 100, 0));
    glColor3f(0, 0, 1);
    drawLine(Point3d(0, 0, 0), Point3d(0, 0, 100));
}


#endif