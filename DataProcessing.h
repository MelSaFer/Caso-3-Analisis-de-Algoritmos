#include <iostream>
#include "rapidxml/rapidxml_ext.hpp" //Clases para manejo del DOM
#include "rapidxml/rapidxml_utils.hpp" //Clase File
#include <sstream>
#include <fstream>
#include <string>
#include "Classes/Path.h"

using namespace std;
using namespace rapidxml; //Namespace de la librería

void extractXMLData(xml_document<>* doc);
void extractNodeData(xml_node<>* node);

vector<Path*> svgPaths;

//Recorre el elemento raíz del documento
void extractXMLData(xml_document<>* doc){
    xml_node<>* node = doc->first_node();
    extractNodeData(node);
}

//Recorre el resto de elementos del documento
void extractNodeData(xml_node<>* node){
    for (node = node->first_node(); node != NULL; node = node->next_sibling()){
        if (node->type() == node_element ){
            if(node->name() == (string)"path"){
                Path* currentPath = new Path(); 	
                for (xml_attribute<>* attrib = node->first_attribute(); attrib != NULL; attrib = attrib->next_attribute()){
					if (attrib->name() == (string)"id"){
						currentPath->setIdentifier(attrib->value());
					}
                    else if (attrib->name() == (string)"fill"){
                        currentPath->setPathColor(attrib->value());
                    }
                    else if (attrib->name() == (string)"d"){
                        currentPath->setPathPoints(attrib->value());
                    }
                    else if (attrib->name() == (string)"style"){
                        currentPath->setPathStyle(attrib->value());
                    }
                }
				svgPaths.push_back(currentPath);
            }
            extractNodeData(node);
        }
    }
}

vector<Path*> pathDataProcessing(){
    file<> file("recyclingsymbol.svg"); // Lee y carga el archivo en memoria
  	xml_document<> myDoc; //Raíz del árbol DOM
  	myDoc.parse<0>(file.data()); //Parsea el XML en un DOM

      //Recorrer elementos y atributos
	extractXMLData(&myDoc);

	cout<< "\nPaths: "<< endl;
    for(int i = 0; i < svgPaths.size(); i++){
        cout<<"======================"<< endl;
        svgPaths[i]->toString();
        cout<<"\n";
    }
    return svgPaths; 
}
