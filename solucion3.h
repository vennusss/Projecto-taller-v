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
    bool insert(nodoT** r, string valor);
    bool arbol::insertInNodo(nodoT* r, string key);
    bool remove(string valor);

};

// Crea el arbol vacio
arbol::arbol(){
    this->R = NULL;
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
    cout << p->keys[p->cantKeys-1] << "|\033[31m[\033[0m ";

    for (int i = 0; i <= K; i++){
        print(p->hijos[i]);
    }
    cout << "\033[31m ]\033[0m ";

}
// inserta nodos con key = parametro de la funcion
//retorna true si lo logra, false si no
bool arbol::insert(nodoT** r, string key){
    // si nodo vacío
    if (*r == nullptr){
        *r = new nodoT;
        for (int i=0;i<=K;i++) (*r)->hijos[i] = nullptr;
        (*r)->keys[0] = key;
        (*r)->cantKeys++;
        return true;
    }
    nodoT* p = *r;
    bool inNodo = false;
    // si nodo lleno
    if (p->cantKeys == K ){
        // si key es menor a primera key en nodo
        if (p->keys[0] > key) return insert(&(p->hijos[0]), key);
        // si key es mayor a ultima key
        if (p->keys[K-1] < key) return insert(&(p->hijos[K]), key);
        // buscamos indice donde insertar, si está en nodo => retorna falso
        int i = K-1;
        while (i >= 0 && p->keys[i] >= key){
            if (p->keys[i] == key) inNodo = true;
            i--;
        }
        if (inNodo) return false;
        
        return insert(&(p->hijos[i + 1]), key);
    }
    else{
        return insertInNodo(p, key);
    }
    return false;
}
bool arbol::insertInNodo(nodoT* r, string key){
    nodoT* p = r;
    // si key en arreglo => no inserta
    if (binarySearchRec(p->keys, 0, p->cantKeys - 1, key)) return false;

    int i = p->cantKeys;
    // buscamos indice donde insertar
    while (i > 0 && p->keys[i - 1] > key){
        p->keys[i] = p->keys[i - 1];
        i--;
    }
    p->keys[i] = key;
    p->cantKeys++;
    return true;
}

bool binarySearchRec(string* keys, int l, int r, string x){
    if (l > r) return false;
    int m = (l + r) / 2;
    if (x < keys[m]) return binarySearchRec(keys, l, m-1, x);
    if (x == keys[m]) return true;
    return binarySearchRec(keys, m+1, r, x);
}

/*
Busca el valor dado dentro del arbol de forma no recursiva

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