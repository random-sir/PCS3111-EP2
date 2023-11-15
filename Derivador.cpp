#include "Derivador.h"

Derivador::Derivador(){
}

Derivador::~Derivador(){
}

Sinal* Derivador::processar(Sinal *sinalIN){
    int comprimentoOUT = sinalIN->getComprimento();
    double *sequenciaOUT = new double[comprimentoOUT];
    
    sequenciaOUT[0] = sinalIN->getSequencia()[0];
    for (int i = 1; i < comprimentoOUT; i++)
        sequenciaOUT[i] = sinalIN->getSequencia()[i] - sinalIN->getSequencia()[i - 1];
    Sinal *sinalOUT = new Sinal(sequenciaOUT, comprimentoOUT);
    
    delete[] sequenciaOUT;
    return sinalOUT;
}
