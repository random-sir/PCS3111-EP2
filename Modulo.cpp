#include "Modulo.h"

Modulo::Modulo(){
  circuitos = new list<CircuitoSISO*>();
}

Modulo::~Modulo(){
  delete circuitos;
}

void Modulo::adicionar(CircuitoSISO* circ){
  circuitos->push_back(circ);  
}

list<CircuitoSISO*>* Modulo::getCircuitos(){
  return circuitos;
}

void Modulo::imprimir(){
  cout << "Modulo com ID " << this->getUltimoID() << " e:" << endl;
  list<CircuitoSISO*>::iterator i = circuitos->begin();
  while(i != circuitos->end()){
    (*i)->imprimir();
    i++;
  }
}
