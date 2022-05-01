//Libraries ---------------------------------------------------------------------------------------------

#ifndef GENERATION
#define GENERATION

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <list>
#include <thread>
#include "Path.h"
#include "ProducerConsumer.h"

#include "ObserverPattern.h"


class Generation : public Subject{
    private:
        //Paths selecionados
        static const int ClassId = 2;
        list<Observer*> ObserversList;

    public:
        //
        Generation() {}
        ~Generation() {}

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

        /*
        Generation Process
        Dinamic Programing:
            -n= The paths after the modifications in Routing
            -Stages: all the points in the SVG
            -Local Optimun: The modifided points in the current path
            -Global Optimun: All the new paths
            -Memorization: We use the previus path to improve the current path
        */

        void generateNewPath(vector<Path*> allPaths, vector<Path*> selectedAndModifiedPaths){
            for(int currentPathIndex  = 0; currentPathIndex < allPaths.size(); currentPathIndex++){

            }

        }

        void stages(Path* pCurrentPath, pPreviusPath){
            //for( int currentPointInPath = 0; currentPointInPath < pCurrentPath->)


        }

};

#endif
