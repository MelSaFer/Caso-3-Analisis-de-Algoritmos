/* 
Main class used to save the path data and generate
the animation. It's used in all three stages.
*/

#include <string>
#include <vector>
using namespace std;

class Path {
    private:
        string identifier;
        int initialXPoint;
        int initialYPoint;
        int finalXPoint;
        int finalYPoint;
        int movementAngle;
        string pathColor;
        int posibleFrames;
        vector<int> movementPoints;
    
    public:
        void setIdentifier(string pIdentifer) {
            identifier = pIdentifer;
        }
        string getIdentifier() {
            return identifier;
        }
        void setInitialXPoint(int pInitialPoint) {
            initialXPoint = pInitialPoint;
        }
        int getInitialXPoint() {
            return initialXPoint;
        }
        void setInitialYPoint(int pInitialPoint) {
            initialYPoint = pInitialPoint;
        }
        int getInitialYPoint() {
            return initialYPoint;
        }
        void setFinalXPoint(int pFinalPoint) {
            finalXPoint = pFinalPoint;
        }
        int getFinalXPoint() {
            return finalXPoint;
        }
        void setFinalYPoint(int pFinalPoint) {
            finalYPoint = pFinalPoint;
        }
        int getFinalYPoint() {
            return finalYPoint;
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
        void setMovementPoints(vector<int> pPoints) {
            movementPoints = pPoints;
        }
        vector<int> getMovementPoints() {
            return movementPoints;
        }
        void addMovementPoint(int pMovement){
            movementPoints.push_back(pMovement);
        }
};