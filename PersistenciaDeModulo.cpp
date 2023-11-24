#include "PersistenciaDeModulo.h"

string tipoDeCircuitoSISO(CircuitoSISO* circ);
string escreverModulo(Modulo* modulo);

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

  escreverModulo(mod);
          
        }
    }
  }
}

Modulo* PersistenciaDeModulo::lerDeArquivo(){
  
}

string tipoDeCircuitoSISO(CircuitoSISO* circ){
//falta fazer o controle de erros corretamente
  if(dynamic_cast<Derivador*>(circ) != NULL) return "D";
  else if(dynamic_cast<Amplificador*>(circ) != NULL) return "A";
  else if(dynamic_cast<Integrador*>(circ) != NULL) return "I";
  else if(dynamic_cast<ModuloEmParalelo*>(circ) != NULL) return "P";
  else if(dynamic_cast<ModuloEmSerie*>(circ) != NULL) return "S";
  else if(dynamic_cast<ModuloRealimentado*>(circ) != NULL) return "R";
//   else{
//     throw new argument_error("Nao eh um circuito SISO");
//     return "ERRO";
//   }
// }

string escreverModulo(Modulo* modulo){
  for(list<CircuitosSISO*>::iterador i = modulo->getCircuitos->begin(); i != modulo->getCircuitos->end(); i++){
    if(tipoDeCircuitoSISO(*i) == "P" || tipoDeCircuitoSISO(*i) == "S" || tipoDeCircuitoSISO(*i) == "R"){
      output << tipoDeCircuitoSISO(*i) << endl;
      escreverModulo(*i);
    }else if(tipoDeCircuitoSISO(*i) == "A") 
      output << "A " << (*i)->getGanho << endl;
     else 
      output << tipoDeCircuitoSISO(*i) << endl;
  }
  return "f";
}
