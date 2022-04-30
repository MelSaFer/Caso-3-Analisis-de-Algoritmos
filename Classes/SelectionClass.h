//Libraries ---------------------------------------------------------------------------------------------
#ifndef SELECTION
#define SELECTION

#include <stdio.h>      
#include <stdlib.h>    
#include <iostream>
#include <vector>
#include <list>
#include <thread>
#include "Path.h"

#include "ObserverPattern.h"

using namespace std;


class Selection : public Subject{
    private:
        //Paths selecionados
        static const int ClassId = 1;
        list<Observer*> ObserversList; 

    public:
        

        Selection() {}
        ~Selection() {}

        void attach(Observer* pNewObserver) {
            ObserversList.emplace_back(pNewObserver);
        }

        void detach(Observer* pObserverDelete) {
            ObserversList.remove(pObserverDelete);
        }

        void notify(void* pClassId, vector<Path*> pPaths) {
            for (Observer* currentObserver: ObserversList) {
                thread t(&Observer::update, currentObserver, pClassId, pPaths); // parametros = (direccionDeMetodo, instancia/objeto, parametro)
                t.join(); // espere a que t termine
            }
        }

        int getClassId(){
            return ClassId;
        }

        /*------------------------------------------------------------------------------
        Function for selecting the paths who has coincidences in the list of
        points and colors
        ->Divide and Conquer Algorithm
            -n: Every path in the SVG
            -Divide: Path
            -Conquer: the selected path
            -Merge: The paths who has coincidences in at least one point and one color    
        -------------------------------------------------------------------------------*/

         /*
        In this section we divede our n in paths and call the funcion who analices** the coincidence in the path (selectionConquer)
        */
        vector<Path*> selecctionDivide(vector<Path*> pPathsInTheSVG, vector<string> pColorsToFind, vector<float*> pPointsToFind){
            vector<Path*> selectedPaths;

            for(int currentPathIndex = 0; currentPathIndex < pPathsInTheSVG.size(); currentPathIndex++){
                selectedPaths = this->selectionConquer(pPathsInTheSVG.at(currentPathIndex),selectedPaths, \
                    pColorsToFind, pPointsToFind);
            }

            return selectedPaths;
        }

        vector<Path*> selectionConquer(Path* pCurrentPath, vector<Path*> pSelectedPaths, vector<string> pColorsToFind, vector<float*> pPointsToFind){
            bool itsAMatch = false;
            int maxSizeInList = 0;

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

            if(pColorsToFind.size() > pPointsToFind.size()){
                maxSizeInList = pColorsToFind.size();
            } else{
                maxSizeInList = pPointsToFind.size();                
            }

            colorTextPathRed = pCurrentPath->getPathColor().substr(1,2).data();
            colorTextPathGreen = pCurrentPath->getPathColor().substr(3,2).data();
            colorTextPathBlue = pCurrentPath->getPathColor().substr(5,6).data();

            rgbColorsPath[0] = strtol(colorTextPathRed, NULL, 16);
            rgbColorsPath[1] = strtol(colorTextPathGreen, NULL, 16);
            rgbColorsPath[2] = strtol(colorTextPathBlue, NULL, 16);

            //cout << maxSizeInList << endl;
            
            for(int currentComparisonIndex = 0; currentComparisonIndex < maxSizeInList; ){
                // cout << "Trabajando" << endl;
                itsAMatch = false;
                if(currentComparisonIndex < pPointsToFind.size()){
                    if( (pPointsToFind.at(currentComparisonIndex)[0] >= pCurrentPath->getMinQuadrantCoordX()) && \
                        (pPointsToFind.at(currentComparisonIndex)[0] <= pCurrentPath->getMaxQuadrantCoordX()) && \
                        (pPointsToFind.at(currentComparisonIndex)[1] >= pCurrentPath->getMinQuadrantCoordY()) &&\
                        (pPointsToFind.at(currentComparisonIndex)[1] <= pCurrentPath->getMaxQuadrantCoordY())){
                        cout << "Match " << pCurrentPath->getIdentifier() << endl;
                        itsAMatch = true;
                        if( pColorsToFind.size() == 0){
                            pSelectedPaths.push_back(pCurrentPath);
                            //currentComparisonIndex++;
                        } //end special case
                    }//endComparing points
                }

                //COMPARISON OF COLORS-------------------------------------------------------------------------------
                

                if(currentComparisonIndex < pColorsToFind.size()){
                    colorTextRed = pColorsToFind.at(currentComparisonIndex).substr(1,2).data();
                    colorTextGreen = pColorsToFind.at(currentComparisonIndex).substr(3,2).data();
                    colorTextBlue = pColorsToFind.at(currentComparisonIndex).substr(5,6).data();
                    rgbColors[0] = strtol(colorTextRed, NULL, 16);
                    rgbColors[1] = strtol(colorTextGreen, NULL, 16);
                    rgbColors[2] = strtol(colorTextBlue, NULL, 16);
                    cout << rgbColors[0] << ", " << rgbColors[1] << ", " << rgbColors[2] << endl;

                    rgbDifferences[0] = abs((rgbColorsPath[0] - rgbColors[0]))/255 ;
                    rgbDifferences[1] = abs((rgbColorsPath[1] - rgbColors[1]))/255 ;
                    rgbDifferences[2] = abs((rgbColorsPath[2] - rgbColors[2]))/255 ;

                     cout << "Suma: " << rgbDifferences[0] << endl;

                    rbgComparison = ((rgbDifferences[0] + rgbDifferences[1] + rgbDifferences[2])/3)*100;

                    // cout << "La diferencia es de: " << rbgComparison << endl;

                    if(rbgComparison <= 15 && itsAMatch){
                        cout << "son colores parecidos e hizo match" << endl;
                        pSelectedPaths.push_back(pCurrentPath);
                        //currentComparisonIndex++;
                        //continue;
                    }
                }
                currentComparisonIndex++;
            }
            return pSelectedPaths;
        }

        vector<Path*> processOfSelection(vector<Path*> pPathsInTheSVG, vector<string> pColorsToFind, vector<float*> pPointsToFind){
            vector<Path*> selectedPaths;
            bool itsAMatch = false;

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

            for(int i =0; i < pPathsInTheSVG.size(); i++){
                // cout << "Color: " << pPathsInTheSVG.at(i)->getPathColor() << endl;

                for(int j = 0; j < pPointsToFind.size(); j++){
                    // cout << "Point = " << pPointsToFind.at(j)[0] << ", " << pPointsToFind.at(j)[1] << endl;
                    if( (pPointsToFind.at(j)[0] >= pPathsInTheSVG.at(i)->getMinQuadrantCoordX()) &&  (pPointsToFind.at(j)[0] <= pPathsInTheSVG.at(i)->getMaxQuadrantCoordX())\
                    && (pPointsToFind.at(j)[1] >= pPathsInTheSVG.at(i)->getMinQuadrantCoordY()) && (pPointsToFind.at(j)[1] <= pPathsInTheSVG.at(i)->getMaxQuadrantCoordY())){
                        cout << "Match " << pPathsInTheSVG.at(i)->getIdentifier() << endl;
                        itsAMatch = true;
                        if( pColorsToFind.size() == 0){
                            selectedPaths.push_back(pPathsInTheSVG.at(i));
                        }
                    }
                }

                colorTextPathRed = pPathsInTheSVG.at(i)->getPathColor().substr(1,2).data();
                colorTextPathGreen = pPathsInTheSVG.at(i)->getPathColor().substr(3,2).data();
                colorTextPathBlue = pPathsInTheSVG.at(i)->getPathColor().substr(5,6).data();

                rgbColorsPath[0] = strtol(colorTextPathRed, NULL, 16);
                rgbColorsPath[1] = strtol(colorTextPathGreen, NULL, 16);
                rgbColorsPath[2] = strtol(colorTextPathBlue, NULL, 16);


                for(int j = 0; j < pColorsToFind.size(); j++){

                    //string prueba = "eb4034";

                    colorTextRed = pColorsToFind.at(j).substr(1,2).data();
                    colorTextGreen = pColorsToFind.at(j).substr(3,2).data();
                    colorTextBlue = pColorsToFind.at(j).substr(5,6).data();
                    rgbColors[0] = strtol(colorTextRed, NULL, 16);
                    rgbColors[1] = strtol(colorTextGreen, NULL, 16);
                    rgbColors[2] = strtol(colorTextBlue, NULL, 16);
                    // cout << rgbColors[0] << ", " << rgbColors[1] << ", " << rgbColors[2] << endl;

                    rgbDifferences[0] = abs((rgbColorsPath[0] - rgbColors[0]))/255 ;
                    rgbDifferences[1] = abs((rgbColorsPath[1] - rgbColors[1]))/255 ;
                    rgbDifferences[2] = abs((rgbColorsPath[2] - rgbColors[2]))/255 ;

                    // cout << "Suma: " << rgbDifferences[0] << endl;

                    rbgComparison = ((rgbDifferences[0] + rgbDifferences[1] + rgbDifferences[2])/3)*100;

                    // cout << "La diferencia es de: " << rbgComparison << endl;

                    if(rbgComparison <= 15 && itsAMatch){
                        cout << "son colores parecidos: " << rgbColors[0] << ", " << rgbColors[1] << ", " << rgbColors[2] << endl;
                        cout << rgbColorsPath[0] << ", " << rgbColorsPath[1] << ", " << rgbColorsPath[2] << endl;
                        selectedPaths.push_back(pPathsInTheSVG.at(i));
                    }

                }
            }

            for(int i = 0; i < selectedPaths.size(); i++){
                //cout << selectedPaths.at(i)->getIdentifier()<< endl;
            }

            //cout << "Contador: " << contador << endl;

            cout << "============================================="  << endl;
            return selectedPaths;
        }

        vector<Path*> processOfSelection_nlogn(Path* currentPath ,vector<Path*> selectedPaths, vector<string> pColorsToFind, vector<float*> pPointsToFind){
            //vector<Path*> selectedPaths;
            bool itsAMatch = false;
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

            for(int j = 0; j < pPointsToFind.size(); j++){
                // cout << "Point = " << pPointsToFind.at(j)[0] << ", " << pPointsToFind.at(j)[1] << endl;
                if( (pPointsToFind.at(j)[0] >= currentPath->getMinQuadrantCoordX()) &&  (pPointsToFind.at(j)[0] <= currentPath->getMaxQuadrantCoordX())\
                && (pPointsToFind.at(j)[1] >= currentPath->getMinQuadrantCoordY()) && (pPointsToFind.at(j)[1] <= currentPath->getMaxQuadrantCoordY())){
                    //cout << "Match" << endl;
                    itsAMatch = true;
                    if( pColorsToFind.size() == 0){
                        selectedPaths.push_back(currentPath);
                    }
                }
            }

            colorTextPathRed = currentPath->getPathColor().substr(1,2).data();
            colorTextPathGreen = currentPath->getPathColor().substr(3,2).data();
            colorTextPathBlue = currentPath->getPathColor().substr(5,6).data();

            rgbColorsPath[0] = strtol(colorTextPathRed, NULL, 16);
            rgbColorsPath[1] = strtol(colorTextPathGreen, NULL, 16);
            rgbColorsPath[2] = strtol(colorTextPathBlue, NULL, 16);

            for(int j2 = 0; j2 < pColorsToFind.size(); j2++){

                //string prueba = "eb4034";

                colorTextRed = pColorsToFind.at(j2).substr(1,2).data();
                colorTextGreen = pColorsToFind.at(j2).substr(3,2).data();
                colorTextBlue = pColorsToFind.at(j2).substr(5,6).data();
                rgbColors[0] = strtol(colorTextRed, NULL, 16);
                rgbColors[1] = strtol(colorTextGreen, NULL, 16);
                rgbColors[2] = strtol(colorTextBlue, NULL, 16);
                //cout << rgbColors[0] << ", " << rgbColors[1] << ", " << rgbColors[2] << endl;

                rgbDifferences[0] = abs((rgbColorsPath[0] - rgbColors[0]))/255 ;
                rgbDifferences[1] = abs((rgbColorsPath[1] - rgbColors[1]))/255 ;
                rgbDifferences[2] = abs((rgbColorsPath[2] - rgbColors[2]))/255 ;

                // cout << "Suma: " << rgbDifferences[0] << endl;

                rbgComparison = ((rgbDifferences[0] + rgbDifferences[1] + rgbDifferences[2])/3)*100;

                // cout << "La diferencia es de: " << rbgComparison << endl;

                if(rbgComparison <= 15 && itsAMatch){
                    cout << "son colores parecidos" << endl;
                    selectedPaths.push_back(currentPath);
                }
            }
        return selectedPaths;
        }


        void estoEsPrueba(){
            cout << "HOLA"<< endl;
        }

};

#endif