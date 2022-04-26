//Libraries ---------------------------------------------------------------------------------------------
#include <stdio.h>      
#include <stdlib.h>    
#include <iostream>
#include <vector>
#include <list>
#include <thread>
#include "Path.h"
#include "SvgShape.h"

//#include "ObserverPattern\ObserverPattern2.h"

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
        vector<SvgShape*> processOfSelection(vector<Path*> pPathsInTheSVG, vector<string> pColorsToFind, vector<float*> pPointsToFind){
            vector<SvgShape*> selectedPaths;
            int maxVectorLenght;
            if(pPointsToFind.size() < pColorsToFind.size()){
                maxVectorLenght = pColorsToFind.size();
            } else{
                maxVectorLenght = pPointsToFind.size();
            }
            //In here the n is travelled
            for( int currentPathIndex = 0; currentPathIndex < pPathsInTheSVG.size() ; currentPathIndex++){
                //
                for( int currentPointIndex = 0; currentPathIndex < maxVectorLenght; currentPathIndex++){
                    if(currentPathIndex < pColorsToFind.size()){

                    } else if (currentPathIndex < pPointsToFind.size()){
                        if( (pPathsInTheSVG.at(currentPathIndex)->getMaxQuadrantCoordX() > (float)pPointsToFind.at(currentPointIndex)[0])\
                        || (pPathsInTheSVG.at(currentPathIndex)->getMinQuadrantCoordX() < (float)pPointsToFind.at(currentPointIndex)[0])){
                            cout << "coincidencia en X" << endl;
                        }
                    }
                }

            }


            return selectedPaths;
        }

        void estoEsPrueba(){
            cout << "HOLA"<< endl;
        }

};