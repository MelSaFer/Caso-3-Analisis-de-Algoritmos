//Libraries ---------------------------------------------------------------------------------------------
#include <stdio.h>      
#include <stdlib.h>    
#include <iostream>
#include <vector>
#include <list>
#include <thread>
// #include "Path.h"
#ifndef PATH_H
#define PATH_H
#endif
#include "SvgShape.h"

//#include "ObserverPattern\ObserverPattern2.h"

using namespace std;


class Selection{ //: public Subject{
    private:
        //Paths selecionados
        static const int ClassId = 1;
        //list<Observer*> ObserversList; 

    public:
        

        Selection() {}
        ~Selection() {}

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

        // int getClassId(){
        //     return ClassId;
        // }

        /*------------------------------------------------------------------------------
        Function for selecting the paths who has coincidences in the list of
        points and colors
        ->Divide and Conquer Algorithm
            -n: Every path in the SVG
            -Divide: Path
            -Conquer: the selected path
            -Merge: The paths who has coincidences in at least one point and one color    
        -------------------------------------------------------------------------------*/
        vector<SvgShape*> processOfSelection(vector<Path*> pPathsInTheSVG, vector<string> pColorsToFind, vector<float*> pPointsToFind){
            vector<SvgShape*> selectedPaths;
            // int maxVectorLenght;
            // if(pPointsToFind.size() < pColorsToFind.size()){
            //     maxVectorLenght = pColorsToFind.size();
            // } else{
            //     maxVectorLenght = pPointsToFind.size();
            // }
            // //In here the n is travelled
            // for( int currentPathIndex = 0; currentPathIndex < pPathsInTheSVG.size() ; currentPathIndex++){
            //     //
            //     for( int currentPointIndex = 0; currentPointIndex < maxVectorLenght; currentPointIndex++){
            //         if(currentPathIndex < pColorsToFind.size()){

            //         } else if (currentPathIndex < pPointsToFind.size()){
            //             cout << "Point = " << pPointsToFind.at(currentPointIndex)[0] << ", " << pPointsToFind.at(currentPointIndex)[1] << endl;
            //             cout << "coordenadas: " << pPathsInTheSVG.at(currentPathIndex)->getMaxQuadrantCoordX() << ", " << pPathsInTheSVG.at(currentPathIndex)->getMaxQuadrantCoordY()\
            //                 << " / " << pPathsInTheSVG.at(currentPathIndex)->getMinQuadrantCoordX() << ", " << pPathsInTheSVG.at(currentPathIndex)->getMinQuadrantCoordY() << endl;
                        
            //             if(  (pPointsToFind.at(currentPointIndex)[0] >= pPathsInTheSVG.at(currentPathIndex)->getMaxQuadrantCoordX() )\
            //             && (pPointsToFind.at(currentPointIndex)[0] <= pPathsInTheSVG.at(currentPathIndex)->getMinQuadrantCoordX())
            //             && (pPointsToFind.at(currentPointIndex)[1] >= pPathsInTheSVG.at(currentPathIndex)->getMaxQuadrantCoordY()) &&\
            //             (pPointsToFind.at(currentPointIndex)[1] <= pPathsInTheSVG.at(currentPathIndex)->getMinQuadrantCoordY()))
            //             {
            //                 cout << "coincidencia en X" << endl;
            //                 cout << "Path: " << pPathsInTheSVG.at(currentPathIndex)->getIdentifier() << endl;
            //                 cout << "coordenadas: " << pPathsInTheSVG.at(currentPathIndex)->getMaxQuadrantCoordX() << ", " << pPathsInTheSVG.at(currentPathIndex)->getMaxQuadrantCoordY()\
            //                 << " / " << pPathsInTheSVG.at(currentPathIndex)->getMinQuadrantCoordX() << ", " << pPathsInTheSVG.at(currentPathIndex)->getMinQuadrantCoordY() << endl;    
            //             }
            //         }
            //     }

            // }

            // for (int i = 0; i < pPointsToFind.size(); i++){
            //     cout << i << endl;
            //     cout << "Point = " << pPointsToFind.at(i)[0] << ", " << pPointsToFind.at(i)[1] << endl;
            // }

            int contador = 0;

            for(int i =0; i < pPathsInTheSVG.size(); i++){
                contador ++;
                for(int j = 0; j < pPointsToFind.size(); j++){
                    // cout << "Point = " << pPointsToFind.at(j)[0] << ", " << pPointsToFind.at(j)[1] << endl;
                    contador ++;

                    if( (pPointsToFind.at(j)[0] >= pPathsInTheSVG.at(i)->getMinQuadrantCoordX()) &&  (pPointsToFind.at(j)[0] <= pPathsInTheSVG.at(i)->getMaxQuadrantCoordX())\
                    && (pPointsToFind.at(j)[1] >= pPathsInTheSVG.at(i)->getMinQuadrantCoordY()) && (pPointsToFind.at(j)[1] <= pPathsInTheSVG.at(i)->getMaxQuadrantCoordY())){
                        cout << "Match" << endl;
                    }
                }
            }

            cout << "Contador: " << contador << endl;

            return selectedPaths;
        }

        void estoEsPrueba(){
            cout << "HOLA"<< endl;
        }

};