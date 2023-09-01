#ifndef _point_buffer_header_
#define _point_buffer_header_

#include <GL/glut.h>
#include <iostream>
#include <vector>
#include "../1805019_vector/1805019_point3d.h"

using namespace std;

class PointBuffer {

    public: 

        vector<vector<Point3d> > buff;

        PointBuffer() {
            
        }

        PointBuffer(int n) {
            for(int i=0;i<n;i++) {
                buff.push_back(vector<Point3d>(n, Point3d(0, 0, 0)));
            }
        }

        void print() {
            for(int i=0;i<buff.size();i++) {
                for(int j=0;j<buff[i].size();j++) {
                    buff[i][j].print();
                }
                cout << endl;
            }
        }

};

#endif