#include "solucion3.h"
#include <fstream>

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
    cout << "cantidad de nodos: " << sudowodo.getCantN() << endl;
    cout << "Peso del arbol: " << sizeof(nodoT) << endl;
    

    sudowodo.remove("10");
    sudowodo.remove("13");
    sudowodo.print();
    cout << "cantidad de nodos: " << sudowodo.getCantN() << endl;


    return 0;
}