#ifndef _objects_header_
#define _objects_header_

#include <GL/glut.h>
#include <vector>
#include "../1805019_vector/1805019_point3d.h"
#include "../1805019_color.h"
#include "1805019_intersection.h"
#include "../1805019_rayTracing/1805019_ray.h"
#include "1805019_plane.h"

using namespace std;

class Object {
    
        public:
    
            GLfloat ambient_coefficient;
            GLfloat diffuse_coefficient;
            GLfloat reflection_coefficient;
            GLfloat specular_coefficient;
            GLfloat shininess;
            Color color;
    
            Object() {
                
            }

            Object(GLfloat ac, GLfloat dc, GLfloat rc) {
                ambient_coefficient = ac;
                diffuse_coefficient = dc;
                reflection_coefficient = rc;
            }
    
            Object(GLfloat ac, GLfloat dc, GLfloat sc, GLfloat rc, GLfloat sh) {
                ambient_coefficient = ac;
                diffuse_coefficient = dc;
                reflection_coefficient = rc;
                specular_coefficient = sc;
                shininess = sh;
            }

            void setColor(Color c) {
                color = c;
            }
    
            virtual void draw() = 0;
            virtual Intersection getIntersectionPoint(Ray r) = 0;
            virtual void print() = 0;

};



#endif