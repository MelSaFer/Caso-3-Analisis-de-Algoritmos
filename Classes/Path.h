/* 
Main class used to save the path data. It's used in all three stages.
*/

#include <string>
#include <vector>
#include <iostream>
using namespace std;

//Struct for points in the path
struct PointInPath{
    int xCoordinate;
    int yCoordinate;
    string svgCommand;
    int positionInCommand; //Use in figures with more than 1 point of reference (like curves)
    bool isCoordinate;

};

/*Class Path*/
class Path{
    private:
        string identifier;
        string pathColor;
        vector<PointInPath> pathPoints;
        string pathStyle;
        string otherInformation;
        int positionInPath;

    public:

        void setPositionInPath(int pCurrentPosition){
            positionInPath = pCurrentPosition;
        }

        int getPositionInPath(){
            return positionInPath;
        }

        void setIdentifier(string pIdentifer) {
            identifier = pIdentifer;
        }
        string getIdentifier() {
            return identifier;
        }

        void setPathColor(string pColor) {
            pathColor = pColor;
        }
        string getPathColor() {
            return pathColor;
        }

        void setPathPoints(string pPoints) {
            //cout << pPoints <<endl;
        }

        vector<PointInPath> getPathPoints() {
            return pathPoints;
        }

        void setPathStyle(string pStyle) {
            pathStyle = pStyle;
        }
        string getPathStyle() {
            return pathStyle;
        }

        void toString(){
            cout << "Id: " << identifier << "\nColor: " << pathColor << "\nPoints: " << "\nPosition: " << positionInPath;
            
            cout<< "\nStyle: " << pathStyle <<endl;
        }


        
};