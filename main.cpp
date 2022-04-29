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
#include "DataProcessing.h"
#include "Classes/SelectionClass.h"
#include "Classes/GenerationClass.h"




using namespace std;



//Main --------------------------------------------------------------------------------------------------
//Funtion main
int main (){
    
    vector<Path*> svgPaths = pathDataProcessing();
    
    Selection* selection = new Selection();
    cout << "\n\n\n\n" << endl;
 
    float p1[2] = {500.848, 274.711};
    float p5[2] = {505.848, 270.711};
    float p2[2] = {300.848, 274.711}; 
    float p3[2] = {200.848, 474.711}; 
    float p4[2] = {50.848, 454.711}; 
    vector<float*> points;
    points.push_back(p1); 
    points.push_back(p2);
    points.push_back(p3);
    points.push_back(p4);
    points.push_back(p5);

    vector<string> colors; 
    string color1 = "#bf7f24";
    colors.push_back(color1);
    selection->processOfSelection(svgPaths, colors, points);

    Generation* gen = new Generation();

    delete selection;
    delete gen;
    return 0;


}