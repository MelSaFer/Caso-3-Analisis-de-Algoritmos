#ifndef DATAPROCESSING
#define DATAPROCESSING

#include <iostream>
#include <stdlib.h>
#include "rapidxml/rapidxml_ext.hpp" //Class 
#include "rapidxml/rapidxml_utils.hpp" //Class File
#include <sstream>
#include <fstream>
#include <string>
#include "Classes/Path.h"
#include "Classes/SelectionClass.h"

using namespace std;
using namespace rapidxml; //Namespace of the library

void extractXMLData(xml_document<>* doc);
void extractNodeData(xml_node<>* node);

vector<Path*> svgPaths;   //stores all the path while the program reads the file
int pathPosition = 1;

//___________________________________________________________________________________________________________________________
/* Funtion for extracting the data int the root of the document****
Input: root of the tree after the parse****
Return: None
*/
void extractXMLData(xml_document<>* doc){
    xml_node<>* node = doc->first_node();

    for (xml_attribute<>* attrib = node->first_attribute(); attrib != NULL; attrib = attrib->next_attribute()){
        if(attrib->name() == (string)"viewBox"){
            string viewBoxString = attrib->value();
            float svgWidth = 0, svgHeight = 0;
            viewBoxString.erase(0,3);

            //string lectura; 
            string actualNumberString;
            stringstream input_stringstream(viewBoxString);  //stringstream input_stringstream(cadena); 

            float actualNumber = -1; // first time

            while(getline(input_stringstream, actualNumberString, ' ')){  //while (getline(input_stringstream, lectura, ' ')){
                if (actualNumberString.length() > 0){
                    if(actualNumber == -1){
                        actualNumber = stof(actualNumberString);
                        svgWidth = actualNumber;
                    }
                    else{
                        actualNumber = stof(actualNumberString);
                        svgHeight = actualNumber;
                    }
                } 
            }
            cout << attrib->name() << endl;
            cout << attrib->value() << endl;
        }
    }
    extractNodeData(node);   //calls the funtion for extract the info of the node
    
}

//___________________________________________________________________________________________________________________________
/* Funtion for extracting the data int the node****
Input: a node of the document(tree with information of the document)
Return: None
*/
void extractNodeData(xml_node<>* node){
    for (node = node->first_node(); node != NULL; node = node->next_sibling()){
        if (node->type() == node_element ){
            //verifies if the node is a path
            if(node->name() == (string)"path"){
                //Creates a new object of type Path
                Path* currentPath = new Path(); 
                currentPath->setPositionInPath(pathPosition);
                pathPosition++;	
                for (xml_attribute<>* attrib = node->first_attribute(); attrib != NULL; attrib = attrib->next_attribute()){
                    //assing the value to the respective variable
					if (attrib->name() == (string)"id"){
						currentPath->setIdentifier(attrib->value());
					}
                    else if (attrib->name() == (string)"fill"){
                        currentPath->setPathColor(attrib->value());
                    }
                    else if (attrib->name() == (string)"d"){
                        currentPath->setPathPoints(attrib->value());
                        //ccout << "\nhola" << attrib->value();
                        currentPath->setQuadrantPoints();
                    }
                    else if (attrib->name() == (string)"style"){
                        string pathStyle = attrib->value();
                        string pathColor = pathStyle.substr(5,11);
                        currentPath->setPathColor(pathColor);
                    }
                }
                
				svgPaths.push_back(currentPath);
            }
            extractNodeData(node);
        }
    }
}

//___________________________________________________________________________________________________________________________

vector<Path*> pathDataProcessing( file<> file){
    //file<> file("Svg/recyclingsymbol.svg"); // read the file
  	xml_document<> myDoc; //root of the tree
  	myDoc.parse<0>(file.data()); //Parse the XML into a DOM

    //Extract the informatito form the svg
	extractXMLData(&myDoc);
    return svgPaths; 
}
#endif