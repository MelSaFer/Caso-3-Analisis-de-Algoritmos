#ifndef PRODUCERCONSUMER
#define PRODUCERCONSUMER

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include <queue>
#include <iostream>
#include <fstream>
#include <thread>
//#include <Classes/Path.h>



using namespace std;
int opcion;
queue<Path*> pathQueue;  //Queue of paths



void productor(){
    //for(int currentPathIndex = 0 ; currentPathIndex < allPaths.size(); currentPathIndex++ ){
        //Modificacion del path
    //}
    //for(int )
    // int salida=false;
    // while(!salida){
    //     Sleep(1000);
    //     menu();
    //     cin>>opcion;

    //     switch(opcion){
    //         case 1:
    //             cola.push("Hola Mundo\n");
    //             break;
    //         case 2:
    //             cola.push("La casa es roja\n");
    //             break;
    //         case 3:
    //             cola.push("Labios color cereza\n");
    //             break;
    //         case 4:
    //             cola.push("Salir");
    //             salida=true;
    //             break;
    //         default:
    //             cout<<"Opcion invalida";
    //             break;
    //     }
    //     cout<<"Producto generado...\n";
    // }

}

void consumidor(){
    // bool salir=false;
    // ofstream file;
    // file.open("archivo.txt",ios_base::app | ios_base::in);
    // while(!salir){
    //     Sleep(4000);
    //     if(!cola.empty()){
    //         if(cola.front()!="Salir"){
    //             file << cola.front();
    //             cola.pop();
    //             cout<<"\n\nProcesando producto...\n";
    //         }
    //         else{
    //             break;
    //         }
    //     }
    //     else{
    //         cout<<"\n\nCola vacia, esperando producto...\nSeleccione una opcion: ";
    //         //menu();
    //     }

    // }
    // file.close();
    // cout<<"Archivo cerrado";
}


// int main(){
//     //Declarando los hilos
//     //thread hilo1(productor);

//     thread hilo2(consumidor);
//     productor();

//     //join permite que un hilo espere a que otro termine su ejecuci�n
//     //hilo1.join();
//     hilo2.join();

// }


#endif
