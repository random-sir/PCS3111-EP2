#include "PersistenciaDeModulo.h"

string tipoDeCircuitoSISO_STR(CircuitoSISO* circ);
CircuitoSISO* tipoDeCircuitoSISO_CircSISO(string letraCirc, ifstream& arquivo);
void escreverModulo(Modulo* modulo, ofstream& arquivo);
void leituraModulo(Modulo* mod, ifstream& arquivo);

PersistenciaDeModulo::PersistenciaDeModulo(string nomeDoArquivo){
  this->nomeDoArquivo = nomeDoArquivo; 
}

PersistenciaDeModulo::~PersistenciaDeModulo(){
}

void PersistenciaDeModulo::salvarEmArquivo(Modulo* mod){ //falta revisar
  ofstream output;
  ouput.open(nomeDoArquivo);

  if(output.fail()){
    throw new invalid_argument("Erro ao abrir o arquivo");
    output.close(nomeDoArquivo);
  }else{
    escreverModulo(mod, ouput); //função recurisiva
    output.close(nomeDoArquivo);
    }
}

Modulo* PersistenciaDeModulo::lerDeArquivo(){ //falta revisar
  ifstream input;
  input.opean(nomeDoArquivo);

  if(input.fail()){
      throw new invalid_argument("Erro ao abrir o arquivo");
      input.close(nomeDoArquivo);
  }else{
    Modulo* mod = new Modulo();
    leituraModulo(mod, input); //função recursiva
    return mod;
    input.close(nomeDoArquivo);
    }
  }
}

string tipoDeCircuitoSISO_STR(CircuitoSISO* circ){ //falta revisar
  //recebe um circuito e retorna a letra correspondente segundo a descrição do enunciado do EP
  //Para descobrir qual era o tipo do circuito utilizei o cast dinâmico
  if(dynamic_cast<Derivador*>(circ) != NULL) return "D";
  else if(dynamic_cast<Amplificador*>(circ) != NULL) return "A";
  else if(dynamic_cast<Integrador*>(circ) != NULL) return "I";
  else if(dynamic_cast<ModuloEmParalelo*>(circ) != NULL) return "P";
  else if(dynamic_cast<ModuloEmSerie*>(circ) != NULL) return "S";
  else if(dynamic_cast<ModuloRealimentado*>(circ) != NULL) return "R";
  else{ //necessario?
    throw new invalid_argument("Nao eh um circuito SISO");
    return "ERRO";
  }
}

CircuitoSISO* tipoDeCircuitoSISO_CircSISO(string letraCirc, ifstream& arquivo){ //falta revisar
  //recebe uma letra e um arquivo e cria um circuito correspondente à letra
  //No caso do amplificador, faço uma leitura a mais do arquivo para coletar o ganho
  if(letraCirc == "A"){
    string ganho;
    arquivo >> ganho;
    //getline(arquivo, ganho, ' ');
    return new Amplificador(static_cast<double>(ganho));
  }else if(letraCirc == "D") return new Derivador();
  else if(letraCirc == "I") return new Integrador();
  else if(letraCirc == "P") return new ModuloEmParalelo();
  else if(letraCirc == "S") return new ModuloEmSerie();
  else if(letraCirc == "R") return new ModuloRealimentado();
}

void escreverModulo(Modulo* modulo, ofstream& arquivo){ //concluida, falta revisar
  //basicamente pega os circuitos da lista de circuitos interna do módulo e acha a correspondente letra utilizando a função escreverModulo
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

void leituraModulo(Modulo* mod, ifstream& arquivo){ //terminada
  //cria o módulo descrito no arquivo
  //utilizei o getline para fazer a leitura no arquivo (vimos o getline em aula, então podemos utilizar)
  //porque ele permite estabelecer um break mark de forma bem fácil
  string letraCirc;
  while(arquivo){ //enquanto arquivo.fail() nao eh false
    arquivo >> ganho;
    //getline(arquivo, letraCirc, ' ');
    if(!arquivo.eof()) throw new logic_error("Arquivo com formatacao inesperada"); //controle de erro necessário conforme dito no enunciado do EP
    if(letraCirc == "P" || letraCirc == "S" || letraCirc == "R"){
      Modulo* moduloInterno = tipoDeCircuitoSISO_CircSISO(letraCirc, arquivo);
      mod->getCircuitos()->adicionar(moduloInterno);
      while(letraCirc != "f")
        leituraModulo(moduloInterno, arquivo);
    }else
      mod->getCircuitos()->adicionar(tipoDeCircuitoSISO_CircSISO(letraCirc, arquivo));
  }
}

