#ifndef SINAL_H
#define SINAL_H
#include <string>
using namespace std;

class Sinal{
private:
    double *sequencia;
    int comprimento;
public:
    Sinal(double *sequencia, int comprimento);
    Sinal(double constante, int comprimento);
    ~Sinal();
    double* getSequencia();
    int getComprimento();
    void imprimir(string nomeDoSinal);
    void imprimir(); // para testes
    void imprimir(int tamanho);
};
#endif
