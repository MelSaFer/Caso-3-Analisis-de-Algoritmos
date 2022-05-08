# ANIMATIONS IN SVG FILES
#### Case 3 
#### Instituto Tecnológico de Costa Rica
#### Análisis de Algoritmos
#### Estudiantes:
* **Melany Salas Fernández** 2021121147
* **Moises Solano Espinoza** 2021144322

At the beginning the svg is read and its data is analyzed, its size is saved, and the paths are read. Each one of these paths is converted to its absolute coordinates, its points are obtained and the quadrant that encloses it is calculated. After working the paths are sent to the selection algorithm.

## Algorithms Used
---------------------------------------------------------------------------------
### SELECTION - DIVIDE & CONQUER 
`n:` The svg paths <br>
`Divide:` each path <br>
`Conquer:` The selected path (check if there is a matching point inside the path area and that it has a similar color) <br>
`Merge:` The paths who where selected <br>
---------------------------------------------------------------------------------

---------------------------------------------------------------------------------
### ROUTING - BACKTRACKING
`n:` The selected svg paths from SELECTION <br>
`Solution Vector (implicit):` list of animation points, discarding those that do not generate significant movements <br>
`PODA:` with the final point calculated, the distance between the start and the end is calculated and divided by the number of frames, so only the necessary points will be made. <br>
---------------------------------------------------------------------------------

---------------------------------------------------------------------------------
### GENERATION - DYNAMIC PROGRAMMING 
`n:` The selected svg paths with their offset points <br>
`Stages:` The points (X,Y) that we are modifyng in the svg <br>
`Local Optimum:` The modifided points in the current path <br>
`Global Optimum:` All the new paths <br>
`Memorization:` We use the previus path to improve the current path <br>
---------------------------------------------------------------------------------