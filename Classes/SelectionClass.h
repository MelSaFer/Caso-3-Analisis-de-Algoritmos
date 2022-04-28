//Libraries ---------------------------------------------------------------------------------------------
#include <stdio.h>      
#include <stdlib.h>    
#include <iostream>
#include <vector>
#include <list>
#include <thread>
//#include "Path.h"
#ifndef PATH_H
#define PATH_H
#endif


#include "ObserverPattern\ObserverPattern2.h"

using namespace std;


class Selection : public Subject{
    private:
        //Paths selecionados
        static const int ClassId = 1;
        list<Observer*> ObserversList; 

    public:
        

        Selection() {}
        ~Selection() {}

        void attach(Observer* pNewObserver) {
            ObserversList.emplace_back(pNewObserver);
        }

        void detach(Observer* pObserverDelete) {
            ObserversList.remove(pObserverDelete);
        }

        void notify(void* pClassId) {
            for (Observer* currentObserver: ObserversList) {
                thread t(&Observer::update, currentObserver, pClassId); // parametros = (direccionDeMetodo, instancia/objeto, parametro)
                t.join(); // espere a que t termine
            }
        }

        int getClassId(){
            return ClassId;
        }

        /*------------------------------------------------------------------------------
        Function for selecting the paths who has coincidences in the list of
        points and colors
        ->Divide and Conquer Algorithm
            -n: Every path in the SVG
            -Divide: Path
            -Conquer: the selected path
            -Merge: The paths who has coincidences in at least one point and one color    
        -------------------------------------------------------------------------------*/
        vector<Path*> processOfSelection(vector<Path*> pPathsInTheSVG, vector<string> pColorsToFind, vector<float*> pPointsToFind){
            vector<Path*> selectedPaths;
            bool itsAMatch = false;

            for(int i =0; i < pPathsInTheSVG.size(); i++){

                for(int j = 0; j < pPointsToFind.size(); j++){
                    // cout << "Point = " << pPointsToFind.at(j)[0] << ", " << pPointsToFind.at(j)[1] << endl;
                    if( (pPointsToFind.at(j)[0] >= pPathsInTheSVG.at(i)->getMinQuadrantCoordX()) &&  (pPointsToFind.at(j)[0] <= pPathsInTheSVG.at(i)->getMaxQuadrantCoordX())\
                    && (pPointsToFind.at(j)[1] >= pPathsInTheSVG.at(i)->getMinQuadrantCoordY()) && (pPointsToFind.at(j)[1] <= pPathsInTheSVG.at(i)->getMaxQuadrantCoordY())){
                        //cout << "Match" << endl;
                        itsAMatch = true;
                        if( pColorsToFind.size() == 0){
                            selectedPaths.push_back(pPathsInTheSVG.at(i));
                        }
                    }
                }

                for(int j = 0; j < pColorsToFind.size(); j++){
                    if(itsAMatch){
                        selectedPaths.push_back(pPathsInTheSVG.at(i));
                    }else{
                        itsAMatch=false;
                    }
                }
            }

            for(int i = 0; i < selectedPaths.size(); i++){
                cout << selectedPaths.at(i)->getIdentifier()<< endl;
            }

            //cout << "Contador: " << contador << endl;

            return selectedPaths;
        }

        void estoEsPrueba(){
            cout << "HOLA"<< endl;
        }

};