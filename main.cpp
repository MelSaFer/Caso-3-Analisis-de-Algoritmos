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
#include "Classes/Plataform.h"
//#include "Classes/GenerationClass.h"




using namespace std;



//Main --------------------------------------------------------------------------------------------------
//Funtion main
int main (){

    Plataform* ambiente = new Plataform();

    vector<Path*> svgPaths = pathDataProcessing();

    Selection* selection = new Selection();
    selection->attach(ambiente);
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
    string color2 = "#1133FF";
    colors.push_back(color1);
    colors.push_back(color2);

    //selection->processOfSelection(svgPaths, colors, points);

    vector<Path*> selectedPaths;

    selectedPaths = selection->processOfSelection(svgPaths, colors, points);

    //---------------------------------
    cout << "-----------------------------------" << endl;
    Selection* selection2 = new Selection();
    vector<Path*> selectedPaths2 = selection2->selecctionDivide(svgPaths, colors, points);

    //Selection* selection3 = new Selection();
    //vector<Path*> svgPathsE = pathDataProcessing2(selection3, colors, points);

    cout << "Comprobacion" << endl;

    for (int i = 0; i < selectedPaths.size(); i++)
    {
        cout << "1- " << selectedPaths.at(i)->getIdentifier() << endl;
        cout << "--" << selectedPaths.at(i)->getPositionInPath() << endl;

    }

    for (int i = 0; i < selectedPaths2.size(); i++)
    {
        //cout << selectedPaths2.size() << endl;
        cout << "2- " << selectedPaths2.at(i)->getIdentifier() << endl;
        cout << "--" << selectedPaths2.at(i)->getPositionInPath() << endl;

    }

    // for (int i = 0; i < svgPathsE.size(); i++)
    // {
    //     //cout << "3- " << svgPathsE.at(i)->getIdentifier() << endl;

    // }


    int code = selection->getClassId();

    int* ClassId = &code;
    selection->notify(ClassId, selectedPaths);



   //Generation* gen = new Generation();

    delete selection;
    delete selection2;
    //delete gen;
    return 0;


}
