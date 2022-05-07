// Libraries ---------------------------------------------------------------------------------------------

#ifndef GENERATION
#define GENERATION

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <list>
#include <thread>
#include <string>
#include "Path.h"
#include <sstream>
#include <fstream>
#include <cstring>
//#include <direct.h>
//#include "ProducerConsumer.h"
#include "ObserverPattern.h"
#include "rapidxml/rapidxml_ext.hpp"   //Class
#include "rapidxml/rapidxml_utils.hpp" //Class File

using namespace std;
using namespace rapidxml; // Namespace de la librería

class Generation{
    private:
        // Paths selecionados
        static const int ClassId = 2;
        list<Observer *> ObserversList;

    public:
        //
        Generation() {}
        ~Generation() {}
        //
        //        void attach(Observer* pNewObserver) {
        //            ObserversList.emplace_back(pNewObserver);
        //        }
        //
        //        void detach(Observer* pObserverDelete) {
        //            ObserversList.remove(pObserverDelete);
        //        }
        //
        //        void notify(void* pClassId) {
        //            for (Observer* currentObserver: ObserversList) {
        //                thread t(&Observer::update, currentObserver, pClassId); // parametros = (direccionDeMetodo, instancia/objeto, parametro)
        //                t.join(); // espere a que t termine
        //            }
        //        }

        int getClassId(){
            return ClassId;
        }

        /*
        Generation Process
        Dinamic Programing:
            -n= The paths after the modifications in Routing
            -Stages: all the points we are modifing in the SVG
            -Local Optimun: The modifided points in the current path
            -Global Optimun: All the new paths
            -Memorization: We use the previus path to improve the current path
        */

        void processSelectedPaths(vector<Path*> pSelectedPaths, file<> pFile, string pName, int pFrames){
            xml_document<> xmlDoc;         // Ra�z del �rbol DOM
            xmlDoc.parse<0>(pFile.data()); // Parsea el XML en un DO
            PointInPath previusPoint;
            for ( int framesGenerated = 0; framesGenerated < pFrames; framesGenerated++){
                for (int currentPathIndex = 0; currentPathIndex < pSelectedPaths.size(); currentPathIndex++){
                    processCurrentPath(pSelectedPaths.at(currentPathIndex), &xmlDoc, framesGenerated);
                    
                    pSelectedPaths.at(currentPathIndex)->toString();
                }//
            }
        }

        void processCurrentPath(Path* pCurrentPath, xml_document<> *pXmlDoc, int pFramesGenerated){
            for(int currentCoincidence = 0; currentCoincidence < pCurrentPath->getCoincidencePoints().size() ; currentCoincidence++){
                stages(pCurrentPath->getCoincidencePoints(currentCoincidence), pXmlDoc, pFramesGenerated);
            }

        }

        void stages(PointInPath pCurrentPoint, xml_document<> *myDoc, int currentFrame){
            cout <<"X original: " << pCurrentPoint.xCoordinate <<endl;
             for(int i = 0; i < pCurrentPoint.offsetPoints.size(); i++){
                cout <<"\tX : " << pCurrentPoint.offsetPoints[0] <<endl;
            }
            // float newMaxX = 10.0 + pCurrentPoint.at(currentFrame)[0];   //[0];
            // cout << pCurrentPoint.at(currentFrame)[0]<<endl;
            // float newMinX = 10.0 - pCurrentPoint.at(currentFrame)[0];
            // float newMaxY = 10.0 + pCurrentPoint.at(currentFrame)[1];
            // float newMinY = 10.0 - pCurrentPoint.at(currentFrame)[1];

            // string space = " ";

            // string newPoints = "M" + space + to_string(newMinX) + space + to_string(newMinY) + space + \
            //              to_string(newMaxX) + space + to_string(newMinY) + space + to_string(newMaxX) + space + \
            //              to_string(newMaxY) + space + to_string(newMinX) + space + to_string(newMaxY)+ " Z";

            // cout << newPoints<< endl;

            // //xml_node<> *newNode;

        }

        // void generateNewPath(vector<Path*> pSelectedAndModifiedPaths, file<> pFile, string pName, int pFrames){

        //}

        // void stages(Path* pCurrentPath, Path* pPreviusPath, file<> pFile, string name, int pFrames){

        //     xml_document<> myDoc; //Ra�z del �rbol DOM
        //     myDoc.parse<0>(pFile.data()); //Parsea el XML en un DOM

        //     int sizeCoincidendePath = pCurrentPath->getCoincidencePoints().size();

        //     float newMaxX;
        //     float newMinX;
        //     float newMaxY;
        //     float newMinY;
        //     //xml_node<> *newNode;
        //     string letterOfSVGPoint = "M";
        //     string space = " ";
        //     string newPoints;
        //     char newPointsInPath[100];
        //     float* currentCpoincidencePoint;

        //     //xml_attribute<> *newAttr;
        //     //xml_attribute<> *newAttr2;
        //     //xml_attribute<> *newAttr;

        //     for( int currentCoincidence = 0; currentCoincidence < sizeCoincidendePath; currentCoincidence++){

        //         currentCpoincidencePoint=  pCurrentPath->getCoincidencePoints(currentCoincidence);

        //         newMaxX = currentCpoincidencePoint[0]+10.0;
        //         newMinX = currentCpoincidencePoint[0]-10.0;

        //         newMaxY = currentCpoincidencePoint[1]+10.0;
        //         newMinY = currentCpoincidencePoint[1]-10.0;

        //         //cout << newMaxX<<endl;

        //         //free(newNode);
        //         newPoints = letterOfSVGPoint + space + to_string(newMinX) + space + to_string(newMinY) + space + \
            //             to_string(newMaxX) + space + to_string(newMinY) + space + to_string(newMaxX) + space + \
            //             to_string(newMaxY) + space + to_string(newMinX) + space + to_string(newMaxY)+ " Z";

        //         strcpy(newPointsInPath,newPoints.c_str());

        //         xml_node<> *newNode = myDoc.allocate_node(node_element, "path");
        //         myDoc.first_node()->append_node(newNode); //Elemento <path>

        //         const char *NewD = newPointsInPath;
        //         //cout << "1-> " << NewD << endl;
        //         xml_attribute<> *newAttr = myDoc.allocate_attribute("d", newPointsInPath);
        //         newNode->append_attribute(newAttr); //Atributo "d" para <path>

        //         cout << "2-> " << NewD << endl;
        //         cout << "2" <<endl;

        //         cout << "1" <<endl;
        //         xml_attribute<> *newAttr2;
        //         if(currentCoincidence == 0 ){
        //             newAttr2 = myDoc.allocate_attribute("fill", "green");
        //             cout << "Agrego: " << newPointsInPath <<endl;

        //         }else{
        //             newAttr2 = myDoc.allocate_attribute("fill", "blue");
        //             cout << "Agrego: " << newPointsInPath <<endl;
        //         }
        //         newNode->append_attribute(newAttr2); //Atributo "fill" para <path>
        //         //newNode->append_attribute(newAttr); //Atributo "d" para <path>

        //         newNode = NULL;
        //         newAttr = NULL;
        //         cout << "3" <<endl;

        //         //delete(newAttr);

        //     }
        //     this->newSVGGenerator(pFile, name, pFrames, &myDoc);
        //     //return pCurrentPath;
        // }

        // file<> generateNewPath(file<> pFile, char* pNewD, char* pNewColor){

        //     xml_document<> pNewDoc; //Ra�z del �rbol DOM
        //     pNewDoc.parse<0>(pFile.data()); //Parsea el XML en un DOM

        //     xml_node<> *newNode = pNewDoc.allocate_node(node_element, "path");
        //     pNewDoc.first_node()->append_node(newNode); //Elemento <path>

        //     //cout << "1-> " << NewD << endl;
        //     xml_attribute<> *newAttr = pNewDoc.allocate_attribute("d", pNewD);
        //     newNode->append_attribute(newAttr); //Atributo "d" para <path>

        //     cout << "2-> " << pNewD << endl;
        //     cout << "2" <<endl;

        //     cout << "1" <<endl;
        //     xml_attribute<> *newAttr2;
        //     newAttr2 = pNewDoc.allocate_attribute("fill", pNewColor);
        //     cout << "Agrego: " << pNewD <<endl;

        //     newNode->append_attribute(newAttr2); //Atributo "fill" para <path>
        //     //newNode->append_attribute(newAttr); //Atributo "d" para <path>
        //     cout << "3" <<endl;

        //     return pFile;

        // }

        // void newSVGGenerator(file<> pFile, string name, int pFrames, xml_document<> *myDoc){
        //     cout << "5" <<endl;
        //     string newFileName = "Results/p" + name + to_string(pFrames)  + ".svg";

        //     char newFileNameCopy[100];
        //     strcpy(newFileNameCopy,newFileName.c_str());
        //     cout << newFileNameCopy;

        //     ofstream copyFile(newFileNameCopy); //Nuevo archivo
        //     stringstream ss;
        //     ss << *myDoc->first_node(); //Pasa el nodo ra�z a ss
        //     string stringXML = ss.str(); //ss.toString
        //     copyFile << stringXML;
        //     copyFile.close(); //Escribe y cierra

        // }

        // void newSVGGenerator2(float pNewMaxX, float pNewMinX, float pNewMaxY, float pNewMinY, file<> pFile, string name, int pFrames){
        //     //cout << "1" << endl;
        //     //file<> fileSVG("Svg/man.svg"); // Lee y carga el archivo en memoria
        //     //cout << "2" << endl;
        //     xml_document<> myDoc; //Ra�z del �rbol DOM
        //     myDoc.parse<0>(pFile.data()); //Parsea el XML en un DOM

        //     //Recorrer elementos y atributos
        //     //extractXMLData2(&myDoc);

        //     xml_node<> *newNode = myDoc.allocate_node(node_element, "path");
        //     myDoc.first_node()->append_node(newNode); //Elemento <path>

        //     string letterOfSVGPoint = "M";
        //     string space = " ";

        //     string newPoints = letterOfSVGPoint + space + to_string(pNewMinX) + space + to_string(pNewMinY) + space + \
            //         to_string(pNewMaxX) + space + to_string(pNewMinY) + space + to_string(pNewMaxX) + space + \
            //         to_string(pNewMaxY) + space + to_string(pNewMinX) + space + to_string(pNewMaxY)+ " Z";

        //     char newPointsInPath[100];
        //     strcpy(newPointsInPath,newPoints.c_str());
        //     cout << newPointsInPath;

        //     cout << newPoints <<endl;

        //     xml_attribute<> *newAttr = myDoc.allocate_attribute("d", newPointsInPath);
        //     newNode->append_attribute(newAttr); //Atributo "d" para <path>

        //     xml_attribute<> *newAttr2 = myDoc.allocate_attribute("fill", "red");
        //     newNode->append_attribute(newAttr2); //Atributo "fill" para <path>
        //     //producer of new paths

        //     //We create a ------ for the result

        //     //string ruta= "Results/";

        //     //string ruta_absoluta = ruta + name;
        //     //cout << ruta_absoluta;
        //     //if (mkdir(ruta_absoluta.c_str()) == 1){
        //     //    cout << "Carpeta creada correctamente" << endl;
        //     //} else
        //     //    cout << "Ha ocurrido un error al crear la carpeta" << endl;

        //     string newFileName = "Results/" + name + to_string(pFrames)  + ".svg";

        //     char newFileNameCopy[100];
        //     strcpy(newFileNameCopy,newFileName.c_str());
        //     cout << newFileNameCopy;

        //     // cout << newPoints <<endl;

        //     ofstream copyFile(newFileNameCopy); //Nuevo archivo
        //     stringstream ss;
        //     ss << *myDoc.first_node(); //Pasa el nodo ra�z a ss
        //     string stringXML = ss.str(); //ss.toString
        //     copyFile << stringXML;
        //     copyFile.close(); //Escribe y cierra

        //     //Document to String
        //     //string strXML;
        //     //print(back_inserter(strXML), myDoc, 0); //Copia el texto del Document en la variable
        //     //cout << strXML << endl;

        // }
};

#endif
