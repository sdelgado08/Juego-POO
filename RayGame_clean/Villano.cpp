#include "Villano.h"

HormigaInfectada::HormigaInfectada(vector<vector<char>>& m, int startF, int startC) : mapa(m), fila(startF), columna(startC) {
    mapa[fila][columna] = 'V';
}

bool HormigaInfectada::puedeMover(int newF, int newC) {
    if (newF < 0 || newF >= (int)mapa.size()) return false;
    if (newC < 0 || newC >= (int)mapa[0].size()) return false;
    if (mapa[newF][newC] == '#' || mapa[newF][newC] == 'V') return false;
    return true;
}

void HormigaInfectada::moverHacia(int objetivoF, int objetivoC) {
    mapa[fila][columna] = ' ';

    int dFila = (objetivoF > fila) ? 1 : (objetivoF < fila ? -1 : 0);
    int dCol = (objetivoC > columna) ? 1 : (objetivoC < columna ? -1 : 0);

    if (dFila != 0 && puedeMover(fila + dFila, columna)) {
        fila += dFila;
    } else if (dCol != 0 && puedeMover(fila, columna + dCol)) {
        columna += dCol;
    }

    mapa[fila][columna] = 'V';
}