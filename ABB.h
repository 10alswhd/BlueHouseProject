//
//  ABB.h
//  Arboles Binarios
//

#ifndef Arboles_Binarios_ABB_h
#define Arboles_Binarios_ABB_h
using namespace std;
#include <queue>

class NodoArbol{
public:
    int info;
    NodoArbol *izq, *der;
    NodoArbol( ){ izq = der = NULL; }
    NodoArbol(int dato)
    { info = dato; izq = der = NULL; }
};

class ABB {
private:
    NodoArbol *raiz;
public:
    ABB(){
        raiz = NULL;
    }
    ~ABB(){
    }
    bool busca (int valor){
        NodoArbol * p = raiz;
        while (p != NULL)
        {
            if (p->info == valor)
                return true;
            else
                p=(p->info > valor? p->izq: p->der);
        }
        return false;
    }
    NodoArbol* encuentraPadre (int valor){
        NodoArbol *padre, *hijo;
        hijo = raiz;
        padre = NULL;
        while (hijo != NULL && hijo->info != valor){
            padre = hijo;
            hijo = (hijo->info > valor ? hijo->izq : hijo->der);
        }
        return padre;
    }
    void meterABB (int valor){
        NodoArbol *padre = encuentraPadre(valor);
        NodoArbol *nuevo = new NodoArbol (valor);
        if(padre == NULL) //Agrega el primer nodo del árbol
            raiz = nuevo;
        else
        { //Agrega un nodo hoja
            if ( padre->info > valor )
                padre->izq = nuevo;
            else
                padre->der = nuevo;
        }
    }
    NodoArbol* predecesor(NodoArbol *actual){
        NodoArbol *p = actual->izq;
        while (p->der != NULL)
            p = p->der;
        return p;
    }
    NodoArbol* sucesor (NodoArbol *actual) {
        NodoArbol *p = actual->der;
        while (p->izq != NULL)
            p = p->izq;
        return p;
    }
    void sacarABB(int valor) {
        NodoArbol *padre = encuentraPadre(valor);
        NodoArbol *nodoABorrar;
        if (padre == NULL)
            nodoABorrar = raiz;
        else
            nodoABorrar=(padre->info > valor? padre->izq : padre->der);
        //Encontrar substituto cuando el nodo a borrar tiene 2 hijos
        if (nodoABorrar->izq != NULL && nodoABorrar->der != NULL)
        {
            NodoArbol *substituto = predecesor(nodoABorrar);
            int nuevovalor = substituto->info;
            sacarABB (substituto->info);
            nodoABorrar->info = nuevovalor;
        }
        else if (padre == NULL)
        { //Borra nodo raíz el cual solo tiene un hijo
            if (nodoABorrar->der == NULL)
                raiz = nodoABorrar->izq;
            else
                raiz = nodoABorrar->der;
        }
        else if (padre->info > valor) //Borra nodo con 0 o 1 hijo
            if (nodoABorrar->izq == NULL)
                padre->izq = nodoABorrar->der;
            else
                padre->izq = nodoABorrar->izq;
            else if (nodoABorrar->der == NULL)
                padre->der =nodoABorrar->izq;
            else
                padre->der = nodoABorrar->der;
    }
    void despliegaAncestros (int valor){
        NodoArbol *p = raiz;
        cout<< "Ancestros: "<<endl;
        while (p != NULL)
        {
            if (p->info != valor){
                cout<< p->info << " ";
                p=(p->info > valor? p->izq: p->der);
            }
            else
                p=NULL;
        }
        cout<<endl;
    }
    void despliegaMenor(){
        NodoArbol * p = raiz;
        cout<<"Menor: " <<endl;
        while (p->izq != NULL)
            p=p->izq;
        cout<<p->info<<endl;
    }
    void despliegaMayor(){
        NodoArbol * p = raiz;
        cout<<"Mayor: " <<endl;
        while (p->der != NULL)
            p=p->der;
        cout<<p->info<<endl;
    }
    int cuentaPositivos(NodoArbol *r){
        if (r==NULL){
            return 0;
        }
        if (r->info > 0){
            return 1 + cuentaPositivos(r->izq)+cuentaPositivos(r->der);
        }
        return cuentaPositivos(r->izq)+cuentaPositivos(r->der);
    }
    int sumaPositivos(NodoArbol *r){
        if (r==NULL){
            return 0;
        }
        if (r->info>0){
            return r->info + sumaPositivos(r->izq) + sumaPositivos(r->der);
        }
        return sumaPositivos(r->izq) + sumaPositivos(r->der);
    }
    void despliegaPositivos(NodoArbol *r){
        if (r != NULL){
            if (r->info > 0){
                cout<<r->info;
            }
            despliegaPositivos(r->izq);
            despliegaPositivos(r->der);
        }
    }
    void alturaArbol(){
        cout << "ALTURA: ";
        cout << altura(raiz);
    }
    int altura(NodoArbol *r){
        if (r==NULL){
            return 0;
        }
        int i=altura(r->izq);
        int d=altura(r->der);
        if (i > d){
            return 1 + i;
        }
        else
            return 1 + d;
    }
    void despliegaNivelxNivel(){
        queue<NodoArbol *> Q;
        Q.push(raiz);
        NodoArbol *x;
        cout<<"Nivel por nivel: ";
        while (!Q.empty()){
            x = Q.front();
            Q.pop();
            cout<< x->info << " ";
            if (x->izq != NULL)
                Q.push(x->izq);
            if (x->der != NULL){
                Q.push(x->der);
            }
        }
    }
};
#endif
