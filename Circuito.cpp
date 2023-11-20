#include "Circuito.h"
#include <iostream>

using namespace std;

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
