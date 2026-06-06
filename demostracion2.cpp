#include <iostream>
#include "solucion2.h"
#include <chrono>
using namespace std;

string base = "D1.txt"; // el .txt base con el que se creara la grilla
string entradas = "D2.txt";     // nombre del archivo de donde vienen las entradas

int main(){
    cout << "=================== Creacion de la Grilla ===================" << endl;
    // Creacion de la grilla

    nodo* raiz = nullptr;
    cout << "Creando la Grilla..." << endl;
    auto grilla_i = chrono::high_resolution_clock::now();   // empieza el cronometro
    
    grilla(&raiz, base);

    auto grilla_f = chrono::high_resolution_clock::now();   // termina el cronometro
    chrono::duration<double> grilla_d = grilla_f - grilla_i;// contenedor del tiempo que tardo en crearse la grilla

    cout << "Grilla creada" << endl;
    cout << "La grilla tardo: " << grilla_d.count() << " segundos en crearse." << endl;
    cout << "tiene: " << cantN << " nodos." << endl;
    cout << "Y pesa: " << (int)sizeof(nodo)*cantN << " bytes" << endl;
    
    cout << "==================== Busquedas ==================" << endl;
    string linea;                   // va tomando las palabras por linea
    ifstream diccionario2;
    diccionario2.open(entradas);
    int sear_cont = 0;              // contador de busquedas totales
    int sear_e = 0;                 // contador de busquedas exitosas
    
    auto buscar_i = chrono::high_resolution_clock::now(); // empieza el cronometro
    while(getline(diccionario2, linea)){
        if (superSearch(raiz, linea)) sear_e++;
        sear_cont++;
    }
    auto buscar_f = chrono::high_resolution_clock::now(); // termina el cronometro
    chrono::duration<double> buscar_d = buscar_f - buscar_i; // contenedor del tiempo que tardo en buscar todos los valores en la grilla
    
    cout << "Las busquedas tardaron: " << buscar_d.count() << " segundos en total." << endl;
    cout << "Se hicieron: " << sear_cont << " busquedas en total." << endl;
    cout << "Se hicieron: " << sear_e << " busquedas exitosas." << endl;
    
    diccionario2.close();
    //printLista(raiz);

    cout << "==================== Insersiones ==================" << endl;
    
    int nodos_i = cantN;            // cantidad de nodos antes de insertar
    int i = 0;
    diccionario2.open(entradas);
    auto insertar_i = chrono::high_resolution_clock::now(); // empieza el cronometro
    while(getline(diccionario2, linea) && i <= 5000){

        insertarNodo(&raiz, linea);
        i++;
    }
    auto insertar_f = chrono::high_resolution_clock::now(); // termina el cronometro
    chrono::duration<double> insertar_d = insertar_f - insertar_i; // contenedor del tiempo que tardo en insertarse los valores en la grilla

    int nodos_d = cantN - nodos_i;  // diferencia de nodos antes y despues de las insersiones

    
    cout << "Las insersiones tardaron: " << insertar_d.count() << " segundos en total." << endl;
    cout << "Se hicieron: " << inserciones << " insersiones." << endl;
    cout << "Se insertaron: " << nodos_d << " nodos." << endl;
    cout << "tiene: " << cantN << " nodos." << endl;
    cout << "Y pesa: " << (int)sizeof(nodo)*cantN << " bytes" << endl;

    diccionario2.close(); // cerramos el archivo
    //printLista(raiz);


    cout << "================== Eliminaciones ====================" << endl;
    nodos_i = cantN;
    i = 0;
    diccionario2.open(entradas);
    auto eliminar_i = chrono::high_resolution_clock::now(); // empieza el cronometro
    int eliminaciones_e = 0;
    
    while (getline(diccionario2, linea)){
        if (5000 <= i) if (superRemove(&raiz, linea)) eliminaciones_e++;
        //if (superRemove(&raiz, linea)) eliminaciones_e++;
        i++;
    }
    
    
    auto eliminar_f = chrono::high_resolution_clock::now(); // termina el cronometro
    chrono::duration<double> eliminar_d = eliminar_f - eliminar_i;
    diccionario2.close();

    cout << "Las eliminaciones tardaron: " << eliminar_d.count() << " segundos en total." << endl;
    cout << "Se hicieron: " << eliminaciones_e << " eliminaciones exitosas." << endl;
    cout << "Se eliminaron: " << nodos_i - cantN << " nodos." << endl;
    cout << "tiene: " << cantN << " nodos." << endl;
    cout << "Y pesa: " << (int)sizeof(nodo)*cantN << " bytes." << endl;
    
    //printLista(raiz);


    cout << "================== Fin :3 =====================" << endl;
    
    cout << "Peso final: " << (float)sizeof(nodo)*cantN/1000000 << " megabytes." << endl;


    return 0;
}
