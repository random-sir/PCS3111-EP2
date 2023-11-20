#include "Sinal.h"
#include "Grafico.h"
#include <string>
#include <stdexcept>

using namespace std;

Sinal::Sinal(double *sequencia, int comprimento){
    if(comprimento <= 0) throw new invalid_argument("Comprimento invalido");
    else{
        this->comprimento = comprimento;
        this->sequencia = new double[comprimento];
        for (int i=0;i<comprimento;i++){
            this->sequencia[i] = sequencia[i];
        }
    }
}

Sinal::Sinal(double constante, int comprimento){
    if(comprimento <= 0) throw new invalid_argument("Comprimento invalido");
    else{
        this->comprimento = comprimento;
        this->sequencia = new const double[comprimento];
        for (int i=0;i<comprimento;i++){
            this->sequencia[i] = constante;
        }
    }
}

Sinal::~Sinal(){
    delete[] sequencia;
}

double *Sinal::getSequencia(){
    return sequencia;
}

int Sinal::getComprimento(){
    return comprimento;
}

void Sinal::imprimir(string nomeDoSinal){
    Grafico* graficoSinal = new Grafico(nomeDoSinal,sequencia,comprimento);
    graficoSinal->plot();
    delete graficoSinal;
}

void Sinal::imprimir(){
    for(int i = 0; i < comprimento; i++)
        cout << i << "- " << sequencia[i] << endl;
    cout << "--" << endl;
}

void Sinal::imprimir(int tamanho){
    for(int i = 0; i < tamanho; i++)
        cout << i << "- " << sequencia[i] << endl;
    cout << "--" << endl;
}
