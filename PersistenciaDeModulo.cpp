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
string tipoDeCircuitoSISO_STR(CircuitoSISO *circ);
CircuitoSISO *tipoDeCircuitoSISO_CircSISO(string letraCirc, ifstream &arquivo);
void escreverModulo(Modulo *modulo, ofstream &arquivo);
void leituraModulo(Modulo *modulo, ifstream &arquivo);

PersistenciaDeModulo::PersistenciaDeModulo(string nomeDoArquivo){
  this->nomeDoArquivo = nomeDoArquivo;
}

PersistenciaDeModulo::~PersistenciaDeModulo(){
}

void PersistenciaDeModulo::salvarEmArquivo(Modulo *mod){ 
  ofstream output;
  output.open(nomeDoArquivo);

  if (output.fail()){
    throw new invalid_argument("Erro ao abrir o arquivo");
    output.close();
  }
  else{
    escreverModulo(mod, output); //função recursiva
    output.close();
  }
}

Modulo *PersistenciaDeModulo::lerDeArquivo(){
  ifstream input;
  input.open(nomeDoArquivo);

  if (input.fail()){
    throw new invalid_argument("Erro ao abrir o arquivo");
    input.close();
    return nullptr;
  }else{
    string letraModulo;
    input >> letraModulo;
    if (letraModulo != "P" && letraModulo != "S" && letraModulo != "R")
      throw new logic_error("Arquivo com formatacao inesperada");
    Modulo *mod = static_cast<Modulo *>(tipoDeCircuitoSISO_CircSISO(letraModulo, input));
    leituraModulo(mod, input); //função recursiva
    input.close();
    return mod;
  }
}

string tipoDeCircuitoSISO_STR(CircuitoSISO *circ){ 
  // recebe um circuito e retorna a letra correspondente segundo a descrição do enunciado do EP
  if (dynamic_cast<Derivador *>(circ) != NULL)
    return "D";
  if (dynamic_cast<Amplificador *>(circ) != NULL)
    return "A";
  if (dynamic_cast<Integrador *>(circ) != NULL)
    return "I";
  if (dynamic_cast<ModuloEmParalelo *>(circ) != NULL)
    return "P";
  if (dynamic_cast<ModuloEmSerie *>(circ) != NULL)
    return "S";
  if (dynamic_cast<ModuloRealimentado *>(circ) != NULL)
    return "R";
  throw new invalid_argument("Nao eh um circuito SISO");
  return "ERRO";
}

CircuitoSISO *tipoDeCircuitoSISO_CircSISO(string letraCirc, ifstream &arquivo){ 
  // recebe uma letra e um arquivo e cria um circuito correspondente à letra
  if (letraCirc == "A")
  {
    double ganho;
    arquivo >> ganho;
    return new Amplificador(ganho);
  }
  if (letraCirc == "D")
    return new Derivador();
  if (letraCirc == "I")
    return new Integrador();
  if (letraCirc == "P")
    return new ModuloEmParalelo();
  if (letraCirc == "S")
    return new ModuloEmSerie();
  if (letraCirc == "R")
    return new ModuloRealimentado();
  throw new logic_error("Arquivo com formatacao inesperada");
  return nullptr;
}

void escreverModulo(Modulo *modulo, ofstream &arquivo){ 
  // pega os circuitos da lista de circuitos interna do módulo e acha a correspondente letra utilizando a função escreverModulo
  arquivo << tipoDeCircuitoSISO_STR(modulo) << endl;
  for (list<CircuitoSISO *>::iterator i = modulo->getCircuitos()->begin(); i != modulo->getCircuitos()->end(); i++)
  {
    string tipoDoCircuitoAtual = tipoDeCircuitoSISO_STR(*i); 
    arquivo << tipoDoCircuitoAtual;                         
    if (tipoDoCircuitoAtual == "A")
      arquivo << " " << (static_cast<Amplificador *>(*i))->getGanho(); // caso especial do ganho
    arquivo << endl;
    if (tipoDoCircuitoAtual == "P" || tipoDoCircuitoAtual == "S" || tipoDoCircuitoAtual == "R")
      escreverModulo(static_cast<Modulo *>(*i), arquivo);
  }
  arquivo << "f" << endl;
}

void leituraModulo(Modulo *modulo, ifstream &arquivo){ 
  // cria o módulo descrito no arquivo
  string letraCirc;
  Modulo *moduloInterno = nullptr;
  bool ehModulo;
  while (arquivo){
    arquivo >> letraCirc;
    if (letraCirc == "f")
      return;
    ehModulo = (letraCirc == "P" || letraCirc == "S" || letraCirc == "R");
    if (!ehModulo)
      modulo->adicionar(tipoDeCircuitoSISO_CircSISO(letraCirc, arquivo));
    else
    {
      moduloInterno = static_cast<Modulo *>(tipoDeCircuitoSISO_CircSISO(letraCirc, arquivo));
      leituraModulo(moduloInterno, arquivo);
      modulo->adicionar(moduloInterno);
    }
  }
}
