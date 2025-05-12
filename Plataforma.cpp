//
// Created by Sebastian on 12/05/2025.
//

#include "Plataforma.h"
#include <iostream>

Plataforma::Plataforma() : tieneTextura(false) {
    forma.setSize(sf::Vector2f(100.f, 10.f));
    forma.setFillColor(sf::Color(139, 69, 19)); // Color marrón por defecto
    forma.setPosition(0.f, 0.f);
}

Plataforma::Plataforma(float x, float y, float ancho, float alto) : tieneTextura(false) {
    forma.setSize(sf::Vector2f(ancho, alto));
    forma.setFillColor(sf::Color(139, 69, 19)); // Color marrón por defecto
    forma.setPosition(x, y);
}

Plataforma::Plataforma(float x, float y, float ancho, float alto, const std::string& rutaTextura) : tieneTextura(true) {
    forma.setSize(sf::Vector2f(ancho, alto));
    forma.setPosition(x, y);

    // Cargar textura
    if (!textura.loadFromFile(rutaTextura)) {
        std::cerr << "Error cargando textura de plataforma: " << rutaTextura << std::endl;
        tieneTextura = false;
        forma.setFillColor(sf::Color(139, 69, 19)); // Color por defecto si falla la carga
    } else {
        forma.setTexture(&textura);
        // Opcional: repetir la textura si la plataforma es más grande que la textura
        textura.setRepeated(true);

        forma.setTextureRect(sf::IntRect(0, 0, ancho, alto));
    }
}

void Plataforma::dibujar(sf::RenderWindow& ventana) {
    ventana.draw(forma);
}

sf::FloatRect Plataforma::getLimites() const {
    return forma.getGlobalBounds();
}

void Plataforma::setPosicion(float x, float y) {
    forma.setPosition(x, y);
}

void Plataforma::setColor(const sf::Color& color) {
    // Solo cambiar el color si no tiene textura o si queremos sobre-colorear la textura
    forma.setFillColor(color);
}