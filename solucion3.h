#include <iostream>
#include <string>
using namespace std;

const int K = 2;    // define como se creara el arbol

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
    void print();
    void print(nodoT* p);
    nodoT* getRoot();
    int getK();
    bool search(string valor);
    bool insert(string valor);
    bool remove(string valor);
};

// Crea el arbol vacio
arbol::arbol(){
    this->R = NULL;
}

// Crea el arbol con un nodo y un valor "val" dentro de ese nodo
// Solo si n es igual al K
arbol::arbol(string entradas[], int n){
    if (n <= K){
        cout << "Se esta creando la raiz" << endl;
        nodoT* nuevo = new nodoT; // se crea el nodo

        // en cada posicion en el arreglo se le ingresa su respectivo valor de entrada
        for (int i = 0; i < n; i++){
            nuevo->keys[i] = entradas[i]; 
            nuevo->cantKeys++;
        }

        // dejamos nulos sus hijos
        for (int i = 0; i <= K; i++){
            nuevo->hijos[i] = nullptr;
        }
        
        // definimos R como el nuevo nodo y sumamos a la cantidad de nodos
        R = nuevo;
        cantN++;
    }
    else {
        cout << "Se creo vacio porque n es mayor a K" << endl;
        this->R = nullptr;
    }
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
    cout << p->keys[p->cantKeys-1] << "|/";

    for (int i = 0; i < K; i++){
        print(p->hijos[i]);
    }

}

// remueve el nodo con el elemento valor
// retorna true si lo logra, retorna false si no
bool arbol::remove(string valor){
    return false;
}
