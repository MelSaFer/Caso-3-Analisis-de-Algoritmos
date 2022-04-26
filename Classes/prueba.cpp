#include <iostream>
#include <list>
#include <vector>
#include <thread>
#include "ObserverPattern\ObserverPattern2.h"
#include "SelectionClass.h"
#include "Plataform.h"
#include "RoutingClass.h"


using namespace std;

int main () {
//observer = ambiente
    Observer* ambiente = new Plataform();
    Subject* selection = new Selection();

    selection->attach(ambiente);

    int code = selection->getClassId();

    int* ClassId = &code;
    //cout << "error";
    selection->notify(ClassId);
    //selection->





    /*Observer* est1 = new Estudiante();
    Observer* est2 = new Estudiante();
    Observer* est3 = new Estudiante();

    Subject* plat = new Plataforma();
    plat->attach(est1);
    plat->attach(est2);
    plat->attach(est3);

    int curso = 2;
    int* cursoPointer = &curso;
    plat->notify(cursoPointer);

    cout << endl;
    cout << "Estudiante 1 ha abandonado un curso" << endl;
    plat->detach(est1);
    cout << "Vamos a crear una tarea nueva" << endl;
    curso = 1;
    plat->notify(cursoPointer);

    // Prueba con un objeto
//    Profesor* profe = new Profesor("Pedro");
//    plat->notify(profe);*/

    return 0;
}
