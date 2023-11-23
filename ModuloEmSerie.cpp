#include "ModuloEmSerie.h"
#include <iostream>

using namespace std;

ModuloEmSerie::ModuloEmSerie(){
  
}

ModuloEmSerie::~ModuloEmSerie(){
  
}

Sinal* ModuloEmSerie::processar(Sinal* sinalIN){
  bool temCircSISO = false; //indicador de passagem. Utilizaremos a ideia de supor que não há circSISO 
                            //nos "circuitos" e, se ao final do laço o indicador continuar como falso ent significa
                            //que não há nenhum circSISO
  Sinal* sinalPrinc = sinalIN;
  CircuitoSISO* circ = nullptr;
  list<CircuitosSISO*>::iterator i;
  for(i = circuitos->begin(); i != circuitos->end(); i++){
    circ = dynamic_cast<CircuitoSISO*>(*i);
    if(circ != NULL){
      temCircSISO = true; 
      //evitando o overleak
      Sinal* sinalInterm = (*i)->processar(sinalPrinc);
      delete sinalPrinc;
      Sinal* sinalPrinc = sinalInterm;
      delete sinalInterm;
    }
  }
}
  if(!temCircSISO) throw logic_error("Nao ha circuitos SISO");
  return sinalPrinc;
}
