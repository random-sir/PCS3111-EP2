#include "Integrador.h"

Integrador::Integrador(){
}

Integrador::~Integrador(){
}

Sinal* Integrador::processar(Sinal *sinalIN){
    int comprimentoOUT = sinalIN->getComprimento();
    double *sequenciaOUT = new double[comprimentoOUT];
    
    double soma = 0;
    for (int i = 0; i < comprimentoOUT; i++){
        soma += sinalIN->getSequencia()[i];
        sequenciaOUT[i] = soma;
    }
    Sinal *sinalOUT = new Sinal(sequenciaOUT, comprimentoOUT);   
    
    delete[] sequenciaOUT;                                                             
    return sinalOUT;
}

