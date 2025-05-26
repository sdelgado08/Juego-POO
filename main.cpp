#include <iostream>
#include <vector>
#include <ctime>
#include <conio.h>
#include <windows.h>
#include "Ray.h"
#include "Villano.h"

using namespace std;

void mostrarMapa(const vector<vector<char>>& mapa, const Ray& ray) {
    system("cls");  // Limpia la pantalla en Windows
    for (int i = 0; i < mapa.size(); ++i) {
        for (int j = 0; j < mapa[i].size(); ++j) {
            if (i == ray.fila && j == ray.columna)
                cout << 'R';
            else
                cout << mapa[i][j];
        }
        cout << '\n';
    }
    cout << "Vida de Ray: " << ray.vida << "\n";
}

vector<vector<char>> crearMapaPersonalizado() {
    // Define aquí tu mapa personalizado
    // '#' = paredes, ' ' = espacio libre, 'P' = power-ups
    vector<string> disenoMapa = {
        "##################################################",
        "#                 #####                 ##       #",
        "#   ####   ############    ####   ##    ######   #",
        "#   ####   ######          ####   ##    ######   #",
        "########   ######   ###########   ##    ######   #",
        "#                   ################             #",
        "##   ###################   ##             ########",
        "#    ###################   ##   #######   ########",
        "#  S ##                    ##   #######   ##     #",
        "#    ##     #################   ##   ##   ##  S  #",
        "#    ##               ##        ##   ##   ##     #",
        "#    ##    #############   #######               #",
        "#                     ##   #######################",
        "#    ############     ##   #######################",
        "#    #######          ##      S                P #",
        "##################################################",
    };

    vector<vector<char>> mapa(disenoMapa.size(), vector<char>(disenoMapa[0].size()));

    for (int i = 0; i < disenoMapa.size(); ++i) {
        for (int j = 0; j < disenoMapa[i].size(); ++j) {
            mapa[i][j] = disenoMapa[i][j];
        }
    }

    return mapa;
}

int main() {
    srand(time(NULL));

    // Crear el mapa personalizado
    vector<vector<char>> mapa = crearMapaPersonalizado();

    Ray ray(mapa, 1, 1);  // Posición inicial de Ray
    vector<Villano> villanos = {
        Villano(mapa, 1, 20),
    };

    mostrarMapa(mapa, ray);

    while (true) {
        if (_kbhit()) {
            char tecla = _getch();

            switch (tecla) {
                case 'a': ray.moverIzquierda(); break;
                case 'd': ray.moverDerecha(); break;
                case 'w': ray.saltar(); break;
                case 's': ray.bajar(); break;
                case 'q':
                case 'Q':
                    cout << "Saliendo del juego...\n";
                    return 0;
            }

            for (auto& v : villanos) {
                mapa[v.fila][v.columna] = ' ';
                v.moverHacia(ray.fila, ray.columna);

                if (v.fila == ray.fila && v.columna == ray.columna) {
                    ray.vida--;

                    int nuevaFila, nuevaCol;
                    do {
                        nuevaFila = rand() % 48 + 1;
                        nuevaCol = rand() % 48 + 1;
                    } while (mapa[nuevaFila][nuevaCol] != ' ');

                    v.fila = nuevaFila;
                    v.columna = nuevaCol;
                }

                mapa[v.fila][v.columna] = 'v';
            }

            mostrarMapa(mapa, ray);

            if (ray.vida <= 0) {
                cout << "\n💀 ¡Ray ha perdido toda su vida! Fin del juego.\n";
                break;
            }
        }

        Sleep(100); // Pequeña pausa para evitar consumo excesivo de CPU
    }

    return 0;
}