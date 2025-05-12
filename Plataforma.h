//
// Created by Sebastian on 12/05/2025.
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
    // Constructor por defecto
    Plataforma();

    // Constructor con parámetros
    Plataforma(float x, float y, float ancho, float alto);

    // Constructor con textura
    Plataforma(float x, float y, float ancho, float alto, const std::string& rutaTextura);

    // Dibujar la plataforma
    void dibujar(sf::RenderWindow& ventana);

    // Obtener los límites (para colisiones)
    sf::FloatRect getLimites() const;

    // Establecer posición
    void setPosicion(float x, float y);

    // Cambiar color (útil para plataformas sin textura)
    void setColor(const sf::Color& color);
};

#endif