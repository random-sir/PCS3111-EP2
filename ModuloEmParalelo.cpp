#include "ModuloEmParalelo.h"
#include "Somador.h"
#include <iostream>
#include <list>

using namespace std;

ModuloEmParalelo::ModuloEmParalelo(){
  
}

ModuloEmParalelo::~ModuloEmParalelo(){
  
}

Sinal* ModuloEmParalelo::processar(Sinal* sinalIN){
  bool temCircSISO = false; //indicador de passagem. Utilizaremos a ideia de supor que não há circSISO 
                            //nos "circuitos" e, se ao final do laço o indicador continuar como falso ent significa
                            //que não há nenhum circSISO
  
  //criando um sinal nulo
  double seq[60];
  for(int i = 0; i < 60; i++) seq[i] = 0;
  Sinal* sinalSomado = new Sinal(seq, 60);

  //inicializações
  Somador* sum = new Somador();
  CircuitoSISO* circ = nullptr;
  for(list<CircuitosSISO*>::iterator i = circuitos->begin(); i != circuitos->end(); i++){
    circ = dynamic_cast<CircuitoSISO*>(*i);
    if(circ != NULL){
      temCircSISO = true; 
      sinalSomado = sum->processar(sinalSomado, (*i)->processar(sinalIN));
    }
  }
  if(!temCircSISO) throw new logic_error("Nao ha circuitos SISO");
  delete sum;
  return sinalSomado;
}
