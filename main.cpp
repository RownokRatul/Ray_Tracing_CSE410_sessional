#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <string>
#include "headers/config.h"
#include "headers/draw3d/axes.h"
#include "headers/draw3d/basicShapes.h"
#include "headers/camera/cameraMovementHandler.h"
#include "headers/parser.h"

using namespace  std;


void drawScene();


void gl_init(int vargc, char* vargv[]) {
    glutInit(&vargc, vargv);
    glutInitWindowSize(768, 768);
    glutInitWindowPosition(100, 100);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("ray tracing");
    glClearColor(0, 0, 0, 1);
    glEnable(GL_DEPTH_TEST);
}


void reshapeListener(GLsizei width, GLsizei height) {
    if(height == 0) {
        height = 1;
    }
    GLfloat aspect = (GLfloat)width / (GLfloat)height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fovy, aspect, near_plane, far_plane);
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(camera.eye.x, camera.eye.y, camera.eye.z,
             camera.centre.x, camera.centre.y, camera.centre.z,
             camera.up.x, camera.up.y, camera.up.z);
    
    // glRotatef(90.0f, 1, 0, 0);
    // glRotatef(180.0f, 0, 1, 0);
    // glRotatef(-90.0f, 0, 0, 1);

    drawScene();

    glutSwapBuffers();
}


void idle() {

}


void drawScene() {
    drawAxes();
    for (Object* obj : objects) {
        obj->draw();
    }
    for (PointLight light : pointLights) {
        light.draw();
    }
    for (SpotLight light : spotLights) {
        light.draw();
    }
}


int main(int argc, char* argv[]) {
    gl_init(argc, argv);

    readDescriptionFile("description.txt");
    glutDisplayFunc(display);
    glutReshapeFunc(reshapeListener);
    glutSpecialFunc(specialKeyListener);
    glutKeyboardFunc(usualKeyListener);
    // glutIdleFunc(idle);
    glutMainLoop();

    return 0;
}