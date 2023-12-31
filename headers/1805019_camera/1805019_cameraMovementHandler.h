#ifndef _KEY_header_
#define _KEY_header_

#include <GL/glut.h>
#include <cmath>
#include <stdio.h>
#include "../1805019_config.h"
#include "../1805019_vector/1805019_vectorUtil.h"
#include "../1805019_rayTracing/1805019_rayTracing.h"

using namespace std;


void updateRightVector() {
    camera.right = normalize(cross_product(camera.eyeToCentreVector(), camera.up));
}

void rotate_camera_left_right(GLfloat f) {
    GLfloat theta = f*DEL*0.2;
    Point3d shifted_centre = Point3d(camera.centre.x-camera.eye.x, camera.centre.y-camera.eye.y, camera.centre.z-camera.eye.z);
    Point3d rotated_centre = Rodrigues_formula(shifted_centre, camera.up, theta);
    camera.centre = addVector(rotated_centre, camera.eye); 
    updateRightVector();
}

void rotate_camera_up_down(GLfloat f) {
    updateRightVector();
    GLfloat theta = f*DEL*0.2;
    Point3d shifted_centre = Point3d(camera.centre.x-camera.eye.x, camera.centre.y-camera.eye.y, camera.centre.z-camera.eye.z);
    Point3d rotated_centre = Rodrigues_formula(shifted_centre, camera.right, theta);
    camera.centre = addVector(rotated_centre, camera.eye);
    camera.up = normalize(cross_product(camera.right, camera.eyeToCentreVector()));
}

void tilt_eye(GLfloat f) {
    GLfloat theta = f*DEL*0.2;
    Point3d rotated_up = Rodrigues_formula(camera.up, camera.eyeToCentreVector(), theta);
    camera.up = normalize(rotated_up);
    updateRightVector();
}

void translate_camera_right_left(GLfloat f) {
    updateRightVector();
    camera.centre.x += f*DEL*camera.right.x*30;
    camera.centre.y += f*DEL*camera.right.y*30;
    camera.centre.z += f*DEL*camera.right.z*30;

    camera.eye.x += f*DEL*camera.right.x*30;
    camera.eye.y += f*DEL*camera.right.y*30;
    camera.eye.z += f*DEL*camera.right.z*30;
}

void translate_camera_forward_backward(GLfloat f) {
    Point3d dir = normalize(camera.eyeToCentreVector());
    camera.eye.x += f*dir.x*DEL*30;
    camera.eye.y += f*dir.y*DEL*30;
    camera.eye.z += f*dir.z*DEL*30;

    camera.centre.x += f*dir.x*DEL*30;
    camera.centre.y += f*dir.y*DEL*30;
    camera.centre.z += f*dir.z*DEL*30;
}

void translate_camera_up_down(GLfloat f) {
    camera.eye.x += f*camera.up.x*DEL*10;
    camera.eye.y += f*camera.up.y*DEL*10;
    camera.eye.z += f*camera.up.z*DEL*10;

    camera.centre.x += f*camera.up.x*DEL*10;
    camera.centre.y += f*camera.up.y*DEL*10;
    camera.centre.z += f*camera.up.z*DEL*10;
}


void screenCapture() {
    cout << "Trying to Capture screen!\n";
    RayTracing tracing = RayTracing(number_of_pixels, camera);
    tracing.traceRays();
    tracing.saveBMPimage("out.bmp");
}

void fixed_reference_move_upDown(GLfloat f) {
    camera.eye.y += f*DEL;
    camera.up = normalize(cross_product(camera.right, camera.eyeToCentreVector()));
}


void usualKeyListener(unsigned char key, int x, int y) {
    switch(key) {
        case 'a':
            // xz_plane_rotation--;
            break;
        case 'd':
            // xz_plane_rotation++;
            break;
        case 'w':
            // fixed_reference_move_upDown(1.0);
            break;
        case 's':
            // fixed_reference_move_upDown(-1.0);
            break;
        case '1':
            rotate_camera_left_right(1.0);
            break;
        case '2':
            rotate_camera_left_right(-1.0);
            break;
        case '3':
            rotate_camera_up_down(1.0);
            break;
        case '4':
            rotate_camera_up_down(-1.0);
            break;
        case '5':
            tilt_eye(1.0);
            break;
        case '6':
            tilt_eye(-1.0);
            break;
        case '0':
            screenCapture();
    }
    glutPostRedisplay();
}

void specialKeyListener(int key, int x, int y) {
    GLfloat eyeToCentre_x = camera.centre.x - camera.eye.x;
    GLfloat eyeToCentre_y = camera.centre.z - camera.eye.z;
    GLfloat proj;

    switch(key) {
        case GLUT_KEY_UP:
            translate_camera_forward_backward(1.0);
            break;
        case GLUT_KEY_DOWN:
            translate_camera_forward_backward(-1.0);
            break;
        case GLUT_KEY_LEFT:
            translate_camera_right_left(-1.0);
            break;
        case GLUT_KEY_RIGHT:
            translate_camera_right_left(1.0);
            break;
        case GLUT_KEY_PAGE_UP:
            translate_camera_up_down(1.0);
            break;
        case GLUT_KEY_PAGE_DOWN:
            translate_camera_up_down(-1.0);
            break;
        
    }

    glutPostRedisplay();
}

#endif