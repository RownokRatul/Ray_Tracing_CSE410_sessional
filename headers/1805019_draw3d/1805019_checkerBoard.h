#ifndef _checkerBoard_header_
#define _checkerBoard_header_


#include <GL/glut.h>
#include <cmath>
#include "../1805019_config.h"
#include "1805019_basicShapes.h"
#include "1805019_objects.h"
#include "../1805019_bitmap_image.hpp"

using namespace std;

class CheckerBoard : public Object {

    public:

        GLfloat square_width;
        bitmap_image texture_w;
        bitmap_image texture_b;


        CheckerBoard(GLfloat sw, GLfloat ac, GLfloat dc, GLfloat rc) : Object(ac, dc, rc) {
            square_width = sw;
            texture_w = bitmap_image("texture_w.bmp");
            texture_b = bitmap_image("texture_b.bmp");
        }

        
        CheckerBoard() {
            square_width = 1;
            ambient_coefficient = 0.4;
            diffuse_coefficient = 0.4;
            reflection_coefficient = 0.2;
            shininess = 0;
            specular_coefficient = 0;
        }

        
        void draw() {
            // cout << "Drawing CheckerBoard" << endl;
            int camera_x = (camera.eye.x)/square_width;
            int camera_y = (camera.eye.y)/square_width;
            int color = 1;
            glPushMatrix();
            {
                glTranslatef(camera_x*square_width, camera_y*square_width, 0);
                // glTranslatef(camera.eye.x, camera.eye.y, 0);
                color = ((camera_x + camera_y) % 2) ? 0 : 1;
                for(int i = -INF; i < INF; i++) {
                    for(int j = -INF; j < INF; j++) {
                        glColor3f(color, color, color);
                        drawQuad(Point3d(i * square_width, j * square_width, 0), Point3d((i + 1) * square_width, j * square_width, 0), Point3d((i + 1) * square_width, (j + 1) * square_width, 0), Point3d(i * square_width, (j + 1) * square_width, 0));
                        color = 1 - color;
                    }
                    color = 1 - color;
                }
            }
            glPopMatrix();
        }

        
        Color texture_mapping(Point3d point, int which) {
            bitmap_image texture = which ? texture_w : texture_b;
            GLfloat x = fmod(fmod(point.x, square_width) + square_width, square_width);
            GLfloat y = fmod(fmod(point.y, square_width) + square_width, square_width);
            GLfloat texture_width = texture.width() - 1;
            GLfloat texture_height = texture.height() - 1;
            unsigned int tex_x = (x/square_width)*texture_width;
            unsigned int tex_y = (y/square_width)*texture_height;
            unsigned char r, g, b;
            texture.get_pixel(tex_y, tex_x, r, g, b);
            return Color(r*1.0f/255.0f, g*1.0f/255.0f, b*1.0f/255.0f);
        }


        Intersection getIntersectionPoint(Ray ray) {
            Plane plane = Plane(Point3d(0, 0, 1), 0);
            GLfloat t = plane.intersect(ray);
            if(t < 0 || t >= MAX_T) {
                return Intersection(false);
            }
            Point3d intersectionPoint = ray.getPointAtaDistance(t);
            int i = (ceil)(intersectionPoint.x/square_width);
            int j = (ceil)(intersectionPoint.y/square_width);
            Color c;
            if((i + j) % 2) {
                // c = Color(0, 0, 0);
                c = texture_mapping(intersectionPoint, 0);
            }
            else {
                // c = Color(1, 1, 1);
                c = texture_mapping(intersectionPoint, 1);
            }
            return Intersection(intersectionPoint, Point3d(0, 0, 1), c, t, shininess, true, ambient_coefficient, diffuse_coefficient, reflection_coefficient, specular_coefficient);
        }


        void print() {
            cout << "--------CheckerBoard--------" << endl;
            cout << "square_width: " << square_width << endl;
            cout << "ambient_coefficient: " << ambient_coefficient << endl;
            cout << "diffuse_coefficient: " << diffuse_coefficient << endl;
            cout << "reflection_coefficient: " << reflection_coefficient << endl;
            cout << "-------------------" << endl;
        }

};


#endif 