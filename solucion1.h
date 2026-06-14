#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;
typedef unsigned char uchar;
//editado por vennus

int contador1(vector<uchar*>A){
    int suma=0; 
    for (uchar* i:A){
        suma=suma+1;
    }
    return suma;}

int contarpalabrita(uchar *palabra){
    int contador=0;
    while (palabra[contador]!='\0'){
        contador++;}
    return contador;}

int comparador(uchar*palabra1, uchar*palabra2){     
    int i=0;
    while(palabra1[i]!='\0' && palabra2[i]!='\0'){
        if (palabra1[i]<palabra2[i])
            return -1;
        if (palabra1[i]>palabra2[i])
            return 1;
        i++;}
    //caso para cuando haga la busqueda
    if (palabra1[i]=='\0' && palabra2[i]=='\0')
        return 0;
    //si se sale del while es pq una es prefijo de otra y debo preguntar
    if(palabra1[i]=='\0')
        return -1;
    return 1;}

int indicebinario(vector<uchar*>&diccionario, map<uchar, int>& letritas, uchar* palabra,int cantidad){
    int letra= palabra[0];
    int izq=letritas[letra];
    int der;
    //caso borde con la z
    if(letra == 'z')
        der = cantidad - 1;
    else
        der= letritas[letra + 1] - 1;
    while(izq<=der){
        int medio=(izq+der)/2;
        int comparacion= comparador(diccionario[medio], palabra);
        if (comparacion<0)
            izq=medio+1;
        else
            der=medio - 1;}
    return izq;}
        
    
        
void agregando(uchar*palabra,vector<uchar*>&diccionario, map<uchar, int>&abcedario, int& cantidad, int& capacidad){
    //caso borde, arreglo lleno
    int nuevacapacidad =capacidad * 2;
    vector<uchar*> nuevo(nuevacapacidad);

    if (cantidad==capacidad){
        for(int i=0;i<cantidad;i++){
            nuevo[i] =diccionario[i];}
        diccionario = nuevo;
        capacidad = nuevacapacidad;}

    int pos=indicebinario(diccionario, abcedario, palabra,cantidad);
    for (int i=cantidad; i>pos; i--){
        diccionario[i]=diccionario[i-1];}
    diccionario[pos]=palabra;
    cantidad++;
char c = palabra[0] + 1;

while (c <= 'z' && c != 'a') {

    abcedario[c]++;

    c++;
}}


int bus_binario (vector<uchar*>& diccionario, map<uchar,int>& abcedario, uchar* palabra, int cantidad){
    int letra = palabra[0];
    int izquierda = abcedario[letra];
    int derecha;
    if (letra=='z')
        derecha=cantidad-1;
    else{
        derecha=abcedario[letra+1]-1;
    }
    while(izquierda <= derecha){
        int medio = (izquierda + derecha) / 2;
        int comparacion = comparador(diccionario[medio], palabra);

        // La encontró
        if(comparacion == 0){

            return medio;
        }
        // palabra del medio es menor
        if(comparacion < 0)
            izquierda = medio + 1;


        // palabra del medio es mayor
        else
            derecha = medio - 1;
    }
    return -1;
}

void eliminando(uchar* palabra, vector<uchar*>&diccionario, map<uchar, int>&abcedario, int &cantidad){
    int indice_eliminar= indicebinario(diccionario, abcedario, palabra, cantidad);
    for(int i=indice_eliminar; i<cantidad-1; i++){
        diccionario[i]=diccionario[i+1];
    }
    cantidad--;
    char c = palabra[0] + 1;
    while (c <= 'z' && c!='a') {
        abcedario[c]--;
        c++;
}}