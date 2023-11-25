#include "Modulo.h"

Modulo::Modulo(){
  circuitos = new list<CircuitoSISO*>();
}

Modulo::~Modulo(){
  delete circuitos;
}

void Modulo::adicionar(CircuitoSISO* circ){
  circuitos->puch_back(circ);  
}

list<CircuitoSISO*>* Modulo::getCircuitos(){
  return circuitos;
}

void Modulo::imprimir(){
  cout << "Modulo com ID " << Modulo->getUltimoID() << " e:" << endl;
  list<CircuitoSISO*>::iterator i = circuitos->begin();
  while(i != circuitos->end()){
    cout << "Circuito com ID " << (*i)->getID() << endl;
    i++;
  }
}
