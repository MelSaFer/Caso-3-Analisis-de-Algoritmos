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

        // inicialzar vector de soluciones
        // funcion backtracking
        // distancia entre puntos

        float* calculateEndPoint (PointInPath pPathCoordinates, float pSvgLenght, float pSvgWidth, float radians){
            cout << "Funcion de punto final" << endl;
            float* endPoint = new float[2]; 
            bool itsSpecialCase = false;
            // current point
            float coorX = pPathCoordinates.xCoordinate;
            float coorY = pPathCoordinates.yCoordinate;
            float grados = radians * (180/M_PI);

            if(grados == 0 || grados == 360){
                coorX = pSvgLenght;
                itsSpecialCase = true;}
            else if(grados == 90){
                coorY == 0;
                itsSpecialCase = true;}
            else if(grados == 180){
                coorX == 0;
                itsSpecialCase = true;}
            else if(grados == 270){
                coorY = pSvgWidth;
                itsSpecialCase = true;}
            if(itsSpecialCase){
                endPoint[0] = coorX;
                endPoint[1] = coorY;
                cout << "caso especial de grados" << endl;
                return endPoint;}
            else{
                float pendiente = tan(grados*M_PI/180);
                // Case 1
                if (grados> 0 && grados < 90){
                    float newCoorX = -(pSvgLenght-coorX);
                    float newCoorY = -coorY;

                    float coincidenceY = -(pendiente*(-newCoorX)+newCoorY);
                    float coincidenceX = pSvgLenght + (coincidenceY/pendiente);

                    if(coincidenceX >= pSvgLenght){
                        coincidenceX = pSvgLenght;}
                    if(coincidenceY <= 0){
                        coincidenceY = 0;}
                        cout << "grados: " << grados << endl;
                    cout << "Caso1/El punto en el que toca el borde es: " << coincidenceX << ", " << coincidenceY << endl;
                    endPoint[0] = coincidenceX;
                    endPoint[1] = coincidenceY;
                }
                // Case 2
                else if (grados > 90 && grados < 180){
                    float newCoorY = -coorY;

                    float coincidenceY = -(pendiente*(-coorX)+newCoorY);
                    float coincidenceX = ((coincidenceY)/pendiente);

                    if(coincidenceX >= pSvgLenght || coincidenceX <= 0){
                        coincidenceX = 0;}
                    if(coincidenceY <= 0){
                        coincidenceY = 0;}
                    cout << "Caso2/El punto en el que toca el borde es: " << coincidenceX << ", " << coincidenceY << endl;
                    endPoint[0] = coincidenceX;
                    endPoint[1] = coincidenceY;
                }
                // Case 3
                else if (grados > 180 && grados < 270){
                    grados -= 180;
                    pendiente = tan(grados*M_PI/180);
                    float newCoorY = pSvgWidth - coorY;

                    float coincidenceY = (pendiente*(-coorX))+newCoorY;
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
                // Case 4
                else if (grados > 270 && grados < 360){
                    grados -= 180;
                    pendiente = tan(grados*M_PI/180);
                    float newCoorY = pSvgWidth - coorY;
                    float newCoorX = -(pSvgLenght - coorX);

                    float coincidenceY = (pendiente*(-newCoorX))+newCoorY;
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

    vector<Path*> routingPreProcess(float radianes, vector<Path*> paths, float largo, float ancho, int frames){
        int pathPosition, coincidencePointPosition;
        // float grados = radianes * (180/M_PI);
        for (pathPosition = 0; pathPosition < paths.size(); pathPosition++){

            for(coincidencePointPosition = 0; coincidencePointPosition < paths.at(pathPosition)->getCoincidencePoints().size(); coincidencePointPosition++){
                // this->calculateEndPoint(paths.at(pathPosition)->getCoincidencePoints(coincidencePointPosition), largo, ancho, radianes);
                paths.at(pathPosition)->modifyPointInPath(\
                this->routingProcess(paths.at(pathPosition)->getCoincidencePoints(coincidencePointPosition), largo, ancho, radianes, frames), \
                coincidencePointPosition);

                cout << "Cantidad de movimientos en el path: " << paths.at(pathPosition)->getCoincidencePoints(coincidencePointPosition).offsetPoints.size() << endl;

                cout << "Coordenada: " << paths.at(pathPosition)->getCoincidencePoints(coincidencePointPosition).xCoordinate  << endl;
                cout << "==========================" << endl;
            }           
        }
        return paths;
    }

    // n = cada path
    // vector de soluciones
    PointInPath routingProcess (PointInPath coincidencePoint, float largo, float ancho, float radianes, int frames){
        float grados = radianes * (180/M_PI);
        float nextMove[2] = {coincidencePoint.xCoordinate, coincidencePoint.yCoordinate};
        // cout << "Coordenadas de next; " << nextMove[0] << ", " << nextMove[1] << endl;
        cout << "Routing process" << endl;

        float *final = {this->calculateEndPoint(coincidencePoint, largo, ancho, radianes)};
        // cout << "X: "<< final[0] << "Y: "<< final[1] << endl;

        float distanceBetweenPoints = sqrt(pow(coincidencePoint.xCoordinate - final[0], 2) + pow(coincidencePoint.yCoordinate - final[1], 2));
        // cout << "Distancia: " << distanceBetweenPoints << endl;
        float movementDistance = distanceBetweenPoints/frames;
        // cout << "La cantidad de movimiento va a ser: " << movementDistance << endl;

        if(movementDistance < 10){
            movementDistance = 10;
        }

        float xMovement = ( movementDistance * abs(coincidencePoint.xCoordinate - final[0]) ) / distanceBetweenPoints;
        float yMovement = ( movementDistance * abs(coincidencePoint.yCoordinate - final[1]) ) / distanceBetweenPoints;

        // cout << "Distancia x: " << xMovement << endl;
        // cout << "Distancia y: " << yMovement << endl;

        // Caso cuadrante 1
        // cout << "GRADOS: " << grados << endl;

        if (grados >= 0 && grados <= 90){
            cout << "Entro al if del cuadrante 1" << endl;
            while ((nextMove[0] >= 0 && nextMove[0] <= largo) && (nextMove[1] >= 0 && nextMove[1] <= ancho)){
                coincidencePoint.offsetPoints.push_back(nextMove);
                cout << "Siguiente: " << nextMove[0] << ", " << nextMove[1] << endl;
                nextMove[0] += xMovement;
                nextMove[1] -= yMovement;
                nextMove[0] = floorf(nextMove[0]*100000) / 100000;
                nextMove[1] = floorf(nextMove[1]*100000) / 100000;
            }
        }

        // Caso cuadrante 2
        if (grados >90 && grados <= 180){
            cout << "Entro al if del cuadrante 2" << endl;
            while ((nextMove[0] >= 0 && nextMove[0] <= largo) && (nextMove[1] >= 0 && nextMove[1] <= ancho)){
                coincidencePoint.offsetPoints.push_back(nextMove);
                cout << "Siguiente: " << nextMove[0] << ", " << nextMove[1] << endl;
                nextMove[0] -= xMovement;
                nextMove[1] -= yMovement;
                nextMove[0] = floorf(nextMove[0]*100000) / 100000;
                nextMove[1] = floorf(nextMove[1]*100000) / 100000;
            }
        }

        // Caso cuadrante 3
        if (grados >180 && grados <= 270){
            cout << "Entro al if del cuadrante 3" << endl;
            while ((nextMove[0] >= 0 && nextMove[0] <= largo) && (nextMove[1] >= 0 && nextMove[1] <= ancho)){
                coincidencePoint.offsetPoints.push_back(nextMove);
                cout << "Siguiente: " << nextMove[0] << ", " << nextMove[1] << endl;
                nextMove[0] -= xMovement;
                nextMove[1] += yMovement;
                nextMove[0] = floorf(nextMove[0]*100000) / 100000;
                nextMove[1] = floorf(nextMove[1]*100000) / 100000;
            }
        }

        // Caso cuadrante 4
        if (grados > 270 && grados <= 360){
            cout << "Entro al if del cuadrante 4" << endl;
            while ((nextMove[0] >= 0 && nextMove[0] <= largo) && (nextMove[1] >= 0 && nextMove[1] <= ancho)){
                coincidencePoint.offsetPoints.push_back(nextMove);
                cout << "Siguiente: " << nextMove[0] << ", " << nextMove[1] << endl;
                nextMove[0] += xMovement;
                nextMove[1] += yMovement;
                nextMove[0] = floorf(nextMove[0]*100000) / 100000;
                nextMove[1] = floorf(nextMove[1]*100000) / 100000;
            }
        }
        return coincidencePoint;
    }












    vector<float*> initializeSolutionVector (PointInPath pCoincidencePoint){
        vector<float*> solutionVector;
        float coordenates[2];
        coordenates[0] = pCoincidencePoint.xCoordinate;
        coordenates[1] = pCoincidencePoint.yCoordinate;
        //pCoincidencePoint.offsetPoints.push_back(coordenates);

        solutionVector.push_back(coordenates);

        return solutionVector;
    }
    

};

#endif