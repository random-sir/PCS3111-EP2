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
  Sinal* sinalPrinc1 = sinalIN;
  Sinal* sinalPrinc2 = sinalPrinc1; //failsafe de lista sem circuitosSISO, falha nao catastroficamente
  for(list<CircuitoSISO*>::iterator i = circuitos->begin(); i != circuitos->end(); i++){
    circ = dynamic_cast<CircuitoSISO*>(*i);
    if(circ != NULL){
      temCircSISO = true; 
      sinalPrinc2 = (*i)->processar(sinalPrinc1);     //deve ser feito dessa forma para evitar um memory leak

      if (sinalPrinc1 != sinalIN) delete sinalPrinc1;//devemos deletar a memoria alocada em sinalPrinc1 (desde que não seja sinalIN),
                                                    //pois o metodo processar não deleta.
      sinalPrinc1 = sinalPrinc2;                    
      
    }
  }
  if(!temCircSISO) throw new logic_error("Nao ha circuitos SISO");
  return sinalPrinc2;
}
