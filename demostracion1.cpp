#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <map>
#include "solucion2.h"
using namespace std;

typedef unsigned char uchar;

struct palabras{
    unsigned char* palabra;
    int largo;
    int asciiletra;
};

int main() {
    ifstream archivoD1("D1.txt");
    if (!archivoD1)
        return 1;

    int capacidad = 70000;
    int cantidad = 0;
    vector<uchar*> diccionario(capacidad);

    map<uchar, int> abcedario = {
        {'a',0},{'b',0},{'c',0},{'d',0},{'e',0},
        {'f',0},{'g',0},{'h',0},{'i',0},{'j',0},
        {'k',0},{'l',0},{'m',0},{'n',0},{'o',0},
        {'p',0},{'q',0},{'r',0},{'s',0},{'t',0},
        {'u',0},{'v',0},{'w',0},{'x',0},{'y',0},
        {'z',0}
    };

    string palabra;
    while (archivoD1 >> palabra) {
        int largo = 0;
        while (palabra[largo] != '\0') {
            largo++;
        }
        uchar* nuevapalabra = new uchar[largo + 1];
        for (int i = 0; i < largo; i++) {
            nuevapalabra[i] = (uchar)palabra[i];
        }
        nuevapalabra[largo] = '\0';
        agregando(nuevapalabra, diccionario, abcedario, cantidad, capacidad);
    }
    archivoD1.close();
    int maximo = cantidad;

for(int j = 0; j < maximo; j++){
    if (diccionario[j][0] == 'b') 
        abcedario['b'] = j;
    if (diccionario[j][0] == 'c') 
        abcedario['c'] = j;
    if (diccionario[j][0] == 'd') 
        abcedario['d'] = j;
    if (diccionario[j][0] == 'e') 
        abcedario['e'] = j;
    if (diccionario[j][0] == 'f') 
        abcedario['f'] = j;
    if (diccionario[j][0] == 'g') 
        abcedario['g'] = j;
    if (diccionario[j][0] == 'h') 
        abcedario['h'] = j;
    if (diccionario[j][0] == 'i') 
        abcedario['i'] = j;
    if (diccionario[j][0] == 'j') 
        abcedario['j'] = j;
    if (diccionario[j][0] == 'k') 
        abcedario['k'] = j;
    if (diccionario[j][0] == 'l') 
        abcedario['l'] = j;
    if (diccionario[j][0] == 'm') 
        abcedario['m'] = j;
    if (diccionario[j][0] == 'n') 
        abcedario['n'] = j;
    if (diccionario[j][0] == 'o') 
        abcedario['o'] = j;
    if (diccionario[j][0] == 'p') 
        abcedario['p'] = j;
    if (diccionario[j][0] == 'q') 
        abcedario['q'] = j;
    if (diccionario[j][0] == 'r') 
        abcedario['r'] = j;
    if (diccionario[j][0] == 's') 
        abcedario['s'] = j;
    if (diccionario[j][0] == 't') 
        abcedario['t'] = j;
    if (diccionario[j][0] == 'u') 
        abcedario['u'] = j;
    if (diccionario[j][0] == 'v') 
        abcedario['v'] = j;
    if (diccionario[j][0] == 'w') 
        abcedario['w'] = j;
    if (diccionario[j][0] == 'x') 
        abcedario['x'] = j;
    if (diccionario[j][0] == 'y') 
        abcedario['y'] = j;
    if (diccionario[j][0] == 'z') 
        abcedario['z'] = j;
}

    vector<uchar*> insercion;
    vector<uchar*> busqueda;
    vector<uchar*> eliminacion;

    ifstream contarD2("D2.txt");
    int total = 0;
    while (contarD2 >> palabra) {
        total++;
    }
    contarD2.close();

    ifstream archivoD2("D2.txt");
    int posicion = 0;
    while (archivoD2 >> palabra) {
        int largo = 0;
        while (palabra[largo] != '\0') {
            largo++;
        }
        uchar* nuevapalabra = new uchar[largo + 1];        
        for (int i = 0; i < largo; i++) {
            nuevapalabra[i] = (uchar)palabra[i];
        }
        nuevapalabra[largo] = '\0';
        if (posicion < 5000) {
            insercion.push_back(nuevapalabra);
        }
        if (posicion < 10000) {
            busqueda.push_back(nuevapalabra);
        }
        if (posicion >= total - 5000) {
            eliminacion.push_back(nuevapalabra);
        }
        posicion++;
    }
    archivoD2.close();

    //calcular el tiempo
    auto inicio_insersision = chrono::high_resolution_clock::now();
    for (uchar* palabra : insercion) {
        agregando(palabra, diccionario, abcedario, cantidad, capacidad);
    }
    auto fin_insersion = chrono::high_resolution_clock::now();
    chrono::duration<double> insersion_duracion = fin_insersion - inicio_insersision;
    cout << insersion_duracion.count() << endl;
    
    int memoria_insercion   = (int)sizeof(diccionario[0]) * contador1(insercion);
    cout << "Bytes de inserccion: " << memoria_insercion << " bytes" << endl;
   

    auto inicio_busqueda = chrono::high_resolution_clock::now();
    for (uchar* palabra : busqueda) {
        bus_binario(diccionario, abcedario, palabra, cantidad);
    }

    auto fin_busqueda = chrono::high_resolution_clock::now();
    chrono::duration<double> busqueda_duracion = fin_busqueda - inicio_busqueda;
    cout << busqueda_duracion.count() << endl;
    
    int memoria_busqueda    = (int)sizeof(diccionario[0]) * contador1(busqueda);
    cout << "Bytes de busqueda: " << memoria_busqueda << " bytes" << endl;




    auto inicio_eliminacion = chrono::high_resolution_clock::now();
    for (uchar* palabra : eliminacion) {
        eliminando(palabra, diccionario, abcedario, cantidad);
    }

    auto fin_eliminacion = chrono::high_resolution_clock::now();
    chrono::duration<double> eliminacion_duracion = fin_eliminacion - inicio_eliminacion;
    cout << eliminacion_duracion.count() << endl;

    int memoria_eliminacion = (int)sizeof(diccionario[0]) * contador1(eliminacion);
    cout << "Bytes de eliminacion: " << memoria_eliminacion << " bytes" << endl;

    for (int i = 0; i < cantidad; i++) {
        delete[] diccionario[i];
    }

    int memoria = (int)sizeof(diccionario[0]) * cantidad;
    cout << memoria << " bytes"<< endl;
    memoria = (8+1)*26;
    cout << memoria << " bytes";
    return 0;
}   
