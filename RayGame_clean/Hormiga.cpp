//
// Created by Sebastian on 26/05/2025.
//

#include "Hormiga.h"

Hormiga::Hormiga(vector<vector<char>>& m, int startF, int startC)
    : mapa(m), fila(startF), columna(startC) {
    mapa[fila][columna] = 'H'; // símbolo para hormiga estática
}

bool Hormiga::puedeMover(int newF, int newC) {
    // Hormiga normal no se mueve
    return false;
}

void Hormiga::moverHacia(int objetivoF, int objetivoC) {
    // Hormiga normal no hace nada al intentar moverse
}