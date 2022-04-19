/*
Class Polygon--------------------------------------------------------------------------------------------------------------
Special Case of paths <ellipse>
This class is used to manage the type rectangle in 
an SVG
*/
#include <string>
#include <vector>

#ifndef SVGPATH_H
#define SVGPATH_H
#endif

class Polygon : public SvgShape{
    private:
        vector<int*> vertexPoints;

    public:
        Polygon(){};

        void setVertexPoints(vector<int*> pVertexPoints){
            vertexPoints = pVertexPoints;
        }

        vector<int*> setVertexPoints(){
            return vertexPoints;
        }

        void addVertexPoints(int pPointX, int pPointY){
            int point[2];
            point[0]= pPointX;
            point[1]= pPointY;
            vertexPoints.push_back(point);
        }

};