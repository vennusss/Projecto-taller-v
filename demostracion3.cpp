#include "solucion3.h"
#include <fstream>

void arbol::cargarDiccionario(vector<string>& palabras, int l, int ri){
    if (l > ri) return;

    int m = (l + ri) / 2;

    // Insertar la palabra del medio primero
    insert(&R, palabras[m]);

    // Luego recursivamente la mitad izquierda y derecha
    cargarDiccionario(palabras, l, m - 1);
    cargarDiccionario(palabras, m + 1, ri);
}
int main(){
    arbol sudowodo;
    vector<string> palabras;
    string palabra;

    // Leer diccionario ordenado
    ifstream archivo("prueba.txt");
    while(archivo >> palabra)
        palabras.push_back(palabra);
    archivo.close();

    // Cargar en el árbol de forma balanceada
    sudowodo.cargarDiccionario(palabras, 0, palabras.size() - 1);
    sudowodo.print();
    cout << "cantidad de nodos: " << sudowodo.getCantN() << endl;
    cout << "Peso del arbol: " << sizeof(nodoT) << endl;
    

    sudowodo.remove("10");
    sudowodo.remove("13");
    sudowodo.print();
    cout << "cantidad de nodos: " << sudowodo.getCantN() << endl;


    return 0;
}