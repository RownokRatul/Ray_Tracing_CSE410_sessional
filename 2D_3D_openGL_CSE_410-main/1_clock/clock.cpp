#include<GL/glut.h>
#include<iostream>
#include<math.h>
#include<ctime>
#include "point.h"
#include "draw.h"
#include "config.h"
#include "2Dpendulum.h"

using namespace std;

SecondPendulum pendulum(pendulum_amplitude, pendulum_initial_phase);

void drawTimeIndicator(int howMany, GLfloat scale) {
    glPushMatrix();
    {
        for(int i=0;i<howMany;i++) {
            drawLine(point(0, inner_radius), point(0, inner_radius/scale));
            glRotatef(360.0/howMany, 0, 0, 1);
        }
    }
    glPopMatrix();
}

void indicateDialTime() {
    drawTimeIndicator(4, 1.25);
    drawTimeIndicator(12, 1.15);
    drawTimeIndicator(60, 1.05);
}

void drawClockBody() {
    drawCircle(inner_radius, steps_to_draw);
    drawCircle(outer_radius, steps_to_draw);
    indicateDialTime();
}

void mapHands(GLfloat l,GLfloat w, GLfloat rot) {
    // cout << rot << endl;
    glPushMatrix();
    {
        glRotatef(rot, 0, 0, 1);
        drawQuad(point(w, 0), point(w, l), point(-w, l), point(-w, 0.0));
        drawTriangle(point(w, l), point(-w, l), point(0.0, l+l/2.5));
    }
    glPopMatrix();
}

void oneSecondPassed(int value) {
    glutTimerFunc(1000, oneSecondPassed, 0); 
    glutPostRedisplay();
}

void drawHands(int value) {
    // glutPostRedisplay();
    // glutTimerFunc(1000, drawHands, 0);
    time_t now = time(0);
    tm *local = localtime(&now);
    cout << local->tm_hour << ":" << local->tm_min << ":" << local->tm_sec << "\n";
    GLfloat hour = local->tm_hour*1.0 + local->tm_min/60.0 ;
    GLfloat min = local->tm_min*1.0 + local->tm_sec/60.0;
    mapHands(hand_length/1.2, hand_width/1.2, -(hour/12.0)*360.0); // hour
    mapHands(hand_length/0.9, hand_width/2, -(min/60.0)*360.0); // minute
    mapHands(hand_length/0.8, hand_width/3, -(local->tm_sec/60.0)*360.0); // second
}

void makeClock() {
    glPushMatrix(); 
    {
        glTranslatef(dial_centre.x, dial_centre.y, 0);
        drawClockBody();
        drawHands(0);
    }
    glPopMatrix();    
}

void attachPendulum(int value) {
    glutTimerFunc(10, attachPendulum, 0);
    glutPostRedisplay();
}

void idle() {
    // glutPostRedisplay();
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // glClearColor(0, 0, 0, 0); 
    // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // drawFilledCircle(0.3, 20);
    makeClock();
    pendulum.drawBob();

    glutSwapBuffers();
}

void gl_init(int pargc, char* pargv[]) {
    glutInit(&pargc, pargv);
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(0, 0);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
    glutCreateWindow("Clock");
    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);
}

int main(int argc, char* argv[]) {
    // cout << "hello\n";
    gl_init(argc, argv);

    glutDisplayFunc(display);
    glutIdleFunc(idle);
    // glutTimerFunc(0, oneSecondPassed, 0);
    glutTimerFunc(0, attachPendulum, 0);

    glutMainLoop();
    
    return 0;
}