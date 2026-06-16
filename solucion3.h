#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int K = 4; 
int pos=0;   // define como se creara el arbol

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
    void cargarDiccionario(vector<string>& palabras, int l, int ri);
    void print();
    void print(nodoT* p);

    nodoT* getRoot();
    int getCantN();

    bool search(string valor);

    bool insert(string valor);
    bool insert(nodoT** r, string valor);
    bool insertInNodo(nodoT* p,string key);
    bool binarySearchRec(string* keys, int l, int r, string x);

    bool remove(string valor);
    bool remove(string valor, nodoT* p, int &pos);
    bool nodoLLeno(nodoT* p);
    nodoT* buscarnodo(nodoT*p, string valor );
    nodoT* obtenerPadre(nodoT* hijoBuscado);
    nodoT* obtenerPadreRec(nodoT* actual, nodoT* hijoBuscado);


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
int arbol::getCantN(){
    return cantN;
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
bool arbol::insert(string valor){
    return insert(&R, valor);
}

// inserta nodos con key = parametro de la funcion
//retorna true si lo logra, false si no
bool arbol::insert(nodoT** r, string key){
    // si nodo vacío
    if (*r == nullptr){
        *r = new nodoT;
        cantN++;
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

bool arbol::binarySearchRec(string* keys, int l, int r, string x){
    if (l > r) return false;
    int m = (l + r) / 2;
    if (x < keys[m]) return binarySearchRec(keys, l, m-1, x);
    if (x == keys[m]) return true;
    return binarySearchRec(keys, m+1, r, x);
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
bool arbol::remove(string valor){
    return remove(valor, R, pos);
}
bool arbol::remove(string valor, nodoT* p, int &pos){
    // busca el nodo que contiene el elemento a eliminar
    p = buscarnodo(R, valor);
    //si el nodo no exixte, no se elimina nada
    if (p == nullptr)
        return false;
    // verifica que la posicion sea válida
    if (pos >= p->cantKeys || p->keys[pos] != valor)
        return false;

    // Verificar si es hoja 
    bool esHoja = true;
    for (int i = 0; i <= K; i++){
        if (p->hijos[i] != nullptr){
            esHoja = false;
            break;
        }
    }
    //caso 1: es hoja 
    if (esHoja){
        //si el nodo tienen un solo elemento
        if (p->cantKeys == 1){
            //obtiene al padre del nodo
            nodoT* padre = obtenerPadre(p);
            // si tiene padre, se desconecta del nodo
            if(padre != nullptr){
                for(int i = 0; i <= padre->cantKeys; i++){
                    if(padre->hijos[i] == p){
                        padre->hijos[i] = nullptr;
                        break;
                    }
                }
            }
            else{
                // si es raiz el arbol queda vacio
                R = nullptr;
            }
            delete p;
            cantN--;
            return true;
        }
        //si el nodo tiene mas de un elemento mueve  los elementos hacia la izquierda
        for(int i = pos; i < p->cantKeys - 1; i++){
            p->keys[i] = p->keys[i + 1];
        }
        //reduce la cantidad de elementos
        p->cantKeys--;
        //limpia la ultima posicion 
        p->keys[p->cantKeys] = "";
        return true;
    }
    //caso 2: el nodo no es hoja
    if(pos + 1 > p->cantKeys)// verifica que exista el hijo derecho
        return false;
    // busca el subarbol derecho del elemento a eliminar
    nodoT* menor = p->hijos[pos + 1];

    if (menor == nullptr)
        return false;
    //encuentra el menor elemento del subarbol derecho
    while (menor->hijos[0] != nullptr){
        menor = menor->hijos[0];
    }
    if (menor->cantKeys == 0)
    return false;

    p->keys[pos] = menor->keys[0];
    for(int i = 0; i < menor->cantKeys - 1; i++){
        menor->keys[i] = menor->keys[i + 1];
    }

    menor->cantKeys--;
    menor->keys[menor->cantKeys] = "";

    if(menor->cantKeys == 0){// si el nodo sucesor queda vacio
        nodoT* padre = obtenerPadre(menor);//obtiene el padre del nodo vacia
        nodoT* reemplazo = nullptr;// busca un posible hijo para reemplazarlo
        for(int i = 0; i <= K; i++){
            if(menor->hijos[i] != nullptr){
                reemplazo = menor->hijos[i];
                break;
            }
        }
        //reconecta al arbol
        if(padre != nullptr){
            for(int i = 0; i <= padre->cantKeys; i++){
                if(padre->hijos[i] == menor){
                    padre->hijos[i] = reemplazo;
                    break;
                }
            }
        }
        else{
            // actualiza la raiz 
            R = reemplazo;
        }
        delete menor;
        cantN --;
    }
    return true;
}

nodoT* arbol::buscarnodo(nodoT*p, string valor ){
    p=R;//busqueda desde la raiz
    while (p != nullptr){//recorre el arbol mientras no sea vacio
        pos =0;
        if (p->cantKeys == 0)// si no tiene elementos la busqueda termina 
            return nullptr;
        if (p->keys[0] > valor){//si el valor es menor, continua por el hijo izquierdo
            p = p->hijos[0];    
        }
        else {// busca la posicion en donde deberia estar el nodo
            while (pos < p->cantKeys && p->keys[pos] < valor) {
                pos++;
            }//si el elemento fue encontrado, retorna al nodo
            if ( pos < p->cantKeys && p->keys[pos] == valor) 
                return p;
            else {
               p = p->hijos[pos];
            }
        }
    }
    return nullptr;// el elemento no existe en el arbol
}

nodoT* arbol::obtenerPadre(nodoT* hijoBuscado) {
    //si el arbol esta vacio o si el nodo es raiz no hay un padre para retornar
    if (R == nullptr || R == hijoBuscado)
        return nullptr; 
    //busqueda recursiva desde la raiz
    return obtenerPadreRec(R, hijoBuscado);
}

nodoT* arbol::obtenerPadreRec(nodoT* actual, nodoT* hijoBuscado) {
    if (actual == nullptr)//si el nodo es nulo, no busca nada
        return nullptr;
    //recorre los hijos para verificar si alguno es el nodo que se esta buscando
    for (int i = 0; i <= actual->cantKeys; i++) {
        if (actual->hijos[i] == hijoBuscado)
            return actual;// es el padre
    }
   //si no se encontro con los hijos se busca recursivamente
    for (int i = 0; i <= actual->cantKeys; i++) {
        nodoT* padre = obtenerPadreRec(actual->hijos[i], hijoBuscado);
        if (padre != nullptr)
            return padre;// si encontro al padre lo retorna 
    }
    //retorna nullptr si no se encuentra en ese subarbol
    return nullptr;
}