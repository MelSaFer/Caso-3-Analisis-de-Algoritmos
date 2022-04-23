/*
Class Line--------------------------------------------------------------------------------------------------------------
Special Case of paths <line>
This class is used to manage the type rectangle in 
an SVG
*/
#include <string>
#include <vector>
//#include "Path.h"
#ifndef SVGPATH_H
#define SVGPATH_H
#endif


using namespace std;

class Line : public SvgShape{
    private:
        int endPoint[2];
    public:
        Line(){};

        void setEndPoint(int pPointX, int pPointY) {
            endPoint[0] = pPointX;
            endPoint[1] = pPointY;
        }

        int* getEndPoint() {
            return endPoint;
        }
};