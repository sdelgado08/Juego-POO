//
// Created by Sebastian on 26/05/2025.
//

#ifndef HORMIGA_H
#define HORMIGA_H
#include <vector>
using namespace std;


class Hormiga {
public:
    int fila, columna;
    vector<vector<char>>& mapa;

    Hormiga(vector<vector<char>>& m, int startF, int startC);

    // Métodos virtuales para permitir override
    virtual bool puedeMover(int newF, int newC);
    virtual void moverHacia(int objetivoF, int objetivoC);

};



#endif//HORMIGA_H