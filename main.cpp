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
#include "DataProcessingCopy.h"
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

    vector<Path*> selectedPaths;

    selectedPaths = selection->processOfSelection(svgPaths, colors, points);

    //---------------------------------
    cout << "-----------------------------------" << endl;
    Selection* selection2 = new Selection();
    vector<Path*> svgPathsE = pathDataProcessing2(selection2, colors, points);

    cout << "Comprobacion" << endl;

    for (int i = 0; i < selectedPaths.size(); i++)
    {
        cout << "1- " << selectedPaths.at(i)->getIdentifier() << endl;

        cout << "2- " << svgPathsE.at(i)->getIdentifier() << endl;

    }
  


    Generation* gen = new Generation();

    delete selection;
    delete selection2;
    delete gen;
    return 0;


}