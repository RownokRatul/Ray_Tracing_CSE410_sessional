#ifndef _parser_header_
#define _parser_header_

#include <GL/glut.h>
#include <iostream>
#include "config.h"
#include "draw3d/objects.h"
#include "draw3d/checkerBoard.h"
#include "draw3d/sphere.h"
#include "draw3d/pyramid.h"
#include "draw3d/cube.h"

using namespace std;


void readSphere() {
    GLfloat x, y ,z, r;
    cin >> x >> y >> z;
    cin >> r;
    GLfloat re, g, b;
    cin >> re >> g >> b;
    GLfloat ac, dc, rc, sc, sh;
    cin >> ac >> dc >> sc >> rc >> sh;
    objects.push_back(new Sphere(Point3d(x, y, z), r, Color(re, g, b), ac, dc, sc, rc, sh));
}

void readPyramid() {
    GLfloat x, y, z;
    cin >> x >> y >> z;
    GLfloat w, h;
    cin >> w >> h;
    GLfloat r, g, b;
    cin >> r >> g >> b;
    GLfloat ac, dc, rc, sc, sh;
    cin >> ac >> dc >> sc >> rc >> sh;
    objects.push_back(new Pyramid(Point3d(x, y, z), w, h, Color(r, g, b), ac, dc, sc, rc, sh));
}

void readCube() {
    GLfloat x, y, z;
    cin >> x >> y >> z;
    GLfloat s;
    cin >> s;
    GLfloat r, g, b;
    cin >> r >> g >> b;
    GLfloat ac, dc, rc, sc, sh;
    cin >> ac >> dc >> sc >> rc >> sh;
    objects.push_back(new Cube(Point3d(x, y, z), s, Color(r, g, b), ac, dc, sc, rc, sh));
}

void readCheckerBoard() {
    GLfloat w, ac, dc, rc, sc, sh;
    cin >> w >> ac >> dc >> rc;
    objects.push_back(new CheckerBoard(w, ac, dc, rc));
}

void readLightSources() {
    int number_of_point_lights, number_of_spot_lights;
    cin >> number_of_point_lights;
    for(int i=0;i<number_of_point_lights; i++) {
        GLfloat x, y, z, fall;
        cin >> x >> y >> z >> fall;
        pointLights.push_back(PointLight(Point3d(x, y, z), Color(1, 1, 1), fall));
    }
    cin >> number_of_spot_lights;
    for(int i=0;i<number_of_spot_lights; i++) {
        GLfloat x, y, z, dx, dy, dz, cut, fall;
        cin >> x >> y >> z >> fall >> dx >> dy >> dz >> cut;
        spotLights.push_back(SpotLight(Point3d(x, y, z), Point3d(dx, dy, dz), Color(1, 1, 1), cut, fall));
    }
}


void readDescriptionFile(string s) {
    freopen(s.c_str(), "r", stdin);
    cin >> near_plane >> far_plane >> fovy >> aspect_ratio;
    cin >> level_of_recursion >> number_of_pixels;
    readCheckerBoard();
    cin >> number_of_objects;
    string type;
    for(int i=0;i<number_of_objects;i++) {
        cin >> type;
        if(type == "cube") {
            readCube();
        }
        else if(type == "sphere") {
            readSphere();
        }
        else if(type == "pyramid") {
            readPyramid();
        }
    }
    readLightSources();
    for (Object* obj : objects) {
        obj->print();
    }
}



#endif