//Libraries ---------------------------------------------------------------------------------------------

#ifndef ROUTING
#define ROUTING
#include <stdio.h>      
#include <stdlib.h>    
#include <iostream>
#include <vector>
#include <list>
#include <thread>
#include "ObserverPattern.h"

using namespace std;

class Routing {
    private:
        //Paths selecionados
        static const int ClassId = 1;
        list<Observer*> ObserversList; 

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

};

#endif