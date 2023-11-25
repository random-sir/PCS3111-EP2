#include "Circuito.h"

int Circuito::GlobalID = 0; //atributo estático

Circuito::Circuito(){
  this->ID = ++Circuito::GlobalID;
}

Circuito::~Circuito(){
}

int Circuito::getID(){
  return ID;
}

void Circuito::imprimir(){
  cout << "Circuito com ID " << ID << endl;
}

int Circuito::getUltimoID(){
  return Circuito::GlobalID;
}
