//
// Created by Sebastian on 6/05/2025.
//

#include "Plataforma.h"
#include <iostream>

// Constructor con textura
Plataforma::Plataforma(float x, float y, float ancho, float alto, const std::string& rutaTextura) {
    forma.setSize(sf::Vector2f(ancho, alto));
    forma.setPosition(x, y);

    tieneTextura = true;
    if (!textura.loadFromFile(rutaTextura)) {
        std::cerr << "Error al cargar la textura de la plataforma: " << rutaTextura << std::endl;
        tieneTextura = false;
        forma.setFillColor(sf::Color(150, 75, 0)); // Color marrón por defecto
    } else {
        textura.setRepeated(true); // Permite que la textura se repita si la plataforma es más grande
        forma.setTexture(&textura);
        forma.setTextureRect(sf::IntRect(0, 0, ancho, alto));
    }
}

// Constructor con color
Plataforma::Plataforma(float x, float y, float ancho, float alto, sf::Color color) {
    forma.setSize(sf::Vector2f(ancho, alto));
    forma.setPosition(x, y);
    forma.setFillColor(color);
    tieneTextura = false;
}

sf::FloatRect Plataforma::getLimites() const {
    return forma.getGlobalBounds();
}

// Ahora también marcado como const en la implementación
void Plataforma::dibujar(sf::RenderWindow& ventana) const {
    ventana.draw(forma);
}

bool Plataforma::estaPorEncima(float x, float y) const {
    sf::FloatRect limites = getLimites();

    // Comprobar si el punto x,y está dentro de los límites horizontales de la plataforma
    bool dentroHorizontal = x >= limites.left && x <= limites.left + limites.width;

    // Comprobar si el punto está justo por encima de la plataforma (con un pequeño margen)
    bool justoPorEncima = y <= limites.top && y + 5 >= limites.top;

    return dentroHorizontal && justoPorEncima;
}