//
// Created by Sebastian on 12/05/2025.
//

#ifndef HORMIGA_H
#define HORMIGA_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Plataforma.h"

class Hormiga {
protected:
    sf::Sprite sprite;
    std::vector<sf::Texture> texturasDerecha;
    std::vector<sf::Texture> texturasIzquierda;
    int frameActual = 0;
    bool moviendoDerecha = true;
    float alturaSuelo = 950.f;

    // Dimensiones de la hitbox del personaje (para colisiones)
    float anchoHitbox;
    float altoHitbox;

public:
    Hormiga(); // Constructor

    // Métodos para dibujar y obtener información básica
    virtual void dibujar(sf::RenderWindow& ventana);
    sf::FloatRect getHitbox() const;
    sf::Vector2f getPosicion() const;
    void setPosicion(float x, float y);
};

#endif