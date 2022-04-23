/* 
Main class used to save the path data. It's used in all three stages.
*/

#include <string>
#include <vector>
using namespace std;

/*Class Path*/
class Path{
    private:
        string identifier;
        string pathColor;
        string pathPoints;
        string pathStyle;
        string otherInformation;
    public:
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
            pathPoints = pPoints;
        }
        string getPathPoints() {
            return pathPoints;
        }

        void setPathStyle(string pStyle) {
            pathStyle = pStyle;
        }
        string getPathStyle() {
            return pathStyle;
        }

        void toString(){
            cout << "Id: " << identifier << "\nColor: " << pathColor << "\nPoints: " << pathPoints << "\nStyle: " << pathStyle <<endl;
        }


        
};