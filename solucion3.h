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
    bool insert(nodoT* r, string valor);
    bool arbol::insertInNodo(nodoT* r, string key, int i);
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
        cout << "Se creo´ vacio porque n es mayor a K" << endl;
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
// inserta nodos con key = parametro de la funcion
//retorna true si lo logra, false si no
bool arbol::insert(nodoT* r, string key){
    // si nodo vacío
    if (r->keys[0] == ""){
        r->keys[0] = key;
        r->cantKeys++;
        return true;
    }
    // si key menor a la primera key en nodo
    if (r->keys[0]> key) return insert(r->hijos[0], key);

    // buscamos indice para insertar y si ya está en nodo => retorna falso
    int i = r->cantKeys - 1;
    bool inNodo = false;
    while (i >=0 && r->keys[i] > key){
        if (r->keys[i] == key) inNodo = true;
        i--;
    }
    if (inNodo) return false;

    // si key mayor a la ultima palabra
    if (r->keys[r->cantKeys - 1] < key){
        //si nodo lleno inserta en hijo derecho sino inserta en nodo
        return (r->cantKeys == K) ? (insert(r->hijos[K+1],key)) : (insertInNodo(r, key,));
    }
    
    // si nodo lleno inserta en hijo[i] sino inserta en nodo
    return (r->cantKeys == K) ? (insert(r->hijos[i+1], key)) : (insertInNodo(r, key, i + 1));
    
    return false;
}
bool arbol::insertInNodo(nodoT* r, string key, int i){
    for (int j=r->cantKeys; j>i; j--){
        r->keys[j] = r->keys[j-1];
    }
    r->keys[i] = key;
    return true;
}
// remueve el nodo con el elemento valor
// retorna true si lo logra, retorna false si no
bool arbol::remove(string valor){
    return false;
}
