#ifndef _pyramid_header_
#define _pyramid_header_

#include <GL/glut.h>
#include <iostream>
#include <vector>
#include "objects.h"
#include "intersection.h"
#include "polygonIntersection.h"

using namespace std;


class Pyramid : public Object {

        void generateFaces() {
            vector<Point3d> base;
            GLfloat factor = width/2.0;
            base.push_back(Point3d(lowest_point.x - factor, lowest_point.y - factor, lowest_point.z));
            base.push_back(Point3d(lowest_point.x - factor, lowest_point.y + factor, lowest_point.z));
            base.push_back(Point3d(lowest_point.x + factor, lowest_point.y + factor, lowest_point.z));
            base.push_back(Point3d(lowest_point.x + factor, lowest_point.y - factor, lowest_point.z));
            faces.push_back(base);
            vector<Point3d> face1;
            face1.push_back(Point3d(lowest_point.x - factor, lowest_point.y - factor, lowest_point.z));
            face1.push_back(Point3d(lowest_point.x, lowest_point.y, lowest_point.z + height));
            face1.push_back(Point3d(lowest_point.x - factor, lowest_point.y + factor, lowest_point.z));
            faces.push_back(face1);
            vector<Point3d> face2;
            face2.push_back(Point3d(lowest_point.x - factor, lowest_point.y + factor, lowest_point.z));
            face2.push_back(Point3d(lowest_point.x, lowest_point.y, lowest_point.z + height));
            face2.push_back(Point3d(lowest_point.x + factor, lowest_point.y + factor, lowest_point.z));
            faces.push_back(face2);
            vector<Point3d> face3;
            face3.push_back(Point3d(lowest_point.x + factor, lowest_point.y + factor, lowest_point.z));
            face3.push_back(Point3d(lowest_point.x, lowest_point.y, lowest_point.z + height));
            face3.push_back(Point3d(lowest_point.x + factor, lowest_point.y - factor, lowest_point.z));
            faces.push_back(face3);
            vector<Point3d> face4;
            face4.push_back(Point3d(lowest_point.x + factor, lowest_point.y - factor, lowest_point.z));
            face4.push_back(Point3d(lowest_point.x, lowest_point.y, lowest_point.z + height));
            face4.push_back(Point3d(lowest_point.x - factor, lowest_point.y - factor, lowest_point.z));
            faces.push_back(face4);
        }

    public:

        Point3d lowest_point;
        GLfloat width;
        GLfloat height;

        vector<vector<Point3d>> faces;


        Pyramid(Point3d lp, GLfloat w, GLfloat h, Color c, GLfloat ac, GLfloat dc, GLfloat sc, GLfloat rc, GLfloat sh) : Object(ac, dc, sc ,rc, sh) {
            lowest_point = lp;
            width = w;
            height = h;
            this->setColor(c);
            generateFaces();
        }

        Pyramid() {
            lowest_point = Point3d(0, 0, 0);
            width = 0;
            height = 0;
            this->setColor(Color(0, 0, 0));
        }

        void draw() {
            // cout << "Drawing Pyramid" << endl;
            glPushMatrix();
            {
                glColor3f(color.r, color.g, color.b);
                for(vector<Point3d> face : faces) {
                    drawPolygon(face);
                }
            }
            glPopMatrix();

        }

        Intersection getIntersectionPoint(Ray ray) {
            Intersection in = Intersection(false);
            for(vector<Point3d> face : faces) {
                Intersection intersection = getIntersectionWithPolygon(face, ray, this->color, shininess, ambient_coefficient, diffuse_coefficient, reflection_coefficient, specular_coefficient);
                if(intersection.intersects && intersection.t < in.t) {
                    in = intersection;
                    // cout << "Pyramid Intersected!\n";
                }
            }
            return in;
        }


        void print() {
            cout << "--------Pyramid--------" << endl;
            cout << "Lowest Point: ";
            lowest_point.print();
            cout << "Width: " << width << endl;
            cout << "Height: " << height << endl;
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