#ifndef _KEY_header_
#define _KEY_header_

#include <GL/glut.h>
#include <cmath>
#include <stdio.h>
#include "config.h"
#include "vector.h"

void updateRightVector() {
    camera.right = cross_product(camera.eyeToCentreVector(), camera.up);
    // printf("%f %f %f\n", camera.right.x, camera.right.y, camera.right.z);
}

void rotate_eye_left_right(GLfloat f) {
    GLfloat theta = f*DEL*0.2;
    point3d shifted_centre = point3d(camera.centre.x-camera.eye.x, camera.centre.y-camera.eye.y, camera.centre.z-camera.eye.z);
    point3d rotated_centre = Rodrigues_formula(shifted_centre, camera.up, theta);
    camera.centre = addVector(rotated_centre, camera.eye); 
    updateRightVector();
}

void rotate_eye_up_down(GLfloat f) {
    updateRightVector();
    GLfloat theta = f*DEL*0.2;
    point3d shifted_centre = point3d(camera.centre.x-camera.eye.x, camera.centre.y-camera.eye.y, camera.centre.z-camera.eye.z);
    point3d rotated_centre = Rodrigues_formula(shifted_centre, camera.right, theta);
    camera.centre = addVector(rotated_centre, camera.eye);
}

void tilt_eye(GLfloat f) {
    GLfloat theta = f*DEL*0.2;
    point3d rotated_up = Rodrigues_formula(camera.up, camera.eyeToCentreVector(), theta);
    camera.up = rotated_up;
    updateRightVector();
}


void translate_eye_right_left(GLfloat f) {
    updateRightVector();
    camera.centre.x += f*DEL*camera.right.x;
    camera.centre.y += f*DEL*camera.right.y;
    camera.centre.z += f*DEL*camera.right.z;

    camera.eye.x += f*DEL*camera.right.x;
    camera.eye.y += f*DEL*camera.right.y;
    camera.eye.z += f*DEL*camera.right.z;
}

void translate_eye_forward_backward(GLfloat f) {
    point3d dir = camera.eyeToCentreVector();
    camera.eye.x += f*dir.x*DEL;
    camera.eye.y += f*dir.y*DEL;
    camera.eye.z += f*dir.z*DEL;

    camera.centre.x += f*dir.x*DEL;
    camera.centre.y += f*dir.y*DEL;
    camera.centre.z += f*dir.z*DEL;
}

void translate_eye_up_down(GLfloat f) {
    camera.eye.x += f*camera.up.x*DEL;
    camera.eye.y += f*camera.up.y*DEL;
    camera.eye.z += f*camera.up.z*DEL;

    camera.centre.x += f*camera.up.x*DEL;
    camera.centre.y += f*camera.up.y*DEL;
    camera.centre.z += f*camera.up.z*DEL;
}

void fixed_reference_move_upDown(GLfloat f) {
    camera.eye.y += f*DEL;
    camera.up = cross_product(camera.right, camera.eyeToCentreVector());
}

void octahedronToSphere() {
    // printf("o to S\n");
    if(currentTriangleScale > 0) {
        currentTriangleScale--;
        currentSphereScale--;
        currentCylinderScale--;
    }
}

void sphereToOctahedron() {
    // printf("s to o\n");
    if(currentTriangleScale < SCALE_SUBDIVISION) {
        currentTriangleScale++;
        currentSphereScale++;
        currentCylinderScale++;
    }
}

void usualKeyListener(unsigned char key, int x, int y) {
    switch(key) {
        case 'a':
            xz_plane_rotation--;
            break;
        case 'd':
            xz_plane_rotation++;
            break;
        case 'w':
            fixed_reference_move_upDown(1.0);
            break;
        case 's':
            fixed_reference_move_upDown(-1.0);
            break;
        case '1':
            rotate_eye_left_right(1.0);
            break;
        case '2':
            rotate_eye_left_right(-1.0);
            break;
        case '3':
            rotate_eye_up_down(1.0);
            break;
        case '4':
            rotate_eye_up_down(-1.0);
            break;
        case '5':
            tilt_eye(1.0);
            break;
        case '6':
            tilt_eye(-1.0);
            break;
        case ',':
            octahedronToSphere();
            break;
        case '.':
            sphereToOctahedron();
            break;
    }
    glutPostRedisplay();
}

void specialKeyListener(int key, int x, int y) {
    GLfloat eyeToCentre_x = camera.centre.x - camera.eye.x;
    GLfloat eyeToCentre_y = camera.centre.z - camera.eye.z;
    GLfloat proj;

    switch(key) {
        case GLUT_KEY_UP:
            translate_eye_forward_backward(1.0);
            break;
        case GLUT_KEY_DOWN:
            translate_eye_forward_backward(-1.0);
            break;
        case GLUT_KEY_LEFT:
            translate_eye_right_left(-1.0);
            break;
        case GLUT_KEY_RIGHT:
            translate_eye_right_left(1.0);
            break;
        case GLUT_KEY_PAGE_UP:
            translate_eye_up_down(1.0);
            break;
        case GLUT_KEY_PAGE_DOWN:
            translate_eye_up_down(-1.0);
            break;
        
    }

    glutPostRedisplay();
}

#endif