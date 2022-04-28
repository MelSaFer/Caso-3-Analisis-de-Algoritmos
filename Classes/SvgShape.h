/* 
Main class used to save the path data and generate
the animation. It's used in all three stages.
*/

#ifndef SVGSHAPE
#define SVGSHAPE

#include <string>
#include <vector>
using namespace std;

/*Class SvgShape*/
class SvgShape{
    private:
        string identifier;
        int initialXYPoints[2];
        int finalXYPoints[2];
        int movementAngle;
        string pathColor;
        int posibleFrames;
        vector<int*> movementPoints;
        string strokeColor;
        int strokeWidth;
    
    public:
        SvgShape(){};

        void setIdentifier(string pIdentifer) {
            identifier = pIdentifer;
        }
        string getIdentifier() {
            return identifier;
        }

        void setInitialXYPoints(int pPointX, int pPointY){
            initialXYPoints[0]= pPointX;
            initialXYPoints[1]= pPointY;
        }

        int* getInitialXYPoints(){
            return initialXYPoints;
        }

        void setFinalXYPoints(int pPointX, int pPointY){
            finalXYPoints[0]= pPointX;
            finalXYPoints[1]= pPointY;
        }

        int* getFinalXYPoints(){
            return finalXYPoints;
        }

        void setMovementAngle(int pAngle) {
            movementAngle = pAngle;
        }
        int getMovementAngle() {
            return movementAngle;
        }
        void setPathColor(string pColor) {
            pathColor = pColor;
        }
        string getPathColor() {
            return pathColor;
        }
        void setPosibleFrames(int pFrames) {
            posibleFrames = pFrames;
        }
        int getPosibleFrames() {
            return posibleFrames;
        }
        void setMovementPoints(vector<int*> pPoints) {
            movementPoints = pPoints;
        }
        vector<int*> getMovementPoints() {
            return movementPoints;
        }
        void addMovementPoint(int pMovement[2]){
            movementPoints.push_back(pMovement);
        }
        void setStrokeColor(string pColor) {
            strokeColor = pColor;
        }
        string getStrokeColor() {
            return strokeColor;
        }
        void setStrokeWidth(int pWidth) {
            strokeWidth = pWidth;
        }
        int getStrokeWidth() {
            return strokeWidth;
        }
};

#endif