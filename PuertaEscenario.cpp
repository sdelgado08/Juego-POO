//
// Created by Sebastian on 24/05/2025.
//

#include "PuertaEscenario.h"
#include <iostream>


PuertaEscenario::PuertaEscenario(const std::string &texturePath){
    if (!texture.loadFromFile(texturePath)) {
        std::cout << "Error loading texture" << std::endl;
    }

    sprite.setTexture(texture);
    sprite.setPosition(position);
    sprite.setScale(0.5f, 0.6f);

}

void PuertaEscenario::draw(RenderWindow& ventana) const {
    ventana.draw(sprite);
}

FloatRect PuertaEscenario::getBounds() const {
    return sprite.getGlobalBounds();
}

void PuertaEscenario::setPosition(const Vector2f& position) {
    sprite.setPosition(position);
}

void PuertaEscenario::dibujar(RenderWindow& ventana) const {
    ventana.draw(sprite);
}