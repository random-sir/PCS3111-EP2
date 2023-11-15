#include "Sinal.h"
#include "Grafico.h"

Sinal::Sinal(double *sequencia, int comprimento) : comprimento(comprimento)
{
    this->sequencia = new double[comprimento];
    for (int i=0;i<comprimento;i++){
        this->sequencia[i] = sequencia[i];
    }
}
Sinal::~Sinal()
{
    delete[] sequencia;
}

double *Sinal::getSequencia()
{
    return sequencia;
}

int Sinal::getComprimento()
{
    return comprimento;
}

void Sinal::imprimir(string nomeDoSinal)
{
    Grafico* graficoSinal = new Grafico(nomeDoSinal,sequencia,comprimento);
    graficoSinal->plot();
    delete graficoSinal;
}
