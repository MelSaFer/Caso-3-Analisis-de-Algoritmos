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

};

#endif