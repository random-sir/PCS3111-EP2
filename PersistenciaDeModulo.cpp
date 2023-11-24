#include "PersistenciaDeModulo.h"

string tipoDeCircuitoSISO(CircuitoSISO* circ);
void escreverModulo(Modulo* modulo, ofstream arquivo);
CircuitoSISO* tipoDeCircuitoSISO_CircSISO(string letraCirc);

PersistenciaDeModulo::PersistenciaDeModulo(string nomeDoArquivo){
  this->nomeDoArquivo = nomeDoArquivo; 
}

PersistenciaDeModulo::~PersistenciaDeModulo(){
  
}

void PersistenciaDeModulo::salvarEmArquivo(Modulo* mod){ //concluída, falta revisar
  ofstream output;
  ouput.open(nomeDoArquivo);

  if(output.fail()){
    throw new invalid_argument("Erro ao abrir o arquivo");
    output.close();
  }else{
    escreverModulo(mod, ouput);
    entrada.close();
    }
}

Modulo* PersistenciaDeModulo::lerDeArquivo(){// não concluída
  ifstream input;
  input.opean(nomeDoArquivo);

  if(input.fail()){
      throw new invalid_argument("Erro ao abrir o arquivo");
      input.close();
  }else{
    Modulo* mod = new Modulo();
    string letraCirc;
    while(input){ //enquanto input.fail() nao eh false
    input >> letraCirc;
    mod->getCircuitos->adicionar(tipoDeCircuitoSISO_CircSISO(letraCirc));
    }
  }
}

string tipoDeCircuitoSISO_STR(CircuitoSISO* circ){ //bruto terminado
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
}

CircuitoSISO* tipoDeCircuitoSISO_CircSISO(string letraCirc){ //não terminada
  //falta fazer o controle de erros corretamente
  if(letraCirc[0] == "A"){ //em manutenção
   return new Amplificador(static_cast<double>(letraCirc[]));
  }else if(letraCirc == "D") return new Derivador();
  else if(letraCirc == "I") return new Integrador();
  else if(letraCirc == "P") return new ModuloEmParalelo();
  else if(letraCirc == "S") return new ModuloEmSerie();
  else if(letraCirc == "R") return new ModuloRealimentado();
}

void escreverModulo(Modulo* modulo, ofstream arquivo){ //concluida, falta revisar
  for(list<CircuitosSISO*>::iterador i = modulo->getCircuitos->begin(); i != modulo->getCircuitos->end(); i++){
    if(tipoDeCircuitoSISO_STR(*i) == "P" || tipoDeCircuitoSISO_STR(*i) == "S" || tipoDeCircuitoSISO_STR(*i) == "R"){
      arquivo << tipoDeCircuitoSISO(*i) << endl;
      escreverModulo(*i);
    }else if(tipoDeCircuitoSISO_STR(*i) == "A") 
      arquivo << "A " << (*i)->getGanho << endl;
     else 
      arquivo << tipoDeCircuitoSISO_STR(*i) << endl;
  }
  arquivo << "f" << endl;
}

Modulo* leituraModulo(Modulo* mod, ifstream arquivo){ //não terminada
  string letraCirc;
  while(input){ //enquanto input.fail() nao eh false
    input >> letraCirc;
    if(letraCirc == "P" || letraCirc == "S" || letraCirc == "R");
      Modulo* moduloInterno = tipoDeCircuitoSISO_CircSISO(letraCirc);
      mod->getCircuitos->adicionar(moduloInterno);
      while(letraCirc != "f"){
       moduloInterno->getCircuitos->adicionar(tipoDeCircuitoSISO_CircSISO(letraCirc));
      }
}

