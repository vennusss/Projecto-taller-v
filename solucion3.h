#include <iostream>
#include <string>
using namespace std;

const int K = 4;    // define como se creara el arbol

// Estructura de los nodos
struct TNodo{
    string keys[K]; // arreglo que contiene K elementos
    TNodo* hijos[K+1]; // arreglo que contiene [k+1] hijos del nodo
    int cantKeys = 0;
}; typedef struct TNodo nodoT;

// Arbol General
class arbol{
    private:
    // Nodo principal del Arbol (Raiz)
    nodoT* R = nullptr;
    
    int cantN = 0;
    
    public:
    // Funciones por defecto
    arbol(); 
    arbol(string entradas[], int n);
    ~arbol();

    // Funciones a utilizar
    void construye_arbol(nodoT** R);
    void print();
    void print(nodoT* p);
    nodoT* getRoot();
    int getK();
    bool search(string valor);
    bool insert(string valor);
    bool insertInNodo(nodoT** p,string key);
    bool remove(string valor);
    bool nodoLLeno(nodoT* p);

};

// Crea el arbol vacio
arbol::arbol(){
    R = NULL;
}

arbol::arbol(string entradas[], int n){
    
}

// Destructor del objeto
arbol::~arbol(){
    
}

// obtiene la raiz
nodoT* arbol::getRoot(){
    return R;
}

void arbol::print(){    
    print(R);
    cout << endl;
}

void arbol::print(nodoT* p){  
    // si es null no imprime nada  
    cout << "|";
        
    if (p == nullptr){ 
        cout << "-| ";
        return;
}
    for (int i = 0; i < p->cantKeys-1; i++){
        cout << p->keys[i] << "-";
    }
    if (p->cantKeys != 0)  cout << p->keys[p->cantKeys-1] << "|\033[31m[\033[0m ";

    for (int i = 0; i <= K; i++){
        print(p->hijos[i]);
    }
    cout << "\033[31m ]\033[0m ";

}

bool arbol::nodoLLeno(nodoT* p){
    return (p->cantKeys == K) ? true : false;
}


// inserta nodos con key = parametro de la funcion
//retorna true si lo logra, false si no
bool arbol::insert(string key){
    if (R == nullptr){
        nodoT* nuevo = new nodoT;
        nuevo->cantKeys++;
        nuevo->keys[0] = key;
        for (int i = 0; i <= K; i++){
            nuevo->hijos[i] = nullptr;
        }
        R = nuevo;
        return true;
    }
    nodoT* q = R;
    while (q != nullptr){
        nodoT* p = q;
        int pos = 0;
        if (q->keys[0] > key){
            if (nodoLLeno(q)){
                p = q;
                q = q->hijos[0];
            }
            else {
                return insertInNodo(&q, key);
            }
        }
              
    }
    return false;
}
bool arbol::insertInNodo(nodoT** p, string key){
    int pos = 0;
    nodoT* q = *p;
    for (int i = 0; i < q->cantKeys-1; i++){
        if (q->keys[i] == key) return false;
        if (q->keys[i] < key){
            pos++;
        }
        else break;
    }
    for (int i = q->cantKeys; i > pos; i--){
        q->keys[i] = q->keys[i-1];
    }
    q->keys[pos] = key;
    q->cantKeys++;
    return true;
}

/*
Busca el valor dado dentro del arbol

Si lo encuentra retorna true, si no lo encuentra retorna falso

No lo encuentra cuando el nodo en el que se busca es nulo
*/
bool arbol::search(string valor){
    
    nodoT* p = R;  // nodo que recorre, empzando en la raiz
    // si el nodo en el que se busca es nulo entonces pasara a retornar falso
    while (p != nullptr){
        // si el valor es menor al primer elemento buscara en el hijo que contenga los menores a ese elemento
        if (p->keys[0] > valor){
            p = p->hijos[0];    
        }
        else {
            int pos = 0;
            // si el valor esta en la primera posicion entonces retornara true
            if (p->keys[pos] == valor){
                return true;
            }
            // recorrera hasta que el elemento en la posicion sea mayor o igual al valor | si es mayor al del final quedara n la posicion n+1 que es la del hijo "mayor"
            while (pos < p->cantKeys && p->keys[pos] < valor) {
                pos++;
            }

            // si el elemento en la posicion es igual al valor retornara true
            if (p->keys[pos] == valor) return true;

            // si no buscara en el hijo que este en la respectiva posicion
            else {
               p = p->hijos[pos];
            }
        }

    }
    return false;
}