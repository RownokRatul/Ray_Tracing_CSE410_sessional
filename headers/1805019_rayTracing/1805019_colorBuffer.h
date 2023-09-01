#ifndef _color_buffer_header_
#define _color_buffer_header_

#include <GL/glut.h>
#include <iostream>
#include <vector>
#include "../1805019_color.h"

using namespace std;

class ColorBuffer {

    public:

        vector<vector<Color> > buff;

        ColorBuffer() {
            
        }

        ColorBuffer(int n) {
            for(int i=0;i<n;i++) {
                buff.push_back(vector<Color>(n, Color(0, 0, 0)));
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