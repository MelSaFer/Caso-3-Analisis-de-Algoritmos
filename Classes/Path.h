/* 
Main class used to save the path data. It's used in all three stages.
*/

#include <string>
#include <vector>
#include <iostream>
using namespace std;

//Struct for points in the path
struct PointInPath{
    float xCoordinate;
    float yCoordinate;
    string svgCommand;
    //int positionInCommand; //Use in figures with more than 1 point of reference (like curves)
    //bool isCoordinate;

};

PointInPath parsePoint(string currentPointString){
    cout<< currentPointString<<endl;
    PointInPath currentPoint;

    currentPoint.svgCommand = currentPointString[0];
    currentPointString.erase(0,1);

    string actualNumberString;  //string lectura; 
    stringstream input_stringstream(currentPointString);  //stringstream input_stringstream(cadena); 

    bool isCoordinateX = 1;
    float actualNumber = 0;

    while(getline(input_stringstream, actualNumberString, ' ')){  //while (getline(input_stringstream, lectura, ' ')){
        if (actualNumberString.length() > 0){
            actualNumber = stof(actualNumberString);
            if(isCoordinateX == 1){
                currentPoint.xCoordinate = actualNumber;
                isCoordinateX=0;
            } else{
                currentPoint.yCoordinate = actualNumber;
                isCoordinateX=1;
            }
        }
    }
    cout << "X= " << currentPoint.xCoordinate << " Y: " << currentPoint.yCoordinate << endl;
    return currentPoint;
}


vector<PointInPath> decomposeString(string pPointsSvg, vector<PointInPath> pPathPoints) {
    int initialPosition = 0;
    int finalPosition = 0;   //last o end?
    int flagIgnoreFirst = 0;  //flag for ignore the firt if???
    PointInPath currentPoint;

    int pPointsSvgLenght = pPointsSvg.length();
    string pPointsSvgCopy;
    

    for (int indexInString = 0; indexInString < pPointsSvgLenght; indexInString++){
        //Replace al the "," for " "
        if(pPointsSvg.at(indexInString) == 44){
            pPointsSvg.replace(indexInString, 1, " ");
        }

        finalPosition = indexInString;

        //Posible letters in the atribute d in a svg
        if(pPointsSvg.at(indexInString) == 77 || pPointsSvg.at(indexInString) == 109 || pPointsSvg.at(indexInString) == 67\
        ||pPointsSvg.at(indexInString) == 72 || pPointsSvg.at(indexInString) == 104 || pPointsSvg.at(indexInString) == 99 \
        || pPointsSvg.at(indexInString) == 76 || pPointsSvg.at(indexInString) == 108 || pPointsSvg.at(indexInString) == 90\
        || pPointsSvg.at(indexInString) == 122){

            if(flagIgnoreFirst != 0){
                pPointsSvgCopy = pPointsSvg.substr(initialPosition, finalPosition-initialPosition);
                //cout << "El substring es: " << pPointsSvgCopy << endl;
                //currentPoint.svgCommand = pPointsSvgCopy[0];   //substr = pPointsSvgCopy
                //Variables for reading the numbers in the string of the currentPoint
                currentPoint = parsePoint(pPointsSvgCopy);
                pPathPoints.push_back(currentPoint);
            }
            initialPosition = indexInString;       
            flagIgnoreFirst ++;
        }
    }
    //Special case 1: The path doesnt end in Z or z
    if(pPointsSvg.at(pPointsSvgLenght-1) != 90 && pPointsSvg.at(pPointsSvgLenght-1) != 122){
        pPointsSvgCopy = pPointsSvg.substr(initialPosition, (finalPosition-initialPosition)+1);
        cout << "El substring es: " << pPointsSvgCopy << endl;  //substr = pPointsSvgCopy
    }
    return pPathPoints;
}

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
            pathPoints = decomposeString(pPoints, pathPoints);
            //cout << "Ex";
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
            cout << "Id: " << identifier << "\nColor: " << pathColor << "\nPoints: " ;
            for(int indexOfCurrentPoint = 0; indexOfCurrentPoint < pathPoints.size(); indexOfCurrentPoint++){
                cout << "\t Command: " << pathPoints.at(indexOfCurrentPoint).svgCommand << " - (" ;
                cout << pathPoints.at(indexOfCurrentPoint).xCoordinate << ", " << pathPoints.at(indexOfCurrentPoint).yCoordinate;
                cout << ")" << endl;
            }
            cout << "\nPosition: " << positionInPath << "\nStyle: " << pathStyle <<endl;
        }

        
};