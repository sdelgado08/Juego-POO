//
// Created by Sebastian on 12/05/2025.
//

#include "Hormiga.h"
#include <iostream>

Hormiga::Hormiga() {
    // Cargar texturas de la hormiga
    sf::Texture texD1, texD2, texI1, texI2;
    if (!texD1.loadFromFile("Hormiga infectada NPC.png") ||
        !texD2.loadFromFile("Hormiga infectada NPC.png") ||
        !texI1.loadFromFile("Hormiga infectada NPC.png") ||
        !texI2.loadFromFile("Hormiga infectada NPC.png")) {
        std::cerr << "Error cargando imágenes de la hormiga\n";
        }

    texturasDerecha.push_back(texD1);
    texturasDerecha.push_back(texD2);
    texturasIzquierda.push_back(texI1);
    texturasIzquierda.push_back(texI2);

    // Configurar sprite inicial
    sprite.setTexture(texturasDerecha[0]);
    sprite.setPosition(1500.f, 1300.f);
    sprite.setScale(1.5f, 1.5f); // Escala ligeramente diferente a Ray

    // Configurar la hitbox
    anchoHitbox = texturasDerecha[0].getSize().x * sprite.getScale().x * 0.7f;
    altoHitbox = texturasDerecha[0].getSize().y * sprite.getScale().y * 0.8f;
}

void Hormiga::dibujar(sf::RenderWindow& ventana) {
    ventana.draw(sprite);

}

sf::FloatRect Hormiga::getHitbox() const {
    sf::Vector2f pos = sprite.getPosition();
    // Centrar la hitbox en el sprite
    return sf::FloatRect(
        pos.x - anchoHitbox/2,
        pos.y - altoHitbox,
        anchoHitbox,
        altoHitbox
    );
}

sf::Vector2f Hormiga::getPosicion() const {
    return sprite.getPosition();
}

void Hormiga::setPosicion(float x, float y) {
    sprite.setPosition(x, y);
}