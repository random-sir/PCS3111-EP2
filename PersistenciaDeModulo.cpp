#include "PersistenciaDeModulo.h"
#include "CircuitoSISO.h"
#include "Modulo.h"
#include "ModuloEmSerie.h"
#include "ModuloEmParalelo.h"
#include "ModuloRealimentado.h"
#include "Derivador.h"
#include "Integrador.h"
#include "Amplificador.h"
#include "Somador.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <list>

using namespace std;
string tipoDeCircuitoSISO_STR(CircuitoSISO* circ);
CircuitoSISO* tipoDeCircuitoSISO_CircSISO(string letraCirc, ifstream& arquivo);
void escreverModulo(Modulo* modulo, ofstream& arquivo);
void leituraModulo(Modulo* modulo, ifstream& arquivo);

PersistenciaDeModulo::PersistenciaDeModulo(string nomeDoArquivo){
  this->nomeDoArquivo = nomeDoArquivo; 
}

PersistenciaDeModulo::~PersistenciaDeModulo(){
}

void PersistenciaDeModulo::salvarEmArquivo(Modulo* mod){ //falta revisar
  ofstream output;
  output.open(nomeDoArquivo);

  if(output.fail()){
    throw new invalid_argument("Erro ao abrir o arquivo");
    output.close();
  }else{
    escreverModulo(mod, output); //função recursiva
    output.close();
    }
}

Modulo* PersistenciaDeModulo::lerDeArquivo(){ //falta revisar
  ifstream input;
  input.open(nomeDoArquivo);

  if(input.fail()){
      throw new invalid_argument("Erro ao abrir o arquivo");
      input.close();
  }else{
    Modulo* mod = new Modulo();
    leituraModulo(mod, input); //função recursiva
    return mod;
    input.close();
    }
  }

string tipoDeCircuitoSISO_STR(CircuitoSISO* circ){ //falta revisar
  //recebe um circuito e retorna a letra correspondente segundo a descrição do enunciado do EP
  //Para descobrir qual era o tipo do circuito utilizei o cast dinâmico
  if(dynamic_cast<Derivador*>(circ) != NULL) return "D";
  if(dynamic_cast<Amplificador*>(circ) != NULL) return "A";
  if(dynamic_cast<Integrador*>(circ) != NULL) return "I";
  if(dynamic_cast<ModuloEmParalelo*>(circ) != NULL) return "P";
  if(dynamic_cast<ModuloEmSerie*>(circ) != NULL) return "S";
  if(dynamic_cast<ModuloRealimentado*>(circ) != NULL) return "R";
  throw new invalid_argument("Nao eh um circuito SISO");
  return "ERRO";
}

CircuitoSISO* tipoDeCircuitoSISO_CircSISO(string letraCirc, ifstream& arquivo){ //falta revisar
  //recebe uma letra e um arquivo e cria um circuito correspondente à letra
  //No caso do amplificador, faço uma leitura a mais do arquivo para coletar o ganho
  if(letraCirc == "A"){
    double ganho;
    arquivo >> ganho;
    return new Amplificador(ganho);
  } 
  if(letraCirc == "D") return new Derivador();
  if(letraCirc == "I") return new Integrador();
  if(letraCirc == "P") return new ModuloEmParalelo();
  if(letraCirc == "S") return new ModuloEmSerie();
  if(letraCirc == "R") return new ModuloRealimentado();
  throw new logic_error("Arquivo com formatacao inesperada");
  return nullptr;
}

void escreverModulo(Modulo* modulo, ofstream& arquivo){ //concluida, falta revisar
  //basicamente pega os circuitos da lista de circuitos interna do módulo e acha a correspondente letra utilizando a função escreverModulo
  for(list<CircuitoSISO*>::iterator i = modulo->getCircuitos()->begin(); i != modulo->getCircuitos()->end(); i++){
    string tipoDoCircuitoAtual = tipoDeCircuitoSISO_STR(*i); //evitar chamar essa funcao desnecessariamente
    arquivo << tipoDoCircuitoAtual; //imprimir tipo do circuito
    if (tipoDoCircuitoAtual == "A") 
      arquivo << " " << (static_cast<Amplificador*>(*i))->getGanho(); //caso especial do ganho
    arquivo << endl;
    if (tipoDoCircuitoAtual == "P" || tipoDoCircuitoAtual == "S" || tipoDoCircuitoAtual == "R") 
      escreverModulo(static_cast<Modulo*>(*i),arquivo); //recursividade para imprimir //os membros de modulos internos
}
  arquivo << "f" <<endl;
}

void leituraModulo(Modulo* modulo, ifstream& arquivo){ //terminada
  //cria o módulo descrito no arquivo
  string letraCirc;
  while(arquivo){ //enquanto arquivo.fail() nao eh false
    arquivo >> letraCirc;
    if(!arquivo.eof()) throw new logic_error("Arquivo com formatacao inesperada"); //controle de erro necessário conforme dito no enunciado do EP
    if(letraCirc == "P" || letraCirc == "S" || letraCirc == "R"){
      Modulo* moduloInterno = static_cast<Modulo*>(tipoDeCircuitoSISO_CircSISO(letraCirc, arquivo));
      modulo->adicionar(moduloInterno);
      while(letraCirc != "f")
        leituraModulo(moduloInterno, arquivo);
    }else
      modulo->adicionar(tipoDeCircuitoSISO_CircSISO(letraCirc, arquivo));
  }
}

