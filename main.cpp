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
#include "Classes/Circle.h"
#include "Classes/Rectangle.h"
#include "Classes/Ellipse.h"
#include "Classes/Polygon.h"
#include "Classes/Line.h"
#include "Classes/Polyline.h"
#include "DataProcessing.h"



using namespace std;

//Main --------------------------------------------------------------------------------------------------
//Funtion main
int main (){
    vector<Path*> svgPaths = pathDataProcessing();

    return 0;
}