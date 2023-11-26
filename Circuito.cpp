#include "Circuito.h"

int Circuito::GlobalID = 0; //atributo estático //Começa do zero, pois a variavel será incrementada antes de ser atribuida.

Circuito::Circuito(){
  this->ID = ++Circuito::GlobalID; // ++Circuito::GlobalID; indica que a variavel será incrementada antes de ser atribuida a ID.
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
  return Circuito::GlobalID; //retornará 0, se nenhum circuito tiver sido criado ainda.
}
