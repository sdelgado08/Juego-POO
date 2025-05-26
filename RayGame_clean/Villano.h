#ifndef VILLANO_H
#define VILLANO_H

#include <vector>
using namespace std;

class Villano {
public:
    int fila, columna;
    vector<vector<char>>& mapa;

    Villano(vector<vector<char>>& m, int startF, int startC);
    bool puedeMover(int newF, int newC);
    void moverHacia(int objetivoF, int objetivoC);
};

#endif
