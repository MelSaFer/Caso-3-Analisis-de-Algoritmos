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
//#include "DataProcessingCopy.h"
#include "Classes/SelectionClass.h"
#include "Classes/Plataform.h"
#include "Classes/GenerationClass.h"
#include "Classes/RoutingClass.h"




using namespace std;



//Main --------------------------------------------------------------------------------------------------
//Funtion main
int main (){

//DATA-----------------------------------------------------------------------------------------------------
    //File 
    char fileName[] = "Svg/recyclingsymbol.svg";
    //Points to find
    vector<float*> points;

    float p1[2] = {500.848, 274.711};
    float p5[2] = {505.848, 270.711};
    float p2[2] = {300.848, 274.711};
    float p3[2] = {200.848, 474.711};
    float p4[2] = {50.848, 454.711};
    
    // Points are added
    points.push_back(p1);
    points.push_back(p2);
    points.push_back(p3);
    points.push_back(p4);
    points.push_back(p5);

    // Radians
    float radians = 0.837758;

    //Colors to find
    vector<string> colors;
    string color1 = "#bf7f24";
    string color2 = "#1133FF";
    colors.push_back(color1);
    colors.push_back(color2);

    //Frames
    int frames = 5;

    //Open file
    file<> file(fileName);

//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
    Plataform* ambiente = new Plataform();

    // Read the paths from the .svg file
    vector<Path*> svgPaths = pathDataProcessing(file);

    //==================================================================
    // SELECTION -> DIVIDE & CONQUER
    //==================================================================
    
    Selection* selection = new Selection();
    selection->attach(ambiente);
    vector<Path*> selectedPaths = selection->selecctionDivide(svgPaths, colors, points);


    cout << "VERIFICATION \n2---------------------------------------" << endl;
    for (int i = 0; i < selectedPaths.size(); i++)
    {
        selectedPaths.at(i)->toString();
        cout << "---------------------------------------" << endl;
    }

    int code = selection->getClassId();
    int* ClassId = &code;
    selection->notify(ClassId, selectedPaths);

    //==================================================================
    // ROUTING -> BACKTRACKING
    //==================================================================

    cout << "---------------------------------------" << endl;
    cout << "---------------------------------------" << endl;
    Routing* rou = new Routing();
    selectedPaths = rou->routingPreProcess(radians, selectedPaths, getSvgSize()[0], getSvgSize()[1], frames);


    //==================================================================
    // GENERATION -> DYNAMIC PROGRAMMING
    //==================================================================
    Generation* gen = new Generation();
    // cout << "call" << endl;
    gen->processSelectedPaths(selectedPaths, file, "recyclingsymbol.svg", frames);

    //delete selection;
    delete selection;
    delete gen;
    delete rou;
    return 0;
}
