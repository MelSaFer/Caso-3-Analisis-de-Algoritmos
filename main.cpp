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
#include "Ellipse.h"
#include "Polygon.h"
#include "Line.h"
#include "Polyline.h"



using namespace std;

//Main --------------------------------------------------------------------------------------------------
//Funtion main
int main (){

    Circle* circulo = new Circle();
    circulo->setRadius(2);
    circulo->setIdentifier("261GG");

    cout <<"CIRCLE : \n" << circulo->getRadius() << endl;
    cout << circulo->getIdentifier() << endl;

    Rectangle* rect = new Rectangle();
    rect->setIdentifier("1614GE");
    cout <<"RECTANGLE: " << rect->getIdentifier() << endl;

    Ellipse* eli = new Ellipse();
    eli->setIdentifier("16151kk");
    cout <<"ELLIPSE: " << eli->getIdentifier() << endl;

    Polygon* pol = new Polygon();
    pol->setIdentifier("16151kk");
    cout <<"POLYGON: "<< pol->getIdentifier() << endl;

    Line* line = new Line();
    line->setIdentifier("das334ghyc7");
    cout <<"LINE: "<< line->getIdentifier() << endl;

    Polyline* pl = new Polyline();
    pl->setIdentifier("kj6k2p3");
    cout <<"POLYLINE: "<< pl->getIdentifier() << endl;

    return 0;
}