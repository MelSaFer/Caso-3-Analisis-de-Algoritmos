/*
Class Polyline--------------------------------------------------------------------------------------------------------------
Special Case of paths <polyline>
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

class Polyline : public SvgShape{
    private:
        vector<int*> vertexPoints;
    
    public:
        Polyline(){};

        void setVertexPoints(vector<int*> pVertexPoints) {
            vertexPoints = pVertexPoints;
        }
        
        vector<int*> getVertexPoints() {
            return vertexPoints;
        }

        void addVertexPoint(int pPointX, int pPointY) {
            int point[2];
            point[0] = pPointX;
            point[1] = pPointY;
            vertexPoints.push_back(point);
        }

};