/*
Class Circle--------------------------------------------------------------------------------------------------------------
Special Case of paths
This class is used to manage the tyoe cicle in 
an SVG
*/
#include <string>
#include <vector>
#include "Path.h"
//#ifndef PATH_H
//#define PATH_H
//#endif

using namespace std;

class Circle : public Paths{
    private:
        int circleRadius;
    
    public:
        // default builder
        Circle(){};
  
        void setRadius(int pRadius){
            circleRadius = pRadius;
        }

        int getRadius(){
            return circleRadius;
        }

};