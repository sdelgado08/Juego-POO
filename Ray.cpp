#include "Ray.h"
#include <iostream>
#include <vector>
#include <cstdlib>  // Para system("cls")

using namespace std;

// Constructor
Ray::Ray(vector<vector<char>>& m, int startF, int startC)
    : mapa(m), fila(startF), columna(startC), vida(10) {
    mapa[fila][columna] = 'R';
}

// Mostrar mapa usando cout (compatible con Windows)
void Ray::mostrarMapa() {
    system("cls");  // Limpia consola en Windows

    for (int i = 0; i < mapa.size(); ++i) {
        for (int j = 0; j < mapa[i].size(); ++j) {
            if (i == fila && j == columna) {
                cout << 'R';  // Ray
            }
            else {
                cout << mapa[i][j];
            }
        }
        cout << '\n';
    }

    cout << "\nVIDA: " << vida << "\n";
    cout << "Controles: WASD para moverse, Q para salir\n";
}

// Verificar si puede moverse
bool Ray::puedeMover(int newF, int newC) {
    if (newF < 0 || newF >= (int)mapa.size()) return false;
    if (newC < 0 || newC >= (int)mapa[0].size()) return false;
    if (mapa[newF][newC] == '#') return false;
    if (mapa[newF][newC] == 'S') vida++;
    return true;
}

// Mover Ray a nueva posición
void Ray::moverA(int newF, int newC) {
    mapa[fila][columna] = ' ';
    fila = newF;
    columna = newC;
    mapa[fila][columna] = 'R';
}

// Controles de movimiento
void Ray::moverIzquierda() {
    if (puedeMover(fila, columna - 1)) moverA(fila, columna - 1);
}

void Ray::moverDerecha() {
    if (puedeMover(fila, columna + 1)) moverA(fila, columna + 1);
}

void Ray::saltar() {
    if (puedeMover(fila - 1, columna)) moverA(fila - 1, columna);
}

void Ray::bajar() {
    if (puedeMover(fila + 1, columna)) moverA(fila + 1, columna);
}
