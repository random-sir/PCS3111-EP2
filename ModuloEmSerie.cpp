#include "ModuloEmSerie.h"

ModuloEmSerie::ModuloEmSerie(){
}

ModuloEmSerie::~ModuloEmSerie(){
}

Sinal* ModuloEmSerie::processar(Sinal* sinalIN){
  bool temCircSISO = false; //indicador de passagem. Utilizaremos a ideia de supor que não há circSISO 
                            //nos "circuitos" e, se ao final do laço o indicador continuar como falso 
                            //ent significa que não há nenhum circSISO
  CircuitoSISO* circ = nullptr;
  Sinal* sinalPrinc = sinalIN;
  for(list<CircuitosSISO*>::iterator i = circuitos->begin(); i != circuitos->end(); i++){
    circ = dynamic_cast<CircuitoSISO*>(*i);
    if(circ != NULL){
      temCircSISO = true; 
      sinalPrinc = (*i)->processar(sinalPrinc);
    }
  }
  if(!temCircSISO) throw new logic_error("Nao ha circuitos SISO");
  return sinalPrinc;
}
