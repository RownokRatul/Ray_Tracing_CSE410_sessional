#ifndef _polygon_header_
#define _polygon_header_

#include <GL/glut.h>
#include <vector>
#include "../vector/point3d.h"
#include "../color.h"
#include "../config.h"
#include "../vector/vectorUtil.h"


GLfloat triangle_area(Point3d a, Point3d b, Point3d c) {
    Point3d v1 = subtractVector(b, a);
    Point3d v2 = subtractVector(c, a);
    Point3d v3 = cross_product(v1, v2);
    return 0.5*sqrt(v3.x*v3.x + v3.y*v3.y + v3.z*v3.z);
}


bool is_point_inside_triangle(Point3d a, Point3d b, Point3d c, Point3d p) {
    double tot_area = triangle_area(a, b, c);
    double area1 = triangle_area(a, b, p);
    double area2 = triangle_area(a, c, p);
    double area3 = triangle_area(b, c, p);
    if(abs(tot_area - (area1 + area2 + area3)) < 0.0001) {
        return true;
    }
    return false;
}

bool is_point_inside_rectangle(Point3d a, Point3d b, Point3d c, Point3d d, Point3d p) {
    if(is_point_inside_triangle(a, b, c, p) || is_point_inside_triangle(a, d, c, p)) {
        return true;
    }
    return false;
}

bool is_point_inside_polygon(Point3d p, vector<Point3d> polygon) {
    if(polygon.size() == 3) {
        return is_point_inside_triangle(polygon[0], polygon[1], polygon[2], p);
    }
    else if(polygon.size() == 4) {
        return is_point_inside_rectangle(polygon[0], polygon[1], polygon[2], polygon[3], p);
    }
    return false;
}


Intersection getIntersectionWithPolygon(vector<Point3d> polygon, Ray ray, Color c, GLfloat shine, GLfloat ac, GLfloat dc, GLfloat rc, GLfloat sc) {
    // make sure the polygon is convex and the points are counterclockwise
    Plane plane = Plane(polygon);
    GLfloat t = plane.intersect(ray);
    if(t < 0 || t >= MAX_T) {
        return Intersection(false);
    }
    Point3d intersection_point = ray.getPointAtaDistance(t);
    if(is_point_inside_polygon(intersection_point, polygon)) {
        // cout << "Intersection with polygon" << endl;
        return Intersection(intersection_point, plane.getNormal(), c, t, shine, true, ac, dc, rc, sc);
    }
    return Intersection(false);
}


#endif