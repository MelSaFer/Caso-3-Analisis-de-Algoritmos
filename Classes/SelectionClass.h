#ifndef SELECTION
#define SELECTION

//Libraries ---------------------------------------------------------------------------------------------
#include <stdio.h>      
#include <stdlib.h>    
#include <iostream>
#include <vector>
#include <list>
#include <thread>
#include "Path.h"
#include "ObserverPattern.h"

using namespace std;


/*
________________________________________________________________________________________________________
Class Selection
    This class is use for the process of selection in our program
    Attributes: int:ClassId  
                list<Observers>:ObserverList
    Methods: attact
             detach
             notify
             getClassId
             selecctionDivide
             selectionConquer
________________________________________________________________________________________________________
*/
class Selection : public Subject{
    private:
        //Attributes
        static const int ClassId = 1;
        list<Observer*> ObserversList; 

    public:
        //Methods
        Selection() {}
        ~Selection() {}

        //-----------------------------------------------------------------------------
        //Adds new observers of the class
        //Parameters: An Observer
        //Return: None
        //-----------------------------------------------------------------------------
        void attach(Observer* pNewObserver) {
            ObserversList.emplace_back(pNewObserver);
        }

        //-----------------------------------------------------------------------------
        //Deletes observers of the class
        //Parameters: An Observer
        //Return: None
        //-----------------------------------------------------------------------------
        void detach(Observer* pObserverDelete) {
            ObserversList.remove(pObserverDelete);
        }

        //-----------------------------------------------------------------------------
        //Notify the observers of the class
        //Parameters: The classId and a vector of paths
        //Return: None
        //-----------------------------------------------------------------------------
        void notify(void* pClassId, vector<Path*> pPaths) {
            for (Observer* currentObserver: ObserversList) {
                thread t(&Observer::update, currentObserver, pClassId, pPaths);
                t.join(); // espere a que t termine
            }
        }

        //-----------------------------------------------------------------------------
        //Parameters: None
        //Return: Class id
        //-----------------------------------------------------------------------------
        int getClassId(){
            return ClassId;
        }

        /*------------------------------------------------------------------------------------------------------------------------------
        Function for selecting the paths who has coincidences in the list of
        points and colors
        ->Divide and Conquer Algorithm
            -n: Every path in the SVG
            -Divide: Path
            -Conquer: the selected path
            -Merge: The paths who has coincidences in at least one point and one color    
        
        Total temporal complexity = O(N*(C+P))
        --------------------------------------------------------------------------------------------------------------------------------*/

        /* 
        --------------------------------------------------------------------------------------------------------------------------------
        In this section we divide our n in paths and call the funcion who analices** the coincidence in the path (selectionConquer)
            Parameters: A vector with al the Paths in the svg, a vector with the colors and a vector of the points we are
                        looking for
            Return: A vector with the selected paths
        Temporal complexity = O(n)
        --------------------------------------------------------------------------------------------------------------------------------
        */
        vector<Path*> selecctionDivide(vector<Path*> pPathsInTheSVG, vector<string> pColorsToFind, vector<float*> pPointsToFind){
            vector<Path*> selectedPaths;
            //----------------------With this cycle we analize every path (our N)----------------------
            for(int currentPathIndex = 0; currentPathIndex < pPathsInTheSVG.size(); currentPathIndex++){
                selectedPaths = this->selectionConquer(pPathsInTheSVG.at(currentPathIndex),selectedPaths, pColorsToFind, pPointsToFind);
            }
            return selectedPaths;
        }

        /*
        --------------------------------------------------------------------------------------------------------------------------------
        In this part we analize every path acording to the colors and the points
            Parameters: A vector with al the Paths in the svg, a vector with the colors and a vector of the points we are
                        looking for
            Returs: The vector of selected paths modified
        */
        // O(C+P)
        vector<Path*> selectionConquer(Path* pCurrentPath, vector<Path*> pSelectedPaths, vector<string> pColorsToFind, vector<float*> pPointsToFind){

            //This variables are used like flags for the colors and points
            bool itsAColorMatch = false;
            bool itsACoordinateMatch = false;
            
            //This variables are used for analice the colors acording to the rgb code
            float rgbColors[3] = {0,0,0};
            float rgbColorsPath[3] = {0,0,0};
            float rgbDifferences[3];
            float rbgComparison;

            char *colorTextRed;
            char *colorTextGreen;
            char *colorTextBlue;

            char *colorTextPathRed;
            char *colorTextPathGreen;
            char *colorTextPathBlue;

            colorTextPathRed = pCurrentPath->getPathColor().substr(1,2).data();
            colorTextPathGreen = pCurrentPath->getPathColor().substr(3,2).data();
            colorTextPathBlue = pCurrentPath->getPathColor().substr(5,6).data();

            rgbColorsPath[0] = strtol(colorTextPathRed, NULL, 16);
            rgbColorsPath[1] = strtol(colorTextPathGreen, NULL, 16);
            rgbColorsPath[2] = strtol(colorTextPathBlue, NULL, 16);

            //This variable is use in the cicles
            int currentComparisonIndex;

            //this cicle is for analice the color in the list of colors (c)
            for(currentComparisonIndex = 0; currentComparisonIndex < pColorsToFind.size(); currentComparisonIndex++){

                colorTextRed = pColorsToFind.at(currentComparisonIndex).substr(1,2).data();
                colorTextGreen = pColorsToFind.at(currentComparisonIndex).substr(3,2).data();
                colorTextBlue = pColorsToFind.at(currentComparisonIndex).substr(5,6).data();
                rgbColors[0] = strtol(colorTextRed, NULL, 16);
                rgbColors[1] = strtol(colorTextGreen, NULL, 16);
                rgbColors[2] = strtol(colorTextBlue, NULL, 16);

                rgbDifferences[0] = abs((rgbColorsPath[0] - rgbColors[0]))/255 ;
                rgbDifferences[1] = abs((rgbColorsPath[1] - rgbColors[1]))/255 ;
                rgbDifferences[2] = abs((rgbColorsPath[2] - rgbColors[2]))/255 ;

                rbgComparison = ((rgbDifferences[0] + rgbDifferences[1] + rgbDifferences[2])/3)*100;

                if(rbgComparison <= 15){
                    itsAColorMatch = true; //if one color is similar to the color of the path means that is is candidate
                    break;  //Just one coincidence is necesary in the colors
                }

            }
            //this cicle is for analice the points in the list of points (p)
            for(currentComparisonIndex = 0; currentComparisonIndex < pPointsToFind.size() && itsAColorMatch; currentComparisonIndex++){
                if( (pPointsToFind.at(currentComparisonIndex)[0] >= pCurrentPath->getMinQuadrantCoordX()) && \
                    (pPointsToFind.at(currentComparisonIndex)[0] <= pCurrentPath->getMaxQuadrantCoordX()) && \
                    (pPointsToFind.at(currentComparisonIndex)[1] >= pCurrentPath->getMinQuadrantCoordY()) &&\
                    (pPointsToFind.at(currentComparisonIndex)[1] <= pCurrentPath->getMaxQuadrantCoordY())){

                    itsACoordinateMatch=true; //The path has at least one point of coincidence
                    PointInPath coincidenceCoordenate;
                    coincidenceCoordenate.xCoordinate = pPointsToFind.at(currentComparisonIndex)[0];
                    coincidenceCoordenate.yCoordinate = pPointsToFind.at(currentComparisonIndex)[1];
                    
                    pCurrentPath->addCoincidencePoint(coincidenceCoordenate);
                }
            }
            //This means that there is at least 1 coincidence
            if(itsACoordinateMatch){
                pSelectedPaths.push_back(pCurrentPath);  
            }
            
            return pSelectedPaths;
        }
};

#endif