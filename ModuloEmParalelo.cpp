#include "ModuloEmParalelo.h"

ModuloEmParalelo::ModuloEmParalelo(){
  
}

ModuloEmParalelo::~ModuloEmParalelo(){
  
}

Sinal* ModuloEmParalelo::processar(Sinal* sinalIN){
  bool temCircSISO = false; //indicador de passagem. Utilizaremos a ideia de supor que não há circSISO 
                            //nos "circuitos" e, se ao final do laço o indicador continuar como falso ent significa
                            //que não há nenhum circSISO
  
  //criando um sinal nulo
  Sinal* sinalSomado = new Sinal(0.0, sinalIN->getComprimento());
  
  //inicializações
  Somador* sum = new Somador();
  CircuitoSISO* circ = nullptr;
  Sinal* sinalProcessado = nullptr;
  Sinal* sinalSomadoTotal = sinalSomado;
  for(list<CircuitoSISO*>::iterator i = circuitos->begin(); i != circuitos->end(); i++){
    circ = dynamic_cast<CircuitoSISO*>(*i);
    if(circ != NULL){
      temCircSISO = true;
      sinalProcessado = (*i)->processar(sinalIN);
      sinalSomado = sinalSomadoTotal;
      sinalSomadoTotal = sum->processar(sinalSomado, sinalProcessado);
      delete sinalSomado;
      delete sinalProcessado;
    }
  }
  delete sum;
  if(!temCircSISO){
     throw new logic_error("Nao ha circuitos SISO");
     return sinalIN; //failsafe de lista sem circuitosSISO, falha nao catastroficamente
  }
  return sinalSomadoTotal;
}
