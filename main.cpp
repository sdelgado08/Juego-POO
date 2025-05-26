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
    cout << "Vida de Ray: " << ray.vida << " | Escenario: " << ray.escenarioActual + 1 << "\n";
    cout << "Controles: W = Arriba | A = Izquierda | S = Abajo | D = derecha" << "\n";
    cout << "\n";
}

vector<vector<char>> crearMapa(int escenario) {
    vector<string> disenoMapa;

    if (escenario == 0) {
        // Escenario 1
        disenoMapa = {
            "##################################################",
            "#            P    #####                 ##       #",
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
            "#    #######          ##      S                  #",
            "##################################################"
        };
    }
    else if (escenario == 1) {
        // Escenario 2
        disenoMapa = {
            "##################################################",
            "#                                                #",
            "########################################   S    ##",
            "######                                           #",
            "#          #######################################",
            "#                                    #######     #",
            "########################         #################",
            "#                               # #  ###    #  ###",
            "#########          ###############################",
            "#########                                        #",
            "###########################################  S   #",
            "#                                                #",
            "#################               ##################",
            "#                                                #",
            "##################################            ####",
            "#          S                                     #",
            "#################                 ################",
            "#################                              P #",
            "##################################################",
        };
    }
    else if (escenario == 2) {
        // Escenario 3
        disenoMapa = {
            "##################################################",
            "#                                               P#",
            "#  ############################################  #",
            "#  #  S  #     #  S    #    S  #     #  S  #  #",
            "#  #     #     #       #       #     #     #  #",
            "#  #######     #########     #######     ###  #",
            "#         #####         #####         ####    #",
            "#  S      #   #    S    #   #      S  #  #    #",
            "#         #   #         #   #         #  #    #",
            "#  ########   ###########   #########    #    #",
            "#  #      #               #         #    #    #",
            "#  #   S  #     #####     #    S    #  ###    #",
            "#  #      #     #   #     #         #         #",
            "#  ########     #   #     ###########  ########",
            "#         S     #   #         S                #",
            "##################################################",
        };
    }

    vector<vector<char>> mapa(disenoMapa.size(), vector<char>(disenoMapa[0].size()));

    for (int i = 0; i < disenoMapa.size(); ++i) {
        for (int j = 0; j < disenoMapa[i].size(); ++j) {
            mapa[i][j] = disenoMapa[i][j];
        }
    }

    return mapa;
}

vector<Villano> crearVillanos(vector<vector<char>>& mapa, int escenario) {
    vector<Villano> villanos;

    if (escenario == 0) {
        // Villanos para escenario 1
        villanos.push_back(Villano(mapa, 5, 11));
        villanos.push_back(Villano(mapa, 1, 30));
    }
    else if (escenario == 1) {
        // Villanos para escenario 2
        villanos.push_back(Villano(mapa, 4, 8));
        villanos.push_back(Villano(mapa, 10, 15));
        villanos.push_back(Villano(mapa, 12, 35));
    }
    else if (escenario == 2) {
        // Villanos para escenario 3
        villanos.push_back(Villano(mapa, 3, 10));
        villanos.push_back(Villano(mapa, 7, 20));
        villanos.push_back(Villano(mapa, 11, 30));
        villanos.push_back(Villano(mapa, 14, 40));
    }

    return villanos;
}

pair<int, int> obtenerPosicionInicial(int escenario) {
    if (escenario == 0) return {1, 1};       // Escenario 1
    else if (escenario == 1) return {1, 2};  // Escenario 2
    else if (escenario == 2) return {1, 1};  // Escenario 3
    return {1, 1}; // Por defecto
}

int main() {
    srand(time(NULL));

    int escenarioActual = 0;
    const int MAX_ESCENARIOS = 3;

    // Crear el primer mapa
    vector<vector<char>> mapa = crearMapa(escenarioActual);

    // Obtener posición inicial para el escenario actual
    pair<int, int> posInicial = obtenerPosicionInicial(escenarioActual);
    Ray ray(mapa, posInicial.first, posInicial.second);
    ray.escenarioActual = escenarioActual;

    // Crear villanos para el escenario actual
    vector<Villano> villanos = crearVillanos(mapa, escenarioActual);

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

            // Verificar si Ray tocó una puerta
            if (mapa[ray.fila][ray.columna] == 'P') {
                escenarioActual++;

                if (escenarioActual >= MAX_ESCENARIOS) {
                    cout << "\n ¡Felicidades! Has completado todos los escenarios!\n";
                    cout << "Presiona cualquier tecla para salir...";
                    _getch();
                    return 0;
                }

                // Limpiar villanos del mapa anterior
                for (auto& v : villanos) {
                    mapa[v.fila][v.columna] = ' ';
                }

                // Cambiar al siguiente escenario
                mapa = crearMapa(escenarioActual);
                posInicial = obtenerPosicionInicial(escenarioActual);

                // Actualizar Ray para el nuevo escenario
                ray.mapa = mapa;
                ray.fila = posInicial.first;
                ray.columna = posInicial.second;
                ray.escenarioActual = escenarioActual;
                mapa[ray.fila][ray.columna] = 'R';

                // Crear nuevos villanos para el nuevo escenario
                villanos = crearVillanos(mapa, escenarioActual);

                cout << "\n🚪 Cambiando al escenario " << escenarioActual + 1 << "...\n";
                Sleep(1500); // Pausa para mostrar el mensaje
            }

            // Mover villanos
            for (auto& v : villanos) {
                mapa[v.fila][v.columna] = ' ';
                v.moverHacia(ray.fila, ray.columna);

                // Verificar colisión con Ray
                if (v.fila == ray.fila && v.columna == ray.columna) {
                    ray.vida--;

                    // Reposicionar villano aleatoriamente
                    int nuevaFila, nuevaCol;
                    do {
                        nuevaFila = rand() % (mapa.size() - 2) + 1;
                        nuevaCol = rand() % (mapa[0].size() - 2) + 1;
                    } while (mapa[nuevaFila][nuevaCol] != ' ');

                    v.fila = nuevaFila;
                    v.columna = nuevaCol;
                }

                mapa[v.fila][v.columna] = 'v';
            }

            mostrarMapa(mapa, ray);

            if (ray.vida <= 0) {
                cout << "\n💀 ¡Ray ha perdido toda su vida! Fin del juego.\n";
                cout << "Presiona cualquier tecla para salir...";
                _getch();
                break;
            }
        }

        Sleep(100); // Pequeña pausa para evitar consumo excesivo de CPU
    }

    return 0;
}