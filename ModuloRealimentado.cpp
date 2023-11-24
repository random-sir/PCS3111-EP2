#include "ModuloRealimentado.h"

ModuloRealimentado::ModuloRealimentado(){
    somadorModuloRealimentado = new Somador();
    inversorModuloRealimentado = new Amplificador(-1);
    moduloEmSerie_ModuloRealimentado = new ModuloEmSerie();
}

ModuloRealimentado::~ModuloRealimentado(){
    delete somadorModuloRealimentado;
    delete inversorModuloRealimentado;
    delete moduloEmSerie_ModuloRealimentado;
}

void ModuloRealimentado::adicionar(CircuitoSISO* circ){
    moduloEmSerie_ModuloRealimentado->adicionar(circ);
}

std::list<CircuitoSISO*>* ModuloRealimentado::getCircuitos(){
    return moduloEmSerie_ModuloRealimentado->getCircuitos();
}

Sinal *ModuloRealimentado::processar(Sinal *sinalIN){
    //inicializacao
    const double velocidadeInicial = 0;
    Sinal* diferenca = nullptr;
    Sinal* saida = nullptr;
    Sinal* saidaInvertida = nullptr;
    double* sequenciaSaidaInvertida = new double[sinalIN->getComprimento()];

    //primeira iteracao
    sequenciaSaidaInvertida[0] = velocidadeInicial * (-1);
    diferenca = new Sinal(sinalIN->getSequencia(), 1);
    saida = moduloEmSerie_ModuloRealimentado->processar(diferenca);
    delete diferenca;

    //iteracoes subsequentes
    for (int i = 1; i < sinalIN->getComprimento(); i++){
        sequenciaSaidaInvertida[i] = ( inversorModuloRealimentado->processar(saida) )->getSequencia()[i-1];
        saidaInvertida = new Sinal(sequenciaSaidaInvertida, i+1); 
        diferenca = somadorModuloRealimentado->processar(saidaInvertida, sinalIN);
        delete saida;
        saida = moduloEmSerie_ModuloRealimentado->processar(diferenca);
        delete saidaInvertida;
        delete diferenca;
    }
    delete[] sequenciaSaidaInvertida;
    return saida;
}
