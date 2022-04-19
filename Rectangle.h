/*
Class Rectangle--------------------------------------------------------------------------------------------------------------
Special Case of paths <rect>
This class is used to manage the type rectangle in 
an SVG
*/
#include <string>
#include <vector>
#include "Path.h"

using namespace std;

class Rectangle : public Paths{
    private:
        int width;
        int height;
        int roundCorners[2];  //attributes rounds the corners of the rectangle
    
    public:
        Rectangle(){};

        void setWidth(int pWidth){
            width = pWidth;
        }

        int getWidth(){
            return width;
        }

        void setHeight(int pHeight){
            height = pHeight;
        }

        int getHeight(){
            return height;
        }

        int setRoundCorners( int pRoundX, int pRoundY){
            roundCorners[0] = pRoundX;
            roundCorners[1] = pRoundY;
        }

};