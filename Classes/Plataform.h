#ifndef PLATAFORM
#define PLATAFORM
#include <iostream>
#include <list>
#include <vector>
#include <thread>
//#include "ObserverPattern\ObserverPattern2.h"
using namespace std;



class Plataform : public Observer {
    private:
        //list<Observer*> ;
        

    public:
        Plataform() {}
        ~Plataform() {}

        void update(void* pClassId) {
            // (int*) = castear el puntero void a puntero a int
            // (int) = valor del int al que apunta
            int notifyValue = *(int*)pClassId;

            if (notifyValue == 1)
                cout << "Seleccion ha terminado" << endl;
            else if (notifyValue == 2)
                cout << "Enrutamiento ha terminado" << endl;
            else if (notifyValue == 3)
                cout << "Se ha publicado una nueva tarea del curso Ambiente Humano" << endl;
        }

};

#endif