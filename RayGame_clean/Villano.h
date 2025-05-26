#ifndef HORMIGA_INFECTADA_H
#define HORMIGA_INFECTADA_H

#include <vector>
using namespace std;

class HormigaInfectada {
public:
    int fila, columna;
    vector<vector<char>>& mapa;

    HormigaInfectada(vector<vector<char>>& m, int startF, int startC);
    bool puedeMover(int newF, int newC);
    void moverHacia(int objetivoF, int objetivoC);
};

#endif