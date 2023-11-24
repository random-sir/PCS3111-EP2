#include "PersistenciaDeModulo.h"

PersistenciaDeModulo::PersistenciaDeModulo(string nomeDoArquivo){
  this->nomeDoArquivo = nomeDoArquivo; 
}

PersistenciaDeModulo::~PersistenciaDeModulo(){
  
}

void PersistenciaDeModulo::salvarEmArquivo(Modulo* mod){
  ofstream output;
  ouput.open(nomeDoArquivo);

  if(output.fail()){
    cout << "Arquivo nao encontrado" << endl;
    entrada.close();
    return
  }

  CircuitoSISO* circ = nullptr;
  for(list<CircuitosSISO*>::iterador i = mod->getCircuitos->begin(); i != mod->getCircuitos->end(); i++){
    circ = dynamic_cast<c>(*i);
    if(dynamic_cast<c>(*i))
    
  }
  
}

Modulo* PersistenciaDeModulo::lerDeArquivo(){
  
}
