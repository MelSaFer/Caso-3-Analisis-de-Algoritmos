/*Case 3
ITCR
Analisis de Algoritmos
Students:
        Melany Salas Fernandez
        Moises Solano Espinoza
*/

//Libraries ---------------------------------------------------------------------------------------------
#include <stdio.h>      
#include <stdlib.h>    
#include <iostream>
#include "Circle.h"
#include "Rectangle.h"
//#include "Ellipse.h"



using namespace std;

//Main --------------------------------------------------------------------------------------------------
//Funtion main
int main (){

    Circle* circulo = new Circle();
    circulo->setRadius(2);
    circulo->setIdentifier("261GG");

    cout << circulo->getRadius() << endl;
    cout << circulo->getIdentifier() << endl;


    Rectangle* rect = new Rectangle();
    rect->setIdentifier("1614GE");
    cout << rect->getIdentifier() << endl;


    return 0;
}