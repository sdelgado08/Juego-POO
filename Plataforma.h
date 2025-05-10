//
// Created by Sebastian on 6/05/2025.
//

#ifndef PLATAFORMA_H
#define PLATAFORMA_H

#include <SFML/Graphics.hpp>

class Plataforma {
private:
    sf::RectangleShape forma;
    sf::Texture textura;
    bool tieneTextura;

public:
    // Constructor para plataforma con textura
    Plataforma(float x, float y, float ancho, float alto, const std::string& rutaTextura);

    // Constructor para plataforma sin textura (solo color)
    Plataforma(float x, float y, float ancho, float alto, sf::Color color);

    // Obtener los límites de la plataforma (para colisiones)
    sf::FloatRect getLimites() const;

    // Dibujar la plataforma en la ventana - ahora marcado como const
    void dibujar(sf::RenderWindow& ventana) const;

    // Comprobar si un punto está por encima de la plataforma
    bool estaPorEncima(float x, float y) const;
};

#endif