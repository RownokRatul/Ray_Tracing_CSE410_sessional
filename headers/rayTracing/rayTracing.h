#ifndef _ray_tracing_header_
#define _ray_tracing_header_

#include <GL/glut.h>
#include <iostream>
#include "../config.h"
#include "ray.h"
#include "colorBuffer.h"
#include "pointBuffer.h"
#include "../vector/vectorUtil.h"
#include "../bitmap_image.hpp"

using namespace std;

class RayTracing {

    public:

        PointBuffer pointBuffer;
        ColorBuffer colorBuffer;
        Camera eye;
        GLfloat width;
        GLfloat height;
        GLfloat dx;
        GLfloat dy;

        RayTracing(int pix, Camera cam) {
            pointBuffer = PointBuffer(pix);
            colorBuffer = ColorBuffer(pix);
            eye = cam;
            height = 2*near_plane*tan(fovy*PI/360.0f);
            width = height*aspect_ratio;
            dx = width/number_of_pixels;
            dy = height/number_of_pixels;
        }

        
        void fillUpBuffers() {
            Point3d near_mid = addVector(eye.eye, scaleVector(normalize(eye.eyeToCentreVector()), near_plane));
            Point3d near_mid_left = addVector(near_mid, scaleVector(normalize(eye.right), -width/2));
            Point3d near_top_left = addVector(near_mid_left, scaleVector(normalize(eye.up), height/2));

            Point3d row_start = near_top_left;
            Point3d cur;

            for(int row=0;row<number_of_pixels;row++) {
                cur = row_start;
                for(int col=0;col<number_of_pixels;col++) {
                    pointBuffer.buff[row][col] = cur;
                    cur = addVector(cur, scaleVector(normalize(eye.right), dx)); 
                }
                row_start = addVector(row_start, scaleVector(normalize(eye.up), -dy));
            }
        }


        Color get_pixel_color(Ray ray) {
            GLfloat t = MAX_T;
            Color color = Color(0, 0, 0);
            for(Object* obj : objects) {
                Intersection intersection = obj->getIntersectionPoint(ray);
                if(intersection.t > 0 && intersection.t < t) {
                    t = intersection.t;
                    color = intersection.color;
                    // cout << "Found Proper Intersection!\n";
                }
            }
            return color;
        }


        void sendRays() {
            for(int row=0;row<number_of_pixels;row++) {
                for(int col=0;col<number_of_pixels;col++) {
                    Point3d d = normalize(subtractVector(pointBuffer.buff[row][col], eye.eye));
                    Ray ray = Ray(pointBuffer.buff[row][col], d);
                    colorBuffer.buff[row][col] = get_pixel_color(ray);
                }
            }
        }


        void traceRays() {
            fillUpBuffers();
            sendRays();
        }


        void rightRotateColorBuffer() {
            ColorBuffer temp = ColorBuffer(number_of_pixels);
            for(int i=0;i<number_of_pixels;i++) {
                for(int j=0;j<number_of_pixels;j++) {
                    temp.buff[i][j] = colorBuffer.buff[j][number_of_pixels - i - 1];
                }
            }
            colorBuffer = temp;
        }


        void reflectColorBuffer() {
            ColorBuffer temp = ColorBuffer(number_of_pixels);
            for(int i=0;i<number_of_pixels;i++) {
                for(int j=0;j<number_of_pixels;j++) {
                    temp.buff[i][j] = colorBuffer.buff[number_of_pixels - i - 1][j];
                }
            }
            colorBuffer = temp;
        }


        void saveBMPimage(string t) {
            bitmap_image* img = new bitmap_image(number_of_pixels, number_of_pixels);
            rightRotateColorBuffer();
            reflectColorBuffer();
            for(int i=0;i<number_of_pixels;i++) {
                for(int j=0;j<number_of_pixels;j++) {
                    Color c = colorBuffer.buff[i][j];
                    img->set_pixel(i, j, c.r*255, c.g*255, c.b*255);
                }
            }
            img->save_image(t);
            cout << "Image Saved!\n";
            delete img;
        }


};


#endif