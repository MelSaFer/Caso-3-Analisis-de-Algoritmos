/*
Class Ellipse--------------------------------------------------------------------------------------------------------------
Special Case of paths <ellipse>
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

class Ellipse : public SvgShape{
    private:
        int horizontalRadius;
        int verticalRadius;
    
    public:
        Ellipse(){};

        void setHorizontalRadius(int pHorizontalRadius){
            horizontalRadius = pHorizontalRadius;
        }

        int getHorizontalRadius(){
            return horizontalRadius;
        }

        void setVerticalRadius(int pVerticalRadius){
            verticalRadius = pVerticalRadius;
        }

        int getVerticalRadius(){
            return verticalRadius;
        }


};