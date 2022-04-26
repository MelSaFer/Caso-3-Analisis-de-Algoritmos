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

string normalizePath(string currentPointString){

    string normalizedString;

    for(int currentLetter = 0; currentLetter < currentPointString.length(); currentLetter++){
        if(currentPointString.at(currentLetter) == 45){
            normalizedString += " ";
            
        }
        normalizedString += currentPointString[currentLetter];
    }

    //cout << normalizedString << endl;
    return normalizedString;   
}

PointInPath specialCaseC(string currentPointString, vector<PointInPath> &pPathPoints){
    //cout << "\n-------> " << currentPointString << endl;
    PointInPath currentPoint;
    string copyCurrentPointString = currentPointString;   

    if(pPathPoints.size() > 0){
        if(currentPointString.at(0) == 99){
            PointInPath lastPoint;
            lastPoint = pPathPoints.back(); 

            currentPoint.xCoordinate = lastPoint.xCoordinate;
            currentPoint.yCoordinate = lastPoint.yCoordinate;

           // cout << "Coordenada anterior = (" << currentPoint.xCoordinate << ", " << currentPoint.yCoordinate << ")" << endl;
        }
    }
    // asignacion de que es m
    currentPoint.svgCommand = currentPointString[0];
    // se borra el m
    currentPointString.erase(0,1);  
    //string lectura; 
    string actualNumberString;  
    stringstream input_stringstream(currentPointString);  //stringstream input_stringstream(cadena); 

    float actualNumber = 0;

    int contadorSeis = 0;

    while(getline(input_stringstream, actualNumberString, ' ')){  //while (getline(input_stringstream, lectura, ' ')){
        
        if (actualNumberString.length() > 0){

            if (copyCurrentPointString.at(0) == 67){
                actualNumber = stof(actualNumberString);
                contadorSeis++;
                if(contadorSeis == 5){
                    currentPoint.xCoordinate = actualNumber;
                }
                if(contadorSeis == 6){
                    currentPoint.yCoordinate = actualNumber;
                    pPathPoints.push_back(currentPoint);
                    contadorSeis = 0;
                   // cout << "Coordenada de C = (" << currentPoint.xCoordinate << ", " << currentPoint.yCoordinate << ")" << endl;
                }
            }
            else{
                //cout << "Es minuscula" << endl;
                actualNumber = stof(actualNumberString);
                contadorSeis++;
                if(contadorSeis == 5){
                    currentPoint.xCoordinate += actualNumber;
                }
                if(contadorSeis == 6){
                    currentPoint.yCoordinate += actualNumber;
                    pPathPoints.push_back(currentPoint);
                    contadorSeis = 0;
                    //cout << "Coordenada de c = (" << currentPoint.xCoordinate << ", " << currentPoint.yCoordinate << ")" << endl;
                }
            }
            
        }
    }
    //cout << "Xc= " << currentPoint.xCoordinate << " Y: " << currentPoint.yCoordinate << endl;
    return currentPoint;
}


PointInPath specialCaseML(string currentPointString, vector<PointInPath> &pPathPoints){
    //cout << "\n-------> " << currentPointString << endl;
    PointInPath currentPoint;
    string copyCurrentPointString = currentPointString;
    
    if(pPathPoints.size() > 0){
        if(currentPointString.at(0) == 108){
            PointInPath lastPoint;
            lastPoint = pPathPoints.back(); 

            currentPoint.xCoordinate = lastPoint.xCoordinate;
            currentPoint.yCoordinate = lastPoint.yCoordinate;
        }
    }
    
    
    // asignacion de que es m
    currentPoint.svgCommand = currentPointString[0];

    // se borra el m
    currentPointString.erase(0,1);
    
    //string lectura; 
    string actualNumberString;  
    stringstream input_stringstream(currentPointString);  //stringstream input_stringstream(cadena); 

    float actualNumber = 0;

    int contadorPareja = 0;

    while(getline(input_stringstream, actualNumberString, ' ')){  //while (getline(input_stringstream, lectura, ' ')){
        if (actualNumberString.length() > 0){

            actualNumber = stof(actualNumberString);
            contadorPareja++;
            if (copyCurrentPointString.at(0) == 76 || copyCurrentPointString.at(0) == 77){
                if(contadorPareja == 1){
                    currentPoint.xCoordinate = actualNumber;
                }
                if(contadorPareja == 2){
                    currentPoint.yCoordinate = actualNumber;
                    //cout << "Coordenada de m = (" << currentPoint.xCoordinate << ", " << currentPoint.yCoordinate << ")" << endl;
                    pPathPoints.push_back(currentPoint);
                    contadorPareja = 0;
                }
            }
            else{
                if(contadorPareja == 1){
                    currentPoint.xCoordinate += actualNumber;
                }
                if(contadorPareja == 2){
                    currentPoint.yCoordinate += actualNumber;
                    //cout << "Coordenada de m = (" << currentPoint.xCoordinate << ", " << currentPoint.yCoordinate << ")" << endl;
                    pPathPoints.push_back(currentPoint);
                    contadorPareja = 0;
                }
            } 
        }
    }
    //cout << "X= " << currentPoint.xCoordinate << " Y: " << currentPoint.yCoordinate << endl
    return currentPoint;
}

PointInPath parsePoint(string currentPointString, vector<PointInPath> pPathPoints){
    //cout << "\n-------> " << currentPointString << endl;
    PointInPath currentPoint;

    string copyCurrentPointString = currentPointString;

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
    if(pPathPoints.size() > 0){
        if (copyCurrentPointString.at(0) >= 97 && copyCurrentPointString.at(0) <= 122) {
            PointInPath lastPoint;
            lastPoint = pPathPoints.back();
            currentPoint.xCoordinate += lastPoint.xCoordinate;
            currentPoint.yCoordinate += lastPoint.yCoordinate;
        }
    }
    //cout << "X= " << currentPoint.xCoordinate << " Y: " << currentPoint.yCoordinate << endl;
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
        // if the string[indexInString] is a letter (capital or lowercase)
        if(pPointsSvg.at(indexInString) >= 65 &&  pPointsSvg.at(indexInString) <= 122){

            if(flagIgnoreFirst != 0){
                pPointsSvgCopy = pPointsSvg.substr(initialPosition, finalPosition-initialPosition);
                //Variables for reading the numbers in the string of the currentPoint
                
                if(pPointsSvgCopy.at(1) != 32){
                    pPointsSvgCopy.insert(1, " ");
                }

                pPointsSvgCopy = normalizePath(pPointsSvgCopy);

                // cout << "\n------->" <<  pPointsSvgCopy << endl;
                // caso especial cuando es m
                if(pPointsSvgCopy.at(0) == 77 || pPointsSvgCopy.at(0) == 109 || pPointsSvgCopy.at(0) == 76 || pPointsSvgCopy.at(0) == 108){
                    specialCaseML(pPointsSvgCopy, pPathPoints);
                }
                else if(pPointsSvgCopy.at(0) == 67 || pPointsSvgCopy.at(0) == 99){
                    specialCaseC(pPointsSvgCopy, pPathPoints);
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
    if(pPointsSvg.at(pPointsSvgLenght-1) != 90 && pPointsSvg.at(pPointsSvgLenght-1) != 122){
        pPointsSvgCopy = pPointsSvg.substr(initialPosition, (finalPosition-initialPosition)+1);
        currentPoint = parsePoint(pPointsSvgCopy, pPathPoints);
        pPathPoints.push_back(currentPoint);
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
        float maxQuadrantPoint[2];
        float minQuadrantPoint[2];

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

        void setQuadrantPoints(){
            float maxXCoord;
            float maxYCoord;
            float minXCoord;
            float minYCoord;
            float quadrantMarginError = 5.0;

            for(int currentPointIndex = 0; currentPointIndex < pathPoints.size(); currentPointIndex++){
                if(currentPointIndex == 0){
                    maxXCoord = pathPoints.at(currentPointIndex).xCoordinate;
                    maxYCoord = pathPoints.at(currentPointIndex).yCoordinate;
                    minXCoord = maxXCoord;
                    minYCoord = maxYCoord;

                } else{
                    if(maxXCoord < pathPoints.at(currentPointIndex).xCoordinate){
                        maxXCoord = pathPoints.at(currentPointIndex).xCoordinate;
                    } else if (maxYCoord < pathPoints.at(currentPointIndex).yCoordinate){
                        maxYCoord = pathPoints.at(currentPointIndex).yCoordinate;
                    } 

                    if( minXCoord > pathPoints.at(currentPointIndex).xCoordinate){
                        minXCoord = pathPoints.at(currentPointIndex).xCoordinate;
                    } else if(minYCoord > pathPoints.at(currentPointIndex).yCoordinate){
                        //cout << "Y= " << pathPoints.at(currentPointIndex).yCoordinate << endl;
                        minYCoord = pathPoints.at(currentPointIndex).yCoordinate;
                    }
                }

            } //end for

            maxQuadrantPoint[0] = maxXCoord + quadrantMarginError;
            maxQuadrantPoint[1] = maxYCoord + quadrantMarginError;
            
            minQuadrantPoint[0] = minXCoord - quadrantMarginError;
            minQuadrantPoint[1] = minYCoord - quadrantMarginError;

            //cout << "MX= " << maxQuadrantPoint[0] << " MY= " << maxQuadrantPoint[1] << " mX= " << minQuadrantPoint[0] << " mY= " << minQuadrantPoint[1] << endl;

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