#include "practList.hpp"

Lista::Lista(){
  head = NULL;
}

void Lista::insSortLista(int elem){
  Nodo* tmp;
  Nodo* prv;
  Nodo* nuevo = new Nodo;
  nuevo->dato = elem;
  nuevo->sig = NULL;
  bool flag = false;
  if(head == NULL){
    head = nuevo;
  }
  else{
    if(elem < head->dato){
      nuevo->sig = head;
      head = nuevo;
    }
    else{
      tmp = head;
      prv = NULL;
      while(tmp != NULL && tmp->dato < elem){
        prv = tmp;
        tmp = tmp->sig;
      }
      prv->sig = nuevo;
      nuevo->sig =  tmp;
    }

  }
}

int Lista::minLista(){
  int ans = -1;
  if(head != NULL)
    ans = head->dato;
  return ans;
}



// anexa un elemento al final de la lista
void Lista::appendLista(int elem){
  Nodo* tmp;
  Nodo* nuevo = new Nodo;
  nuevo->dato = elem;
  nuevo->sig = NULL;

  if(head == NULL)
    head = nuevo;
  else{
    tmp = head;
    while(tmp->sig != NULL)
      tmp = tmp->sig;
    tmp->sig = nuevo;
  }
}


// inserta un elemento en una posición dada
void Lista::insertLista(int elem, int pos){
  Nodo *nuevo, *tmp;
  nuevo = new Nodo;
  nuevo->dato = elem;
  nuevo->sig = NULL;

  if(pos >= 1 && pos <= lenLista()){
    if(pos == 1){
      nuevo->sig = head;
      head = nuevo;
    }
    else{
      tmp = head;
      for(int i = 0; i < pos - 2; i++){
	       tmp = tmp->sig;
      }
      nuevo->sig = tmp->sig;
      tmp->sig = nuevo;
    }
  }
}

void Lista::delLista(int pos){
  Nodo *tmp, *elim;
  if(pos >= 1 && pos <= lenLista()){
    if(pos == 1)
      head = head->sig;
    else{
      tmp = head;
      for(int i = 0; i < pos-2; i++)
	        tmp = tmp->sig;
      elim = tmp->sig;
      tmp->sig = tmp->sig->sig;
      delete elim;
    }
  }
}

int Lista::searchPosLista(int pos){
  Nodo* tmp = head;

  for(int i = 1; i < pos; i++)
    tmp = tmp->sig;

  return tmp->dato;
}

int Lista::lenLista(){
  Nodo* tmp = head;
  int cont = 0;

  while(tmp != NULL){
    tmp = tmp->sig;
    cont++;
  }

  return cont;
}

bool Lista::isEmptyLista(){
  if (head == NULL)
    return true;
  return false;
}

int Lista::maxLista() {
    Nodo* auxiliar = head;
    if(auxiliar == nullptr) {
        // lista vacia 
        return -1;
    }

    int mayor = 0;
    while(auxiliar != nullptr) {
        if(auxiliar->dato >= mayor) {
            mayor = auxiliar->dato;
        }
        auxiliar = auxiliar->sig;
    }
    return mayor;
}

// ahora eliminar los nodos que tengan un valor un par 

void Lista::delOddLista() {

    Nodo* auxiliar = head;
    Nodo* anterior = nullptr;

    if(auxiliar == nullptr) {
        // la lista esta vacia
        return; 
    }

    while(auxiliar != nullptr) {
        Nodo* siguienteReal = auxiliar->sig;

        if(auxiliar->dato % 2 != 0) {
            if(anterior == nullptr) {
                head = siguienteReal;
            } else {
                anterior->sig = siguienteReal;
            }
            delete auxiliar;
            auxiliar = siguienteReal;   // el fix del punto 3, también acá adentro
        }

    }
}