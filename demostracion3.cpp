#include "solucion3.h"
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <chrono>

string d1 = "D1.txt";
string d2 = "D2.txt";
#define largo_d1 69904
#define largo_d2 10000

void arbol::cargarDiccionario(vector<string>& palabras, int l, int ri){
    cargarDiccionario(palabras, l, ri, &R);
}

void arbol::cargarDiccionario(vector<string>& palabras, int l, int ri, nodoT** nodo){
    if (l > ri) return;
    int n = ri - l + 1;

    //  si los elementos del array son menor a la separación => inserta directamente
    if (n <= K - 1){
        for (int i = l; i <= ri; i++)
            insert(nodo, palabras[i]);
        return;
    }

    // calcular los K-1 separadores
    vector<int> sep(K - 1);
    for (int i = 0; i < K - 1; i++)
        sep[i] = l + ((i + 1) * n) / K;  // (i+1)*n/K evita error acumulado

    // insertar los K-1 separadores en el nodo actual
    for (int i = 0; i < K - 1; i++)
        insert(nodo, palabras[sep[i]]);

    // recursar en los K subrangos hacia cada hijo
    // subrango 0: [l, sep[0]-1]
    cargarDiccionario(palabras, l, sep[0] - 1, &((*nodo)->hijos[0]));

    // subrangos intermedios: [sep[i]+1, sep[i+1]-1]
    for (int i = 0; i < K - 2; i++)
        cargarDiccionario(palabras, sep[i] + 1, sep[i + 1] - 1, &((*nodo)->hijos[i + 1]));

    // subrango final: [sep[K-2]+1, ri]
    cargarDiccionario(palabras, sep[K - 2] + 1, ri, &((*nodo)->hijos[K - 1]));
}

int main(){
    srand(time(nullptr));
    arbol raiz;
    
    
    vector<string> palabras_d1;
    vector<string> palabras_d2;
    string palabra;

    // Leer diccionario 1
    ifstream archivo_1(d1);
    while(archivo_1 >> palabra)
        palabras_d1.push_back(palabra);
    archivo_1.close();
    cout << "Arreglo 1 creado" << endl;

    // Leer diccionario 2
    ifstream archivo_2(d2);
    while(archivo_2 >> palabra)
        palabras_d2.push_back(palabra);
    archivo_2.close();
    cout << "Arreglo 2 creado" << endl;

    // Cargar en el árbol de forma balanceada
    cout << "================Creacion================" << endl;

    auto inicio = chrono::high_resolution_clock::now(); // inicia el cronometro
    raiz.cargarDiccionario(palabras_d1, 0, palabras_d1.size() - 1);
    auto fin = chrono::high_resolution_clock::now(); // fin del cronometro
    chrono::duration<double> duracion_creacion = fin - inicio;

    cout << "Tiempo de creación: " << duracion_creacion.count() << endl;
    cout << "cantidad de nodos: " << raiz.getCantN() << endl;
    cout << "Peso del arbol: " << ((float)sizeof(nodoT)*(float)raiz.getCantN())/1000000 << " megabytes" << endl;

    // buscamos palabras al "azar" del diccionario 1
    
    cout << "================Busqueda================" << endl;
    int claves_encontradas = 0;
    
    inicio = chrono::high_resolution_clock::now();
    for (int i = 0; i < 10000; i++){
        int numero_aleatorio = rand()%largo_d2;
        if (raiz.search(palabras_d2[numero_aleatorio])) claves_encontradas++;
    }
    fin = chrono::high_resolution_clock::now();
    chrono::duration<double> duracion_busquedas = fin - inicio;
    
    cout << "Claves encontradas: " << claves_encontradas << endl;
    cout << "Tiempo de busquedas: " << duracion_busquedas.count() << endl;
    
    cout << "================Insersion================" << endl;

    int claves_insertadas = 0;
    
    inicio = chrono::high_resolution_clock::now();
    for (int i = 0; i < 5000; i++){
        int numero_aleatorio = rand()%largo_d2;
        if (raiz.insert(palabras_d2[numero_aleatorio])) claves_insertadas++;
    }
    fin = chrono::high_resolution_clock::now();
    chrono::duration<double> duracion_insersiones = fin - inicio;
    
    cout << "Claves insertadas: " << claves_insertadas << endl;
    cout << "Tiempo de insersiones: " << duracion_insersiones.count() << endl;
    cout << "cantidad de nodos: " << raiz.getCantN() << endl;
    cout << "Peso del arbol: " << ((float)sizeof(nodoT)*(float)raiz.getCantN())/1000000 << " megabytes" << endl;
    
    cout << "================eliminacion================" << endl;

    int claves_removidas = 0;
    
    inicio = chrono::high_resolution_clock::now();
    for (int i = 0; i < 5000; i++){
        int numero_aleatorio = rand()%largo_d2;
        if (raiz.remove(palabras_d2[numero_aleatorio])) claves_removidas++;
    }
    fin = chrono::high_resolution_clock::now();
    chrono::duration<double> duracion_eliminaciones = fin - inicio;
    
    cout << "Claves removidas: " << claves_removidas << endl;
    cout << "Tiempo de eliminación: " << duracion_eliminaciones.count() << endl;
    cout << "cantidad de nodos: " << raiz.getCantN() << endl;
    cout << "Peso del arbol: " << ((float)sizeof(nodoT)*(float)raiz.getCantN())/1000000 << " megabytes" << endl;
    
    cout << "================Fin================" << endl;

    return 0;
}