// c++ code
// en el archivo donde se hara la grulla hay que hacer #include "beta_2.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

# define K 2
int inserciones = 0;
int niveles = 0;
int cantN = 0;
// estructura de los nodos a utilizar
struct nodoDoble{
    string keys;
    nodoDoble* up = nullptr; // nodo superior
    nodoDoble* right = nullptr; // nodo a la derecha 
}; 
typedef struct nodoDoble nodo;

void grilla(nodo** R, string referencia){
    // Se abre el diccionario uno
    ifstream dicc1;
    dicc1.open(referencia);
    long count = 0;
    
    if (dicc1.is_open()){
        // Se inserta cada palabra a un nodo del primer nivel
        string linea;
        nodo* s = nullptr;
        while (getline(dicc1, linea)){
            nodo* q = new nodo;
            q->keys = linea;
            if (*R == nullptr)
                *R =  q;
            else
                s->right = q;
            s = q;
            count++;
            cantN++;
            
        }
        niveles++;
    }
    dicc1.close();
    
    // Seguimos para i niveles
    long n = count;
    
    while(n > K){
        int contador = 0;

        nodo* p = *R;

        nodo* s = nullptr;
        while(p != nullptr){
            if (contador % K == 0){
                nodo* q = new nodo;
                q->keys = p->keys;
                if (s == nullptr)
                    *R = q;
                else
                    s->right = q;
                q->up = p;
                s = q;
                cantN++;
                
            }
            p = p->right;
            contador++;
        }
        // El nivel tiene n nodos
        n = (n + K - 1)/K;
        niveles++;
    }

}

// imprime la lista completa
void printLista(nodo *R){
    if (R == nullptr) return;
    printLista(R->up);
    nodo *p = R;
    int cont = 0;
    while (p != nullptr) {
        cout << p->keys << " -> ";
        p = p->right;
        cont++;
    }
    cout << endl;
    //cout << "y tiene: " << cont << " nodos.";
    //cout << endl;
}


void insertarNodo(nodo **R, string nueva_key){
    //cout << "Insertando nodo.." << endl;
    nodo* q = new nodo;
    q->keys = nueva_key;
    // si la lista esta vacia
    if (*R == nullptr){
        *R = q;
        inserciones++;
        cantN++;
        return;
    }
    
    // si nueva keys es menor a la primera palabra
    if ((*R)->keys > nueva_key){
        nodo* p = *R;
        for (int i=1;i<=niveles;i++){
            if (i == 1){
                q->right = p;
                *R = q;
            }
            else{
                nodo* r = new nodo;
                r->keys = nueva_key;
                r->right = p;
                q->up = r;
                q = q->up;
            }
            p = p->up;
            cantN++;
            inserciones++;
        }
        return;
    }
    
    nodo* p = *R;
    while (true){
        // Recorre hacia la derecha
        while ((p->right) != nullptr && (p->right)->keys < nueva_key)   
            p = p->right;

        // Si puede recorre hacia arriba
        if (p->up != nullptr)
            p = p->up;
        
        // Else: No se puede subir más
        else break;
    }
    
    // Insertando nodo
    if (p->keys < nueva_key){
        if (p->right != nullptr && p->right->keys != nueva_key){
            q->right = p->right;
            p->right = q;
            inserciones++;
            cantN++;
            return;
        }
        if (p->right == nullptr){
            q->right = p->right;
            p->right = q;
            inserciones++;
            cantN++;
            return;
        }
    }
    delete q;
    return;
}

// Busca el primer nodo con el elemento "valor" y si lo encuentra retorna true
// Si no lo encuentra retorna false
bool superSearch(nodo* R, string valor){
    // Si busco en algo que no existe retorna true
    if (R == nullptr) return false;

    nodo* p = R; // nodo que recorre

    // Si esta en el primer nodo retorna true
    if (p->keys == valor) return true;

    // recorremos el nivel en el que estemos hasta quedar antes del valor o que el siguiente sea nulo
    while (p->right != nullptr && p->right->keys < valor) p = p->right;

    // si el nodo siguiente tiene el valor rotorna true
    if (p->right != nullptr && p->right->keys == valor) return true;

    // sino hacemos el mismo proceso en el nivel de arriba desde el nodo en el que nos quedamos
    else return superSearch(p->up, valor);


    return false;

}

bool superRemove(nodo** R, string valor){
    if ((*R) == nullptr) return false;
    
    nodo* p = *R;

    if (p->keys >= valor) return false;

    while(p->right != nullptr && p->right->keys < valor) p = p->right;

    if (p->right != nullptr && p->right->keys == valor) {
        nodo* aux = p->right;
        p->right = aux->right;
        aux->up = nullptr;
        delete aux;
        cantN--;
        superRemove(&(p->up), valor);
        return true;
    }
    else return superRemove(&(p->up), valor);
    return false;
}