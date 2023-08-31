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
#include "../config.h"

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


        Intersection getClosestIntersectionPoint(Ray ray) {
            Intersection in = Intersection(false);
            for(Object* obj : objects) {
                Intersection intersection = obj->getIntersectionPoint(ray);
                if(intersection.t > 0 && intersection.t < in.t) {
                    in = intersection;
                }
            }
            return in;
        }


        bool isIlluminatedByPointLight(Point3d p, PointLight light) {
            Ray ray = Ray(p, subtractVector(p, light.position));
            Intersection in = getClosestIntersectionPoint(ray);
            if(in.intersects && (distanceBetweenPoints(p, light.position) > distanceBetweenPoints(in.point, light.position))) {
                return false;
            }
            return true;
        }

        bool isIlluminatedBySpotLight(Point3d p, SpotLight light) {
            Point3d look = normalize(subtractVector(light.look, light.position));
            Point3d light_to_point = normalize(subtractVector(p, light.position));
            GLfloat angle = acos(dot_product(look, light_to_point));
            if(angle*180.0f/PI > light.cutoff) {
                return false;
            }
            Ray ray = Ray(p, subtractVector(p, light.position));
            Intersection in = getClosestIntersectionPoint(ray);
            if(in.intersects && (distanceBetweenPoints(p, light.position) > distanceBetweenPoints(in.point, light.position))) {
                return false;
            }
            return true;
        }

        pair<GLfloat, GLfloat> computeLambertPhongValues(Intersection in, PointLight light, Ray ray) {
            Point3d pointToLight = normalize(subtractVector(light.position, in.point));
            Ray reflected = Ray(in.point, ray.getReflectedRay(in.normal));
            GLfloat distance = distanceBetweenPoints(in.point, light.position);
            GLfloat scaling_factor = exp(-distance*distance*light.falloff);
            // GLfloat scaling_factor = 1.0f;
            GLfloat factor_lambert = max (0.0f, dot_product(in.normal, pointToLight));
            GLfloat factor_phong = max(0.0f, dot_product(reflected.direction, pointToLight));
            GLfloat lambert = scaling_factor*factor_lambert;
            GLfloat phong = scaling_factor*pow(factor_phong, in.shininess);
            return make_pair(lambert, phong);
        }

        pair<GLfloat, GLfloat> computeLambertPhongValues(Intersection in, SpotLight light, Ray ray) {
            Point3d pointToLight = normalize(subtractVector(light.position, in.point));
            Ray reflected = Ray(in.point, ray.getReflectedRay(in.normal));
            GLfloat distance = distanceBetweenPoints(in.point, light.position);
            GLfloat scaling_factor = exp(-distance*distance*light.falloff);
            // GLfloat scaling_factor = 1.0f;
            GLfloat factor_lambert = max (0.0f, dot_product(in.normal, pointToLight));
            GLfloat factor_phong = max(0.0f, dot_product(reflected.direction, pointToLight));
            GLfloat lambert = scaling_factor*factor_lambert;
            GLfloat phong = scaling_factor*pow(factor_phong, in.shininess);
            return make_pair(lambert, phong);
        }
        

        Color get_pixel_color(Ray ray, int level) {
            Intersection in = getClosestIntersectionPoint(ray);
            // no intersection
            if(!in.intersects) {
                return in.color;
            }

            if(normal_mapping_debug) {
                return Color((in.normal.x+1)/2, (in.normal.y+1)/2, (in.normal.z+1)/2);
            }

            GLfloat lambert = 0;
            GLfloat phong = 0; 
            for(PointLight light : pointLights) {
                if(isIlluminatedByPointLight(in.point, light)) {
                    pair<GLfloat, GLfloat> lambert_phong = computeLambertPhongValues(in, light, ray);
                    lambert += lambert_phong.first;
                    phong += lambert_phong.second;
                }
            }
            for(SpotLight light : spotLights) {
                if(isIlluminatedBySpotLight(in.point, light)) {
                    pair<GLfloat, GLfloat> lambert_phong = computeLambertPhongValues(in, light, ray);
                    lambert += lambert_phong.first;
                    phong += lambert_phong.second;
                }
            }

            Color c1 = scaleColor(in.color, in.ambient_coefficient);
            Color c2 = scaleColor(in.color, in.diffuse_coefficient*lambert);
            Color c3 = scaleColor(in.color, in.specular_coefficient*phong);

            Color final_color = addColors(addColors(c1, c2), c3);

            // recursion for reflected ray
            if(level == 1) {
                return final_color;
            }
            
            Ray reflected = Ray(in.point, ray.getReflectedRay(in.normal));
            reflected.origin = addVector(in.point, scaleVector(reflected.direction, 0.01f));
            Color reflected_color = get_pixel_color(reflected, level - 1);
            final_color = addColors(final_color, scaleColor(reflected_color, in.reflection_coefficient));
            return final_color;
        }


        void sendRays() {
            for(int row=0;row<number_of_pixels;row++) {
                for(int col=0;col<number_of_pixels;col++) {
                    Point3d d = normalize(subtractVector(pointBuffer.buff[row][col], eye.eye));
                    Ray ray = Ray(pointBuffer.buff[row][col], d);
                    Color c = get_pixel_color(ray, level_of_recursion);
                    colorBuffer.buff[row][col] = Color(min(c.r, 1.0f), min(c.g, 1.0f), min(c.b, 1.0f));
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