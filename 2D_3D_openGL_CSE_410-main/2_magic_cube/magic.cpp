#include<GL/glut.h>
#include<iostream>
#include<cmath>
#include "config.h"
#include "draw3d.h"
#include "keyHandler.h"

using namespace std;


void reshapeListener(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
    // Compute aspect ratio of the new window
    if (height == 0) height = 1;                // To prevent divide by 0
    GLfloat aspect = (GLfloat)width / (GLfloat)height;

    // Set the viewport to cover the new window
    glViewport(0, 0, width, height);

    // Set the aspect ratio of the clipping area to match the viewport
    glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
    glLoadIdentity();             // Reset the projection matrix
    /*if (width >= height) {
        // aspect >= 1, set the height from -1 to 1, with larger width
        gluOrtho2D(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0);
    } else {
        // aspect < 1, set the width to -1 to 1, with larger height
        gluOrtho2D(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect);
    }*/
    // Enable perspective projection with fovy, aspect, zNear and zFar
    gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}

void idle() {

}


// let the sphere centre move from 0, 0, 0 to 1, 0, 0 unitarily.
// similarly, let the radius scale from "base_radius" to 0;
void fillSphere() {
    glPushMatrix();
        GLfloat scaledRadius = sphere_base_radius - ((sphere_base_radius - 0.0)*currentSphereScale/SCALE_SUBDIVISION);
        GLfloat toTranslate = 0.0 + currentSphereScale*(1.0 - 0.0)/SCALE_SUBDIVISION;
        bool t = 1;
        // side faces
        for(int i=0;i<4;i++) {
            glPushMatrix();
                glColor3f(t, !t, 0);
                glTranslatef(toTranslate, 0, 0);
                drawCubeSphereFace(scaledRadius);
            glPopMatrix();
            t = !t;
            glRotatef(90.0, 0, 1, 0);
        }
        // top faces
        for(int i=0;i<2;i++) {
            glRotatef(90.0*(i+1), 0, 0, 1);
            glPushMatrix();
                glColor3f(0, 0, 1);
                glTranslatef(toTranslate, 0 ,0);
                drawCubeSphereFace(scaledRadius);
            glPopMatrix();
        }
    glPopMatrix();

} 

// let the cylinder radius increases from 0.0 to "base_radius"
// let the cylinder height decreases from "base_h" to 0.0
// translation from centre of hypotenuse of triangle to origin
void fillCylinder() {
    GLfloat scaledRadius = cylinder_base_radius - (cylinder_base_radius - 0.0)*(currentCylinderScale*1.0/SCALE_SUBDIVISION);
    GLfloat scaledHeight = 0.0 + (cylinder_base_height - 0.0)*(currentCylinderScale*1.0/SCALE_SUBDIVISION);
    GLfloat originNormalToHypotenuse = sqrt(2*0.5*0.5);
    GLfloat toTranslate = 0.0 + (originNormalToHypotenuse - 0.0)*(currentCylinderScale*1.0/SCALE_SUBDIVISION);
    //xz plane
    glPushMatrix();
        glRotatef(45.0, 0, 1, 0);
        for(int i=0;i<4;i++) {
            glPushMatrix();
                glTranslatef(toTranslate, 0, 0);
                drawCylinder(scaledHeight, scaledRadius, CYLINDER_SUBDIVISION);
            glPopMatrix();
            glRotatef(90.0, 0, 1, 0); 
        }
    glPopMatrix();
    // yz plane
    glPushMatrix();
        glRotatef(45.0, 1, 0, 0);
        for(int i=0;i<4;i++) {
            glPushMatrix();
                glTranslatef(0, toTranslate, 0);
                drawCylinder(scaledHeight, scaledRadius, CYLINDER_SUBDIVISION);
            glPopMatrix();
            glRotatef(90.0, 1, 0, 0);
        }
    glPopMatrix();
    // xy plane
    glPushMatrix();
        glRotatef(90.0, 0, 1, 0);
        glRotatef(45.0, 1, 0, 0);
        for(int i=0;i<4;i++) {
            glPushMatrix();
                glTranslatef(0, toTranslate, 0);
                drawCylinder(scaledHeight, scaledRadius, CYLINDER_SUBDIVISION);
            glPopMatrix();
            glRotatef(90.0, 1, 0, 0);
        }
    glPopMatrix();
}

void drawOctahedron() {
    glPushMatrix();
        // glScalef(currentTriangleScale, currentTriangleScale, currentTriangleScale);
        // glScalef(0.5, 0.5, 0.5);
        bool col = 1;
        for(int i=0;i<4;i++) {
            glColor3f(col, !col, 1);
            col = !col;
            drawBasicTriangle();
            glPushMatrix();
                glColor3f(col, !col, 1);
                glRotatef(45.0, 0, 1, 0);
                glRotatef(180.0, 0, 0, 1);
                glRotatef(-45.0, 0, 1, 0);
                drawBasicTriangle();
            glPopMatrix();
            glRotatef(90.0, 0, 1, 0);
            
        }
    glPopMatrix();
}

void display() {
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(camera.eye.x, camera.eye.y, camera.eye.z,
             camera.centre.x, camera.centre.y, camera.centre.z,
             camera.up.x, camera.up.y, camera.up.z);

    // due to A and D.
    glRotatef(xz_plane_rotation, 0, 1, 0);

    drawAxes();
    drawOctahedron();
    fillSphere();
    fillCylinder();

    glutSwapBuffers();
}

void gl_init(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(50, 50);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("Magic_Cube");
    glClearColor(0, 0, 0, 1); 
    glEnable(GL_DEPTH_TEST);
}

int main(int argc, char* argv[]) {
    gl_init(argc, argv);

    glutDisplayFunc(display);
    glutReshapeFunc(reshapeListener);
    glutSpecialFunc(specialKeyListener);
    glutKeyboardFunc(usualKeyListener);
    // glutIdleFunc(idle);

    glutMainLoop();
    
    return 0;
}