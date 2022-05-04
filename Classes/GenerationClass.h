//Libraries ---------------------------------------------------------------------------------------------

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
//#include "ProducerConsumer.h"
#include "ObserverPattern.h"
#include "rapidxml/rapidxml_ext.hpp" //Class
#include "rapidxml/rapidxml_utils.hpp" //Class File

using namespace std;
using namespace rapidxml; //Namespace de la librería



class Generation {
    private:
        //Paths selecionados
        static const int ClassId = 2;
        list<Observer*> ObserversList;

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
            -Stages: all the points in the SVG
            -Local Optimun: The modifided points in the current path
            -Global Optimun: All the new paths
            -Memorization: We use the previus path to improve the current path
        */

        void generateNewPath(vector<Path*> pSelectedAndModifiedPaths, file<> pFile, string name, int pFrames){
            Path* previusPath = new Path();
            for(int currentPathIndex  = 0; currentPathIndex < pSelectedAndModifiedPaths.size(); currentPathIndex++){
                //Path* previusPath=
                this->stages(pSelectedAndModifiedPaths.at(currentPathIndex), previusPath, pFile, name, pFrames);
            }

        }

        void stages(Path* pCurrentPath, Path* pPreviusPath, file<> pFile, string name, int pFrames){
            int sizeCoincidendePath = pCurrentPath->getCoincidencePoints().size();

            float newMaxX;
            float newMinX;
            float newMaxY;
            float newMinY;

            for( int currentCoincidence = 0; currentCoincidence < sizeCoincidendePath; currentCoincidence++){
                //busca paths y hace las modificaciones, luego lo manda al productor
                float* currentCpoincidencePoint=  pCurrentPath->getCoincidencePoints(currentCoincidence);

                newMaxX = currentCpoincidencePoint[0]+10.0;
                newMinX = currentCpoincidencePoint[0]-10.0;

                newMaxY = currentCpoincidencePoint[1]+10.0;
                newMinY = currentCpoincidencePoint[1]-10.0;

                cout << newMaxX<<endl;
                this->newSVGGenerator(newMaxX, newMinX, newMaxY, newMinY, pFile, name, pFrames);

            }
            //return pCurrentPath;
        }

        void newSVGGenerator(float pNewMaxX, float pNewMinX, float pNewMaxY, float pNewMinY, file<> pFile, string name, int pFrames){
            //cout << "1" << endl;
            //file<> fileSVG("Svg/man.svg"); // Lee y carga el archivo en memoria
            //cout << "2" << endl;
            xml_document<> myDoc; //Ra�z del �rbol DOM
            myDoc.parse<0>(pFile.data()); //Parsea el XML en un DOM

            //Recorrer elementos y atributos
            //extractXMLData2(&myDoc);

            xml_node<> *newNode = myDoc.allocate_node(node_element, "path");
            myDoc.first_node()->append_node(newNode); //Elemento <path>

            string letterOfSVGPoint = "M";
            string space = " ";

            string newPoints = letterOfSVGPoint + space + to_string(pNewMinX) + space + to_string(pNewMinY) + space + \
                to_string(pNewMaxX) + space + to_string(pNewMinY) + space + to_string(pNewMaxX) + space + \
                to_string(pNewMaxY) + space + to_string(pNewMinX) + space + to_string(pNewMaxY)+ " Z";

            
            char newPointsInPath[100];
            strcpy(newPointsInPath,newPoints.c_str());
            cout << newPointsInPath;

            cout << newPoints <<endl;

            xml_attribute<> *newAttr = myDoc.allocate_attribute("d", newPointsInPath);
            newNode->append_attribute(newAttr); //Atributo "d" para <path>

            xml_attribute<> *newAttr2 = myDoc.allocate_attribute("fill", "blue");
            newNode->append_attribute(newAttr2); //Atributo "fill" para <path>
            //producer of new paths


            string newFileName = name + to_string(pFrames)  + ".svg";
           

            
            char newFileNameCopy[100];
            strcpy(newFileNameCopy,newFileName.c_str());
            cout << newFileNameCopy;

            // cout << newPoints <<endl;


            ofstream copyFile(newFileNameCopy); //Nuevo archivo
            stringstream ss;
            ss << *myDoc.first_node(); //Pasa el nodo ra�z a ss
            string stringXML = ss.str(); //ss.toString
            copyFile << stringXML;
            copyFile.close(); //Escribe y cierra

            //Document to String
           // string strXML;
            //print(back_inserter(strXML), myDoc, 0); //Copia el texto del Document en la variable
            //cout << strXML << endl;

        }

};

#endif
