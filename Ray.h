//
// Created by Sebastian on 1/05/2025.
//

#ifndef RAY_H
#define RAY_H

#include <SFML/Graphics.hpp>
#include <vector>

class Ray {
private:
    sf::Sprite sprite;
    std::vector<sf::Texture> texturasDerecha;
    std::vector<sf::Texture> texturasIzquierda;
    int frameActual = 0;
    bool moviendoDerecha = true;
    bool enMovimiento = false;

    bool saltando = false;
    float velocidadSalto = 0.f;
    float gravedad = 0.08f;
    float alturaSuelo = 950.f; // Ajusta esto según la altura del suelo en tu juego

    sf::Clock relojAnimacion;

public:
    Ray();

    void moverDerecha();
    void moverIzquierda();
    void saltar();
    void actualizar();  // se llama cada frame
    void detener();     // se llama si no se mueve
    void dibujar(sf::RenderWindow& ventana);
};

#endif