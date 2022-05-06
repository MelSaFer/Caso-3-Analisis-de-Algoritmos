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
    //Point to find
    vector<float*> points;
    
    //file<> file("Svg/recyclingsymbol.svg");

    //Plataform* ambiente = new Plataform();

    //vector<Path*> svgPaths = pathDataProcessing(file);


    float radians = 4.71239;

    float p1[2] = {500.848, 274.711};
    float p5[2] = {505.848, 270.711};
    float p2[2] = {300.848, 274.711};
    float p3[2] = {200.848, 474.711};
    float p4[2] = {50.848, 454.711};
    
    points.push_back(p1);
    points.push_back(p2);
    points.push_back(p3);
    points.push_back(p4);
    points.push_back(p5);

    //Color to find
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
    Plataform* ambiente = new Plataform();

    vector<Path*> svgPaths = pathDataProcessing(file);


    //---------------------------------
    
    Selection* selection = new Selection();
    selection->attach(ambiente);
    vector<Path*> selectedPaths = selection->selecctionDivide(svgPaths, colors, points);


    cout << "Comprobacion \n2---------------------------------------" << endl;
    for (int i = 0; i < selectedPaths.size(); i++)
    {
        selectedPaths.at(i)->toString();
        cout << "---------------------------------------" << endl;
    }

    int code = selection->getClassId();
    int* ClassId = &code;
    selection->notify(ClassId, selectedPaths);

    cout << "---------------------------------------" << endl;
    cout << "---------------------------------------" << endl;
    Routing* rou = new Routing();
    selectedPaths = rou->routingPreProcess(radians, selectedPaths, 628.254, 613.516, frames);



//    Generation* gen = new Generation();
//    cout << "call" << endl;
//    gen->generateNewPath(selectedPaths, file);

    //delete selection;
    delete selection;
    // delete gen;
    delete rou;
    return 0;


}
