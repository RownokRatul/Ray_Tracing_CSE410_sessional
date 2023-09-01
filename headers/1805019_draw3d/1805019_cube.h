#ifndef _cube_header_
#define _cube_header_

#include <GL/glut.h>
#include "../1805019_color.h"
#include "1805019_objects.h"
#include "1805019_basicShapes.h"
#include <vector>
#include "1805019_intersection.h"
#include "1805019_polygonIntersection.h"

class Cube : public Object{

        void generateFaces() {
            // left
            vector<Point3d> face1;
            face1.push_back(bottom_lower_left);
            face1.push_back(Point3d(bottom_lower_left.x + side, bottom_lower_left.y, bottom_lower_left.z));
            face1.push_back(Point3d(bottom_lower_left.x + side, bottom_lower_left.y, bottom_lower_left.z + side));
            face1.push_back(Point3d(bottom_lower_left.x, bottom_lower_left.y, bottom_lower_left.z + side));
            faces.push_back(face1);
            // right
            vector<Point3d> face3;
            face3.push_back(Point3d(bottom_lower_left.x, bottom_lower_left.y + side, bottom_lower_left.z + side));
            face3.push_back(Point3d(bottom_lower_left.x + side, bottom_lower_left.y + side, bottom_lower_left.z + side));
            face3.push_back(Point3d(bottom_lower_left.x + side, bottom_lower_left.y + side, bottom_lower_left.z));
            face3.push_back(Point3d(bottom_lower_left.x, bottom_lower_left.y + side, bottom_lower_left.z));
            faces.push_back(face3);
            // top
            vector<Point3d> face2;
            face2.push_back(Point3d(bottom_lower_left.x, bottom_lower_left.y, bottom_lower_left.z + side));
            face2.push_back(Point3d(bottom_lower_left.x + side, bottom_lower_left.y, bottom_lower_left.z + side));
            face2.push_back(Point3d(bottom_lower_left.x + side, bottom_lower_left.y + side, bottom_lower_left.z + side));
            face2.push_back(Point3d(bottom_lower_left.x, bottom_lower_left.y + side, bottom_lower_left.z + side));
            faces.push_back(face2);
            // bottom
            vector<Point3d> face4;
            face4.push_back(Point3d(bottom_lower_left.x, bottom_lower_left.y + side, bottom_lower_left.z));
            face4.push_back(Point3d(bottom_lower_left.x + side, bottom_lower_left.y + side, bottom_lower_left.z));
            face4.push_back(Point3d(bottom_lower_left.x + side, bottom_lower_left.y, bottom_lower_left.z));
            face4.push_back(bottom_lower_left);
            faces.push_back(face4);
            // front
            vector<Point3d> face5;
            face5.push_back(bottom_lower_left);
            face5.push_back(Point3d(bottom_lower_left.x, bottom_lower_left.y + side, bottom_lower_left.z));
            face5.push_back(Point3d(bottom_lower_left.x, bottom_lower_left.y + side, bottom_lower_left.z + side));
            face5.push_back(Point3d(bottom_lower_left.x, bottom_lower_left.y, bottom_lower_left.z + side));
            faces.push_back(face5);
            // back
            vector<Point3d> face6;
            face6.push_back(Point3d(bottom_lower_left.x + side, bottom_lower_left.y, bottom_lower_left.z));
            face6.push_back(Point3d(bottom_lower_left.x + side, bottom_lower_left.y + side, bottom_lower_left.z));
            face6.push_back(Point3d(bottom_lower_left.x + side, bottom_lower_left.y + side, bottom_lower_left.z + side));
            face6.push_back(Point3d(bottom_lower_left.x + side, bottom_lower_left.y, bottom_lower_left.z + side));
            faces.push_back(face6);
        }


    public:

        Point3d bottom_lower_left;
        GLfloat side;
        vector<vector<Point3d> > faces;


        Cube(Point3d bll, GLfloat s, Color c, GLfloat ac, GLfloat dc, GLfloat sc, GLfloat rc, GLfloat sh) : Object(ac, dc, sc ,rc, sh) {
            bottom_lower_left = bll;
            side = s;
            this->setColor(c);
            generateFaces();
        }


        Cube() {
            bottom_lower_left = Point3d(0, 0, 0);
            side = 0;
            this->setColor(Color(0, 0, 0));
        }


        void draw() {
            // cout << "Drawing Cube" << endl;
            glPushMatrix();
            {
                glColor3f(color.r, color.g, color.b);
                for (vector<Point3d> face : faces) {
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
                    // cout << "Cube intersected!\n";
                }
            }
            return in;
        }


        void print() {
            cout << "--------Cube--------" << endl;
            cout << "Bottom Lower Left: ";
            bottom_lower_left.print();
            cout << "Side: " << side << endl;
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