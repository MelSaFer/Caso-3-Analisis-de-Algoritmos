#ifndef PATH
#define PATH

/*
Main class used to save the path data. It's used in all three stages.
*/

#include <string>
#include <vector>
#include <iostream>
#include<fstream>
#include <sstream>

using namespace std;


//Struct for points in the path
struct PointInPath{
    float xCoordinate;
    float yCoordinate;
    string svgCommand;
    vector <float> offsetPoints; //This vector is for save the movement points generated in routing
};

/*
-----------------------------------------------------------------------------
This function normalize the path (if it comes with "," put " ")
    Parameters: The string of the attribute d of a path
    Return: The string with the changes
-----------------------------------------------------------------------------
*/
string normalizePath(string currentPointString){
    string normalizedString;
    for(int currentLetter = 0; currentLetter < currentPointString.length(); currentLetter++){
        if(currentPointString.at(currentLetter) == 45){
            normalizedString += " ";
        }
        normalizedString += currentPointString[currentLetter];
    }
    return normalizedString;
}

/*
-----------------------------------------------------------------------------
This function reads the case when we have an H or an V in the attribute d
    Parameters: The string of the attribute d of a path and the vector
                of points in the current path
    Return: the current point
-----------------------------------------------------------------------------
*/
PointInPath specialCaseHV(string currentPointString, vector<PointInPath> &pPathPoints){
    PointInPath lastPoint;
    lastPoint = pPathPoints.back();

    PointInPath currentPoint;
    currentPoint.xCoordinate = lastPoint.xCoordinate;
    currentPoint.yCoordinate = lastPoint.yCoordinate;
    string copyCurrentPointString = currentPointString;

    // assign the letter (in this case H or V)
    currentPoint.svgCommand = currentPointString[0];
    // deletes the letter 
    currentPointString.erase(0,1);
    
    string actualNumberString;
    stringstream input_stringstream(currentPointString); 

    float actualNumber = 0;

    while(getline(input_stringstream, actualNumberString, ' ')){  

        if (actualNumberString.length() > 0){
            actualNumber = stof(actualNumberString);
            if( copyCurrentPointString.at(0) == 72 ){
                currentPoint.xCoordinate = actualNumber;
                pPathPoints.push_back(currentPoint);
            }
            else if(copyCurrentPointString.at(0) == 104){
                currentPoint.xCoordinate += actualNumber;
                pPathPoints.push_back(currentPoint);
            }
            else if(copyCurrentPointString.at(0) == 86){
                currentPoint.yCoordinate = actualNumber;
                pPathPoints.push_back(currentPoint);
            }
            else{
                currentPoint.yCoordinate += actualNumber;
                pPathPoints.push_back(currentPoint);
            }

        }
    }
    return currentPoint;
}

/*
-----------------------------------------------------------------------------
This function reads the case when we have a C
    Parameters: The string of the attribute d of a path and the vector
                of points in the current path
    Return: the current point
-----------------------------------------------------------------------------
*/
PointInPath specialCaseC(string currentPointString, vector<PointInPath> &pPathPoints){
    PointInPath currentPoint;
    string copyCurrentPointString = currentPointString;

    if(pPathPoints.size() > 0){
        if(currentPointString.at(0) == 99){
            PointInPath lastPoint;
            lastPoint = pPathPoints.back();

            currentPoint.xCoordinate = lastPoint.xCoordinate;
            currentPoint.yCoordinate = lastPoint.yCoordinate;
        }
    }
    
    currentPoint.svgCommand = currentPointString[0];
    currentPointString.erase(0,1);
    string actualNumberString;
    stringstream input_stringstream(currentPointString); 

    float actualNumber = 0;
    int currentPosition = 0;

    while(getline(input_stringstream, actualNumberString, ' ')){  
        if (actualNumberString.length() > 0){
            actualNumber = stof(actualNumberString);
            if (copyCurrentPointString.at(0) == 67){
                currentPosition++;
                if(currentPosition == 5){
                    currentPoint.xCoordinate = actualNumber;
                }
                if(currentPosition == 6){
                    currentPoint.yCoordinate = actualNumber;
                    pPathPoints.push_back(currentPoint);
                    currentPosition = 0;
                }
            }
            else{
                currentPosition++;
                if(currentPosition == 5){
                    currentPoint.xCoordinate += actualNumber;
                }
                if(currentPosition == 6){
                    currentPoint.yCoordinate += actualNumber;
                    pPathPoints.push_back(currentPoint);
                    currentPosition = 0;
                }
            }

        }
    }
    return currentPoint;
}

/*
-----------------------------------------------------------------------------
This function reads the case when we have a ML
    Parameters: The string of the attribute d of a path and the vector
                of points in the current path
    Return: the current point
-----------------------------------------------------------------------------
*/
PointInPath specialCaseML(string currentPointString, vector<PointInPath> &pPathPoints){
    PointInPath currentPoint;
    currentPoint.xCoordinate = 0;
    currentPoint.yCoordinate = 0;
    string copyCurrentPointString = currentPointString;

    if(pPathPoints.size() > 0){
        if(currentPointString.at(0) == 108){
            PointInPath lastPoint;
            lastPoint = pPathPoints.back();
            currentPoint.xCoordinate = lastPoint.xCoordinate;
            currentPoint.yCoordinate = lastPoint.yCoordinate;
        }
    }
    // Assign the comand to the point
    currentPoint.svgCommand = currentPointString[0];

    // Deletes the first part (The letter)
    currentPointString.erase(0,1);

    string actualNumberString;
    stringstream input_stringstream(currentPointString); 
    float actualNumber = 0;

    int isCoordXorY = 0;

    while(getline(input_stringstream, actualNumberString, ' ')){ 
        if (actualNumberString.length() > 0){

            actualNumber = stof(actualNumberString);
            isCoordXorY++;
            if ((copyCurrentPointString.at(0) == 76) || (copyCurrentPointString.at(0) == 77)){
                if(isCoordXorY == 1){
                    currentPoint.xCoordinate = actualNumber;
                }
                else if(isCoordXorY == 2){
                    currentPoint.yCoordinate = actualNumber;
                    pPathPoints.push_back(currentPoint);
                    isCoordXorY = 0;
                }
            }
            else{
                if(isCoordXorY == 1){
                    currentPoint.xCoordinate += actualNumber;
                }
                else if(isCoordXorY == 2){
                    currentPoint.yCoordinate += actualNumber;
                    pPathPoints.push_back(currentPoint);
                    isCoordXorY = 0;
                }
            }
        }
    }
    return currentPoint;
}

/*
-----------------------------------------------------------------------------
This function reads the rest of cases
    Parameters: The string of the attribute d of a path and the vector
                of points in the current path
    Return: the current point
-----------------------------------------------------------------------------
*/
PointInPath parsePoint(string currentPointString, vector<PointInPath> pPathPoints){
    PointInPath currentPoint;

    string copyCurrentPointString = currentPointString;

    currentPoint.svgCommand = currentPointString[0];
    copyCurrentPointString.erase(0,1);

    string actualNumberString;  //string lectura;
    stringstream input_stringstream(copyCurrentPointString); 

    bool isCoordinateX = 1;
    float actualNumber = 0;

    while(getline(input_stringstream, actualNumberString, ' ')){  
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
        if(pPathPoints.size() > 0){
            if ((currentPointString.at(0) >= 97) && (currentPointString.at(0) <= 122)) {
                PointInPath lastPoint;
                lastPoint = pPathPoints.back();
                currentPoint.xCoordinate += lastPoint.xCoordinate;
                currentPoint.yCoordinate += lastPoint.yCoordinate;
            }
        }
    return currentPoint;
}

/*
-----------------------------------------------------------------------------
This function decompose-> calls the other funtions for reading
    Parameters: The string with the points in the svg and a vector
                with the path points
    Return: the vector with the new points
-----------------------------------------------------------------------------
*/
vector<PointInPath> decomposeString(string pPointsSvg, vector<PointInPath> pPathPoints) {
    int initialPosition = 0;
    int finalPosition = 0;   //last position
    int flagIgnoreFirst = 0;  //flag for ignore the firt if
    PointInPath currentPoint;

    int pPointsSvgLenght = pPointsSvg.length();
    string pPointsSvgCopy;


    for (int indexInString = 0; indexInString < pPointsSvgLenght; indexInString++){
        //Replace al the "," for " "
        if(pPointsSvg.at(indexInString) == 44){
            pPointsSvg.replace(indexInString, 1, " ");
        }
        finalPosition = indexInString;
        // if the string[indexInString] is a letter (capital or lowercase)
        if(pPointsSvg.at(indexInString) >= 65 &&  pPointsSvg.at(indexInString) <= 122){

            if(flagIgnoreFirst != 0){
                pPointsSvgCopy = pPointsSvg.substr(initialPosition, finalPosition-initialPosition);

                if(pPointsSvgCopy.at(1) != 32){
                    pPointsSvgCopy.insert(1, " ");
                }

                pPointsSvgCopy = normalizePath(pPointsSvgCopy);

                // Special case-> Its an M
                if((pPointsSvgCopy.at(0) == 77 || pPointsSvgCopy.at(0) == 109) || (pPointsSvgCopy.at(0) == 76 || pPointsSvgCopy.at(0) == 108)){
                    specialCaseML(pPointsSvgCopy, pPathPoints);
                }
                else if(pPointsSvgCopy.at(0) == 67 || pPointsSvgCopy.at(0) == 99){
                    specialCaseC(pPointsSvgCopy, pPathPoints);
                }
                else if((pPointsSvgCopy.at(0) == 72 || pPointsSvgCopy.at(0) == 104) || (pPointsSvgCopy.at(0) == 86 || pPointsSvgCopy.at(0) == 118)){
                    specialCaseHV(pPointsSvgCopy, pPathPoints);
                }
                else{
                    currentPoint = parsePoint(pPointsSvgCopy, pPathPoints);
                    pPathPoints.push_back(currentPoint);
                }
            }
            initialPosition = indexInString;
            flagIgnoreFirst ++;
        }
    }
    //Special case 1: The path doesnt end in Z or z
    if((pPointsSvg.at(pPointsSvgLenght-1) != 90) && (pPointsSvg.at(pPointsSvgLenght-1) != 122)){
        pPointsSvgCopy = pPointsSvg.substr(initialPosition, (finalPosition-initialPosition)+1);
        currentPoint = parsePoint(pPointsSvgCopy, pPathPoints);
        pPathPoints.push_back(currentPoint);
    }
    return pPathPoints;
}

/*
________________________________________________________________________________________________________
Class Path
    This class is use to save the information when we do the reading of the svg
    Attributes: string: identifier ->This is use to save the id of the svg
                string: pathColor
                vector<PointInPath>: pathPoints
                string: pathStyle
                string: otherInformation 
                float: maxQuadrantPoint
                float: minQuadrantPoint
                vector<PointInPath>: Coincidence points
    Methods: sets and gets
             to string
________________________________________________________________________________________________________
*/
class Path{
    private:
        //Attributes
        string identifier;
        string pathColor;
        vector<PointInPath> pathPoints;
        string pathStyle;
        string otherInformation;
        int positionInPath;
        float maxQuadrantPoint[2];
        float minQuadrantPoint[2];
        vector<PointInPath> coincidencePoints;

    public:
        //Methods
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

        }

        vector<PointInPath> getPathPoints() {
            return pathPoints;
        }

        PointInPath getPathPoints(int indexOfPoint) {
            return pathPoints.at(indexOfPoint);
        }

        void setPathStyle(string pStyle) {
            pathStyle = pStyle;
        }

        string getPathStyle() {
            return pathStyle;
        }

        /*
        -----------------------------------------------------------------------------
        This function sets the maximun and minimum points 
            Parameters: None
            Return: None
        -----------------------------------------------------------------------------
        */
        void setQuadrantPoints(){
            float maxXCoord;
            float maxYCoord;
            float minXCoord;
            float minYCoord;

            for(int currentPointIndex = 0; currentPointIndex < pathPoints.size(); currentPointIndex++){
                if(currentPointIndex == 0){
                    maxXCoord = pathPoints.at(currentPointIndex).xCoordinate;
                    maxYCoord = pathPoints.at(currentPointIndex).yCoordinate;
                    minXCoord = maxXCoord;
                    minYCoord = maxYCoord;

                } else{
                    if(maxXCoord < pathPoints.at(currentPointIndex).xCoordinate){
                        maxXCoord = pathPoints.at(currentPointIndex).xCoordinate;
                    } else if ( maxYCoord < pathPoints.at(currentPointIndex).yCoordinate){
                        maxYCoord = pathPoints.at(currentPointIndex).yCoordinate;
                    }

                    if( minXCoord > pathPoints.at(currentPointIndex).xCoordinate){
                        minXCoord = pathPoints.at(currentPointIndex).xCoordinate;
                    } else if(minYCoord > pathPoints.at(currentPointIndex).yCoordinate ){
                        //cout << "Y= " << pathPoints.at(currentPointIndex).yCoordinate << endl;
                        minYCoord = pathPoints.at(currentPointIndex).yCoordinate;
                    }
                }

            } //end for
            maxQuadrantPoint[0] = maxXCoord ;
            maxQuadrantPoint[1] = maxYCoord;

            minQuadrantPoint[0] = minXCoord;
            minQuadrantPoint[1] = minYCoord;
        }

        void addCoincidencePoint(PointInPath pCoincidencePoint) {
            coincidencePoints.push_back(pCoincidencePoint);
        }

        vector<PointInPath> getCoincidencePoints() {
            return coincidencePoints;
        }

        PointInPath getCoincidencePoints(int pIndexOfPoint) {
            return coincidencePoints.at(pIndexOfPoint);
        }

        PointInPath getVectorOffMovs(int pIndexOfPoint) {
            return coincidencePoints.at(pIndexOfPoint);
        }
        

        void modifyPointInPath(PointInPath pCoincidencePoint, int pPointPosition){
            coincidencePoints.at(pPointPosition) = pCoincidencePoint;
        }

       
        float getMaxQuadrantCoordX(){
            return maxQuadrantPoint[0];
        }

        float getMaxQuadrantCoordY(){
            return maxQuadrantPoint[1];
        }

        float getMinQuadrantCoordX(){
            return minQuadrantPoint[0];
        }

        float getMinQuadrantCoordY(){
            return minQuadrantPoint[1];
        }

        void toString(){
            cout << "Id: " << identifier << "\nColor: " << pathColor << "\nPoints: " ;
            for(int indexOfCurrentPoint = 0; indexOfCurrentPoint < pathPoints.size(); indexOfCurrentPoint++){
                cout << "\t Command: " << pathPoints.at(indexOfCurrentPoint).svgCommand << " - (" ;
                cout << pathPoints.at(indexOfCurrentPoint).xCoordinate << ", " << pathPoints.at(indexOfCurrentPoint).yCoordinate;
                cout << ")" << endl;
            }
            cout << "\nPosition: " << positionInPath << "\nStyle: " << pathStyle <<endl;
            cout << "Coincidence Points: " ;
            for(int indexOfCurrentCoincidencePoint = 0; indexOfCurrentCoincidencePoint < coincidencePoints.size(); indexOfCurrentCoincidencePoint++){
                // cout << "X: " << coincidencePoints.at(indexOfCurrentCoincidencePoint)[0] << " Y: " << coincidencePoints.at(indexOfCurrentCoincidencePoint)[1] << endl;
                cout << "X: " << coincidencePoints.at(indexOfCurrentCoincidencePoint).xCoordinate << " Y: " << coincidencePoints.at(indexOfCurrentCoincidencePoint).yCoordinate << endl;

            }
        }
};

#endif
