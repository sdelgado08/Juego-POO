//
// Created by Sebastian on 1/05/2025.
//

#include "Ray.h"
#include <iostream>

Ray::Ray() {
    // Cargar texturas derecha
    sf::Texture texD1, texD2, texD3;
    if (!texD1.loadFromFile("Ray derecha1.png") ||
        !texD2.loadFromFile("Ray derecha3.png") ||
        !texD3.loadFromFile("Ray derecha2.png")) {
        std::cerr << "Error cargando imágenes derecha\n";
    }
    texturasDerecha.push_back(texD1);
    texturasDerecha.push_back(texD2);
    texturasDerecha.push_back(texD3);

    // Cargar texturas izquierda
    sf::Texture texI1, texI2, texI3;
    if (!texI1.loadFromFile("Ray izquierda1.png") ||
        !texI2.loadFromFile("Ray izquierda3.png") ||
        !texI3.loadFromFile("Ray izquierda2.png")) {
        std::cerr << "Error cargando imágenes izquierda\n";
    }

    texturasIzquierda.push_back(texI1);
    texturasIzquierda.push_back(texI2);
    texturasIzquierda.push_back(texI3);

    sprite.setTexture(texturasDerecha[0]);
    sprite.setPosition(100.f, 950.f);
    sprite.setScale(2.0f, 2.0f); // escalar si es muy pequeño
}

void Ray::moverDerecha() {
    moviendoDerecha = true;
    enMovimiento = true;
    sprite.move(1.5, 0.f);
}

void Ray::moverIzquierda() {
    moviendoDerecha = false;
    enMovimiento = true;
    sprite.move(-1.5, 0.f);
}

void Ray::saltar() {
    // Solo permitir saltar si no está ya saltando
    if (!saltando) {
        saltando = true;
        velocidadSalto = -8.0f; // Velocidad inicial negativa (hacia arriba)
    }
}

void Ray::detener() {
    enMovimiento = false;
}

void Ray::actualizar() {
    // Animación de movimiento horizontal
    if (enMovimiento) {
        // Cambiar frame cada 0.15 segundos (aproximadamente 6.7fps)
        if (relojAnimacion.getElapsedTime().asSeconds() >= 0.15f) {
            frameActual = (frameActual + 1) % 3; // Ahora son 3 frames en vez de 2

            if (moviendoDerecha) {
                sprite.setTexture(texturasDerecha[frameActual]);
            } else {
                sprite.setTexture(texturasIzquierda[frameActual]);
            }

            relojAnimacion.restart();
        }
    }

    // Física del salto
    if (saltando) {
        // Aplicar velocidad actual al sprite
        sprite.move(0.f, velocidadSalto);

        // Aplicar gravedad a la velocidad
        velocidadSalto += gravedad;

        // Verificar si ha llegado al suelo
        if (sprite.getPosition().y >= alturaSuelo) {
            // Restablecer posición exacta al nivel del suelo
            sprite.setPosition(sprite.getPosition().x, alturaSuelo);
            saltando = false;
            velocidadSalto = 0.f;
        }
    }
}

void Ray::dibujar(sf::RenderWindow& ventana) {
    ventana.draw(sprite);
}