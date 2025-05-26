#ifndef RAY_H
#define RAY_H

#include <vector>
using namespace std;

class Ray {
public:
    int fila, columna;
    int vida;
    vector<vector<char>>& mapa;

    Ray(vector<vector<char>>& m, int startF, int startC);
    void mostrarMapa();
    bool puedeMover(int newF, int newC);
    void moverA(int newF, int newC);
    void moverIzquierda();
    void moverDerecha();
    void saltar();
    void bajar();
};

#endif
