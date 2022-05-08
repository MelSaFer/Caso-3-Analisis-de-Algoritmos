//Libraries ---------------------------------------------------------------------------------------------

#ifndef ROUTING
#define ROUTING
#include <stdio.h>      
#include <stdlib.h>    
#include <iostream>
#include <vector>
#include <list>
#include <thread>
#include <cmath>
#include "Path.h"
#include "ObserverPattern.h"

using namespace std;

/*
________________________________________________________________________________________________________
Class Routing
    This class is used to calculate the movement points of the paths
    Attributes: int:ClassId  
                list<Observers>:ObserverList
    Methods: attach
             detach
             notify
             getClassId
             calculateEndPoint
             routingPrerocess
             routingProcess
________________________________________________________________________________________________________
*/

class Routing {
    private:
        static const int ClassId = 1;
        list<Observer*> ObserversList;

        vector <float*> movementPoints;

    public:
        // int getClassId(){
        //     return ClassId;
        // }

        // void attach(Observer* pNewObserver) {
        //     ObserversList.emplace_back(pNewObserver);
        // }

        // void detach(Observer* pObserverDelete) {
        //     ObserversList.remove(pObserverDelete);
        // }

        // void notify(void* pClassId) {
        //     for (Observer* currentObserver: ObserversList) {
        //         thread t(&Observer::update, currentObserver, pClassId); // parametros = (direccionDeMetodo, instancia/objeto, parametro)
        //         t.join(); // espere a que t termine
        //     }
        // }
        //



        /* This function calculates the final (x,y) point for each selected point after making its 
        displacement.
        Entries: the PointInPath that contains the initial coordinates; the svg size and the radians
        Output: the (x,y) coordinate

        n = a point in path
        O(n) = n;
        */
        float* calculateEndPoint (PointInPath pPathCoordinates, float pSvgLenght, float pSvgWidth, float pRadians){
            float* endPoint = new float[2]; 
            bool itsSpecialCase = false;
            // current point 
            float coordenateX = pPathCoordinates.xCoordinate;
            float coordenateY = pPathCoordinates.yCoordinate;
            float degrees = pRadians * (180/M_PI); // convert de radians to degrees

            if(degrees == 0 || degrees == 360){ // Special cases (when the degrees are 0, 90, 180, 270, 360)
                coordenateX = pSvgLenght;
                itsSpecialCase = true;}
            else if(degrees == 90){
                coordenateY == 0;
                itsSpecialCase = true;}
            else if(degrees == 180){
                coordenateX == 0;
                itsSpecialCase = true;}
            else if(degrees == 270){
                coordenateY = pSvgWidth;
                itsSpecialCase = true;}
            if(itsSpecialCase){
                endPoint[0] = coordenateX;
                endPoint[1] = coordenateY;
                cout << "Special case of degrees" << endl;
                return endPoint;}
            else{
                float lineSlope = tan(degrees*M_PI/180);
                // Case 1: when 0 < degrees < 90
                if (degrees> 0 && degrees < 90){
                    float newCoordenateX = -(pSvgLenght-coordenateX);
                    float newCoordenateY = -coordenateY;

                    float coincidenceY = -(lineSlope*(-newCoordenateX)+newCoordenateY);
                    float coincidenceX = pSvgLenght + (coincidenceY/lineSlope);

                    if(coincidenceX >= pSvgLenght){
                        coincidenceX = pSvgLenght;}
                    if(coincidenceY <= 0){
                        coincidenceY = 0;}
                        // cout << "degrees: " << degrees << endl;
                    cout << "Case1/the point touches the edge at: " << coincidenceX << ", " << coincidenceY << endl;
                    endPoint[0] = coincidenceX;
                    endPoint[1] = coincidenceY;
                }
                // Case 2: when 90 < degrees < 180
                else if (degrees > 90 && degrees < 180){
                    float newCoordenateY = -coordenateY;

                    float coincidenceY = -(lineSlope*(-coordenateX)+newCoordenateY);
                    float coincidenceX = ((coincidenceY)/lineSlope);

                    if(coincidenceX >= pSvgLenght || coincidenceX <= 0){
                        coincidenceX = 0;}
                    if(coincidenceY <= 0){
                        coincidenceY = 0;}
                    cout << "Case2/the point touches the edge at: " << coincidenceX << ", " << coincidenceY << endl;
                    endPoint[0] = coincidenceX;
                    endPoint[1] = coincidenceY;
                }
                // Case 3: when 180 < degrees < 270
                else if (degrees > 180 && degrees < 270){
                    degrees -= 180;
                    lineSlope = tan(degrees*M_PI/180);
                    float newCoordenateY = pSvgWidth - coordenateY;

                    float coincidenceY = (lineSlope*(-coordenateX))+newCoordenateY;
                    float coincidenceX = ((-coincidenceY)/lineSlope);
                    coincidenceY = pSvgWidth - coincidenceY;

                    if(coincidenceY <= 0 || coincidenceY >= pSvgWidth){
                        coincidenceY = pSvgWidth;}
                    if(coincidenceX <= 0 || coincidenceX >= pSvgLenght){
                        coincidenceX = 0;}
                    cout << "Case3/ the point touches the edge at: " << coincidenceX << ", " << coincidenceY << endl;
                    endPoint[0] = coincidenceX;
                    endPoint[1] = coincidenceY;
                }
                // Case 4: when 270 < degrees < 360
                else if (degrees > 270 && degrees < 360){
                    degrees -= 180;
                    lineSlope = tan(degrees*M_PI/180);
                    float newCoordenateY = pSvgWidth - coordenateY;
                    float newCoordenateX = -(pSvgLenght - coordenateX);

                    float coincidenceY = (lineSlope*(-newCoordenateX))+newCoordenateY;
                    float coincidenceX = ((-coincidenceY)/lineSlope);
                    coincidenceY = pSvgWidth - coincidenceY;
                    coincidenceX = pSvgLenght + coincidenceX;

                    if(coincidenceY <= 0 || coincidenceY >= pSvgWidth){
                        coincidenceY = pSvgWidth;}
                    if(coincidenceX <= 0 || coincidenceX >= pSvgLenght){
                        coincidenceX = 100;}
                    cout << "Case4/ the point touches the edge at: " << coincidenceX << ", " << coincidenceY << endl;
                    endPoint[0] = coincidenceX;
                    endPoint[1] = coincidenceY;
                }
            }    
        return endPoint;    
    }

    /* Pre routing process
            n = the vector of selected paths
            O(n) = n * p
    */

   //-----------------------------------------------------------------------------
        //Parameters: the coincidence point, the svg sizes, the radians and the frames
        //Return: the vecctor of modified paths with their SOLUTION VECTORS.
    //-----------------------------------------------------------------------------

    vector<Path*> routingPreProcess(float radianes, vector<Path*> pSelectedPaths, float pSvgLenght, float pSvgWidth, int pFrames){
        cout << "====================" << endl;
        cout << "Routing process" << endl;
        cout << "====================" << endl;
        int pathPosition, coincidencePointPosition;

        // go through the n
        for (pathPosition = 0; pathPosition < pSelectedPaths.size(); pathPosition++){ 

            // go through the coincidence points
            for(coincidencePointPosition = 0; coincidencePointPosition < pSelectedPaths.at(pathPosition)->getCoincidencePoints().size(); coincidencePointPosition++){
                pSelectedPaths.at(pathPosition)->modifyPointInPath(\
                this->routingProcess(pSelectedPaths.at(pathPosition)->getCoincidencePoints(coincidencePointPosition), pSvgLenght, pSvgWidth, radianes, pFrames), \
                coincidencePointPosition);

                cout << "Quantity of path movements: " << (pSelectedPaths.at(pathPosition)->getCoincidencePoints(coincidencePointPosition).offsetPoints.size()) / 2 << endl;
                cout << "===" << endl;
            }           
        }
        return pSelectedPaths;
    }

    /*
    -> BACKTRACKING
            n = the vector of svg paths
            SOLUTION VECTOR (implicit): list of animation points, discarding those that do not generate significant movements
            PODA: with the final point calculated, the distance between the start and the end is calculated and 
                divided by the number of frames, so only the necessary points will be made.
            O(n) = n * p
    */ 

    //-----------------------------------------------------------------------------
        //Parameters: the coincidence point, the svg sizes, the radians and the frames
        //Return: the modified coincidence Point with the SOLUTION VECTOR
    //-----------------------------------------------------------------------------
    PointInPath routingProcess (PointInPath coincidencePoint, float pSvgLenght, float pSvgWidth, float radianes, int pFrames){
        float grados = radianes * (180/M_PI);
        float nextMove[2] = {coincidencePoint.xCoordinate, coincidencePoint.yCoordinate};

        float *final = {this->calculateEndPoint(coincidencePoint, pSvgLenght, pSvgWidth, radianes)};

        // distance between the initial and the end point
        float distanceBetweenPoints = sqrt(pow(coincidencePoint.xCoordinate - final[0], 2) + pow(coincidencePoint.yCoordinate - final[1], 2));
        
        /*
        PODA
            The (distance / frames) is the movement distance, this avoids making unnecessary calculations
            If the distance is very little, the distance is going to be 10
        */
        float movementDistance = distanceBetweenPoints/pFrames;

        if(movementDistance < 10){
            movementDistance = 10;
        }

        // How much does it move X and Y
        float xMovement = ( movementDistance * abs(coincidencePoint.xCoordinate - final[0]) ) / distanceBetweenPoints;
        float yMovement = ( movementDistance * abs(coincidencePoint.yCoordinate - final[1]) ) / distanceBetweenPoints;

        // Case 1; first quadrant
        if (grados >= 0 && grados <= 90){
            cout << "First quadrant" << endl;
            while ((nextMove[0] >= 0 && nextMove[0] <= pSvgLenght) && (nextMove[1] >= 0 && nextMove[1] <= pSvgWidth)){
                coincidencePoint.offsetPoints.push_back(nextMove[0]);
                coincidencePoint.offsetPoints.push_back(nextMove[1]);
                cout << "NEXT: " << nextMove[0] << ", " << nextMove[1] << endl;
                nextMove[0] += xMovement;
                nextMove[1] -= yMovement;
                nextMove[0] = floorf(nextMove[0]*100000) / 100000;
                nextMove[1] = floorf(nextMove[1]*100000) / 100000;
            }
        }

        // Case 2; second quadrant
        if (grados >90 && grados <= 180){
            cout << "Second quadrant" << endl;
            while ((nextMove[0] >= 0 && nextMove[0] <= pSvgLenght) && (nextMove[1] >= 0 && nextMove[1] <= pSvgWidth)){
                coincidencePoint.offsetPoints.push_back(nextMove[0]);
                coincidencePoint.offsetPoints.push_back(nextMove[1]);
                cout << "NEXT: " << nextMove[0] << ", " << nextMove[1] << endl;
                nextMove[0] -= xMovement;
                nextMove[1] -= yMovement;
                nextMove[0] = floorf(nextMove[0]*100000) / 100000;
                nextMove[1] = floorf(nextMove[1]*100000) / 100000;
            }
        }

        // Case 3; third quadrant
        if (grados >180 && grados <= 270){
            cout << "Third quadrant" << endl;
            while ((nextMove[0] >= 0 && nextMove[0] <= pSvgLenght) && (nextMove[1] >= 0 && nextMove[1] <= pSvgWidth)){
                coincidencePoint.offsetPoints.push_back(nextMove[0]);
                coincidencePoint.offsetPoints.push_back(nextMove[1]);
                cout << "NEXT: " << nextMove[0] << ", " << nextMove[1] << endl;
                nextMove[0] -= xMovement;
                nextMove[1] += yMovement;
                nextMove[0] = floorf(nextMove[0]*100000) / 100000;
                nextMove[1] = floorf(nextMove[1]*100000) / 100000;
            }
        }

        // Case 4; fourth quadrant
        if (grados > 270 && grados <= 360){
            cout << "Fourth quadrant" << endl;
            while ((nextMove[0] >= 0 && nextMove[0] <= pSvgLenght) && (nextMove[1] >= 0 && nextMove[1] <= pSvgWidth)){
                coincidencePoint.offsetPoints.push_back(nextMove[0]);
                coincidencePoint.offsetPoints.push_back(nextMove[1]);
                cout << "NEXT: " << nextMove[0] << ", " << nextMove[1] << endl;
                nextMove[0] += xMovement;
                nextMove[1] += yMovement;
                nextMove[0] = floorf(nextMove[0]*100000) / 100000;
                nextMove[1] = floorf(nextMove[1]*100000) / 100000;
            }
        }
        return coincidencePoint;
    }

};

#endif