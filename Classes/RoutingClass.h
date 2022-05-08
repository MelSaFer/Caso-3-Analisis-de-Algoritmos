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

class Routing {
    private:
        //Paths selecionados
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

        /* This function calculates the final (x,y) point for each selectecct point after making its 
        displacement.
        Entries: the PointInPath that contains the initial coordinates; the svg size and the radians
        Output: the (x,y) coordinate
        */
        float* calculateEndPoint (PointInPath pPathCoordinates, float pSvgLenght, float pSvgWidth, float pRadians){
            // cout << "Funcion de punto final" << endl;
            float* endPoint = new float[2]; 
            bool itsSpecialCase = false;
            // current point
            float coordenateX = pPathCoordinates.xCoordinate;
            float coordenateY = pPathCoordinates.yCoordinate;
            float degrees = pRadians * (180/M_PI);

            if(degrees == 0 || degrees == 360){ // Special cases
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
                cout << "caso especial de degrees" << endl;
                return endPoint;}
            else{
                float pendiente = tan(degrees*M_PI/180);
                // Case 1: when 0 < degrees < 90
                if (degrees> 0 && degrees < 90){
                    float newCoordenateX = -(pSvgLenght-coordenateX);
                    float newCoordenateY = -coordenateY;

                    float coincidenceY = -(pendiente*(-newCoordenateX)+newCoordenateY);
                    float coincidenceX = pSvgLenght + (coincidenceY/pendiente);

                    if(coincidenceX >= pSvgLenght){
                        coincidenceX = pSvgLenght;}
                    if(coincidenceY <= 0){
                        coincidenceY = 0;}
                        cout << "degrees: " << degrees << endl;
                    cout << "Caso1/El punto en el que toca el borde es: " << coincidenceX << ", " << coincidenceY << endl;
                    endPoint[0] = coincidenceX;
                    endPoint[1] = coincidenceY;
                }
                // Case 2: when 90 < degrees < 180
                else if (degrees > 90 && degrees < 180){
                    float newCoordenateY = -coordenateY;

                    float coincidenceY = -(pendiente*(-coordenateX)+newCoordenateY);
                    float coincidenceX = ((coincidenceY)/pendiente);

                    if(coincidenceX >= pSvgLenght || coincidenceX <= 0){
                        coincidenceX = 0;}
                    if(coincidenceY <= 0){
                        coincidenceY = 0;}
                    cout << "Caso2/El punto en el que toca el borde es: " << coincidenceX << ", " << coincidenceY << endl;
                    endPoint[0] = coincidenceX;
                    endPoint[1] = coincidenceY;
                }
                // Case 3: when 180 < degrees < 270
                else if (degrees > 180 && degrees < 270){
                    degrees -= 180;
                    pendiente = tan(degrees*M_PI/180);
                    float newCoordenateY = pSvgWidth - coordenateY;

                    float coincidenceY = (pendiente*(-coordenateX))+newCoordenateY;
                    float coincidenceX = ((-coincidenceY)/pendiente);
                    coincidenceY = pSvgWidth - coincidenceY;

                    if(coincidenceY <= 0 || coincidenceY >= pSvgWidth){
                        coincidenceY = pSvgWidth;}
                    if(coincidenceX <= 0 || coincidenceX >= pSvgLenght){
                        coincidenceX = 0;}
                    cout << "Caso3/ El punto en el que toca el borde es: " << coincidenceX << ", " << coincidenceY << endl;
                    endPoint[0] = coincidenceX;
                    endPoint[1] = coincidenceY;
                }
                // Case 4: when 270 < degrees < 360
                else if (degrees > 270 && degrees < 360){
                    degrees -= 180;
                    pendiente = tan(degrees*M_PI/180);
                    float newCoordenateY = pSvgWidth - coordenateY;
                    float newCoordenateX = -(pSvgLenght - coordenateX);

                    float coincidenceY = (pendiente*(-newCoordenateX))+newCoordenateY;
                    float coincidenceX = ((-coincidenceY)/pendiente);
                    coincidenceY = pSvgWidth - coincidenceY;
                    coincidenceX = pSvgLenght + coincidenceX;

                    if(coincidenceY <= 0 || coincidenceY >= pSvgWidth){
                        coincidenceY = pSvgWidth;}
                    if(coincidenceX <= 0 || coincidenceX >= pSvgLenght){
                        coincidenceX = 100;}
                    cout << "Caso4/ El punto en el que toca el borde es: " << coincidenceX << ", " << coincidenceY << endl;
                    endPoint[0] = coincidenceX;
                    endPoint[1] = coincidenceY;
                }
            }    
        return endPoint;    
    }

    /* Routing process


    */

    vector<Path*> routingPreProcess(float radianes, vector<Path*> pSelectedPaths, float pSvgLenght, float pSvgWidth, int pFrames){
        int pathPosition, coincidencePointPosition;
        for (pathPosition = 0; pathPosition < pSelectedPaths.size(); pathPosition++){ // go through the n

            for(coincidencePointPosition = 0; coincidencePointPosition < pSelectedPaths.at(pathPosition)->getCoincidencePoints().size(); coincidencePointPosition++){
                pSelectedPaths.at(pathPosition)->modifyPointInPath(\
                this->routingProcess(pSelectedPaths.at(pathPosition)->getCoincidencePoints(coincidencePointPosition), pSvgLenght, pSvgWidth, radianes, pFrames), \
                coincidencePointPosition);

                cout << "Cantidad de movimientos en el path: " << (pSelectedPaths.at(pathPosition)->getCoincidencePoints(coincidencePointPosition).offsetPoints.size()) / 2 << endl;

                cout << "Coordenada: " << pSelectedPaths.at(pathPosition)->getCoincidencePoints(coincidencePointPosition).xCoordinate  << endl;
                cout << "==========================" << endl;

                for(int i =0; i < pSelectedPaths.at(pathPosition)->getCoincidencePoints(coincidencePointPosition).offsetPoints.size(); i++){
                    cout << pSelectedPaths.at(pathPosition)->getCoincidencePoints(coincidencePointPosition).offsetPoints.at(i) << endl;
                }
            }           
        }
        return pSelectedPaths;
    }

    // n = cada path
    // vector de soluciones
    PointInPath routingProcess (PointInPath coincidencePoint, float pSvgLenght, float pSvgWidth, float radianes, int pFrames){
        float grados = radianes * (180/M_PI);
        float nextMove[2] = {coincidencePoint.xCoordinate, coincidencePoint.yCoordinate};
        // cout << "Coordenadas de next; " << nextMove[0] << ", " << nextMove[1] << endl;
        cout << "Routing process" << endl;

        float *final = {this->calculateEndPoint(coincidencePoint, pSvgLenght, pSvgWidth, radianes)};
        // cout << "X: "<< final[0] << "Y: "<< final[1] << endl;

        float distanceBetweenPoints = sqrt(pow(coincidencePoint.xCoordinate - final[0], 2) + pow(coincidencePoint.yCoordinate - final[1], 2));
        // cout << "Distancia: " << distanceBetweenPoints << endl;
        float movementDistance = distanceBetweenPoints/pFrames;
        // cout << "La cantidad de movimiento va a ser: " << movementDistance << endl;

        if(movementDistance < 10){
            movementDistance = 10;
        }

        float xMovement = ( movementDistance * abs(coincidencePoint.xCoordinate - final[0]) ) / distanceBetweenPoints;
        float yMovement = ( movementDistance * abs(coincidencePoint.yCoordinate - final[1]) ) / distanceBetweenPoints;

        // cout << "Distancia x: " << xMovement << endl;
        // cout << "Distancia y: " << yMovement << endl;

        // Case 1; first quadrant
        // cout << "GRADOS: " << grados << endl;

        if (grados >= 0 && grados <= 90){
            cout << "Entro al if del cuadrante 1" << endl;
            while ((nextMove[0] >= 0 && nextMove[0] <= pSvgLenght) && (nextMove[1] >= 0 && nextMove[1] <= pSvgWidth)){
                coincidencePoint.offsetPoints.push_back(nextMove[0]);
                coincidencePoint.offsetPoints.push_back(nextMove[1]);
                cout << "Siguiente: " << nextMove[0] << ", " << nextMove[1] << endl;
                nextMove[0] += xMovement;
                nextMove[1] -= yMovement;
                nextMove[0] = floorf(nextMove[0]*100000) / 100000;
                nextMove[1] = floorf(nextMove[1]*100000) / 100000;
            }
        }

        // Case 2; second quadrant
        if (grados >90 && grados <= 180){
            cout << "Entro al if del cuadrante 2" << endl;
            while ((nextMove[0] >= 0 && nextMove[0] <= pSvgLenght) && (nextMove[1] >= 0 && nextMove[1] <= pSvgWidth)){
                coincidencePoint.offsetPoints.push_back(nextMove[0]);
                coincidencePoint.offsetPoints.push_back(nextMove[1]);
                cout << "Siguiente: " << nextMove[0] << ", " << nextMove[1] << endl;
                nextMove[0] -= xMovement;
                nextMove[1] -= yMovement;
                nextMove[0] = floorf(nextMove[0]*100000) / 100000;
                nextMove[1] = floorf(nextMove[1]*100000) / 100000;
            }
        }

        // Case 3; third quadrant
        if (grados >180 && grados <= 270){
            cout << "Entro al if del cuadrante 3" << endl;
            while ((nextMove[0] >= 0 && nextMove[0] <= pSvgLenght) && (nextMove[1] >= 0 && nextMove[1] <= pSvgWidth)){
                coincidencePoint.offsetPoints.push_back(nextMove[0]);
                coincidencePoint.offsetPoints.push_back(nextMove[1]);
                cout << "Siguiente: " << nextMove[0] << ", " << nextMove[1] << endl;
                nextMove[0] -= xMovement;
                nextMove[1] += yMovement;
                nextMove[0] = floorf(nextMove[0]*100000) / 100000;
                nextMove[1] = floorf(nextMove[1]*100000) / 100000;
            }
        }

        // Case 4; fourth quadrant
        if (grados > 270 && grados <= 360){
            cout << "Entro al if del cuadrante 4" << endl;
            while ((nextMove[0] >= 0 && nextMove[0] <= pSvgLenght) && (nextMove[1] >= 0 && nextMove[1] <= pSvgWidth)){
                coincidencePoint.offsetPoints.push_back(nextMove[0]);
                coincidencePoint.offsetPoints.push_back(nextMove[1]);
                
                cout << "Siguiente: " << nextMove[0] << ", " << nextMove[1] << endl;
                nextMove[0] += xMovement;
                nextMove[1] += yMovement;
                nextMove[0] = floorf(nextMove[0]*100000) / 100000;
                nextMove[1] = floorf(nextMove[1]*100000) / 100000;
            }
        }

        // for (int i = 0; i < coincidencePoint.offsetPoints.size(); i++){
        //     cout << i << endl;
        //     cout << coincidencePoint.offsetPoints.at(i) << endl;
        // }
        return coincidencePoint;
    }

};

#endif