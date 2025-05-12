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

    // Cargar texturas de salto hacia la derecha
    sf::Texture texSaltoD1, texSaltoD2;
    if (!texSaltoD1.loadFromFile("SaltoDerecha.png") ||
        !texSaltoD2.loadFromFile("MitadSaltoDerecha.png")) {
        std::cerr << "Error cargando imágenes de salto derecha\n";
    }
    texturasSaltoDerecha.push_back(texSaltoD1);
    texturasSaltoDerecha.push_back(texSaltoD2);

    // Cargar texturas de salto hacia la izquierda
    sf::Texture texSaltoI1, texSaltoI2;
    if (!texSaltoI1.loadFromFile("SaltoIzquierda.png") ||
        !texSaltoI2.loadFromFile("MitadSaltoIzquierda.png")) {
        std::cerr << "Error cargando imágenes de salto izquierda\n";
    }
    texturasSaltoIzquierda.push_back(texSaltoI1);
    texturasSaltoIzquierda.push_back(texSaltoI2);

    sprite.setTexture(texturasDerecha[0]);
    sprite.setPosition(100.f, 950.f);
    sprite.setScale(2.0f, 2.0f); // escalar si es muy pequeño

    // Configurar la hitbox según el tamaño de la textura y la escala
    anchoHitbox = texturasDerecha[0].getSize().x * sprite.getScale().x * 0.8f; // 80% del ancho para una hitbox más precisa
    altoHitbox = texturasDerecha[0].getSize().y * sprite.getScale().y * 0.9f;  // 90% del alto
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
        relojSalto.restart();   // Reiniciar el reloj de animación de salto

        // Establecer la textura inicial de salto según la dirección
        if (moviendoDerecha) {
            sprite.setTexture(texturasSaltoDerecha[0]);
        } else {
            sprite.setTexture(texturasSaltoIzquierda[0]);
        }
    }
}

void Ray::detener() {
    enMovimiento = false;
}

void Ray::actualizar() {
    // Animación de movimiento horizontal
    if (enMovimiento && !saltando) {
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
        // Animación de salto
        float tiempoSalto = relojSalto.getElapsedTime().asSeconds();
        int frameSalto = (tiempoSalto > 0.3f) ? 1 : 0; // Cambiar frame después de 0.3 segundos

        // Aplicar textura de salto según dirección y frame
        if (moviendoDerecha) {
            sprite.setTexture(texturasSaltoDerecha[frameSalto]);
        } else {
            sprite.setTexture(texturasSaltoIzquierda[frameSalto]);
        }

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

            // Volver a la textura normal
            if (moviendoDerecha) {
                sprite.setTexture(texturasDerecha[0]);
            } else {
                sprite.setTexture(texturasIzquierda[0]);
            }
        }
    }
}

// Nuevo método para actualizar considerando plataformas
void Ray::actualizarConPlataformas(const std::vector<Plataforma>& plataformas) {
    if (enMovimiento && !saltando) {
        if (relojAnimacion.getElapsedTime().asSeconds() >= 0.15f) {
            frameActual = (frameActual + 1) % 3;

            if (moviendoDerecha) {
                sprite.setTexture(texturasDerecha[frameActual]);
            } else {
                sprite.setTexture(texturasIzquierda[frameActual]);
            }

            relojAnimacion.restart();
        }
    }

    // Variables para verificar colisiones con plataformas
    bool sobrePlataforma = false;
    float nuevaAltura = alturaSuelo; // Por defecto, el suelo original

    // Guardar posición anterior antes del movimiento
    sf::Vector2f posAnterior = sprite.getPosition();

    // Física del salto
    if (saltando) {
        // Animación de salto
        float tiempoSalto = relojSalto.getElapsedTime().asSeconds();
        int frameSalto = (tiempoSalto > 0.3f) ? 1 : 0; // Cambiar frame después de 0.3 segundos

        // Aplicar textura de salto según dirección y frame
        if (moviendoDerecha) {
            sprite.setTexture(texturasSaltoDerecha[frameSalto]);
        } else {
            sprite.setTexture(texturasSaltoIzquierda[frameSalto]);
        }

        // Aplicar velocidad actual al sprite
        sprite.move(0.f, velocidadSalto);

        // Aplicar gravedad a la velocidad
        velocidadSalto += gravedad;

        // Obtener la posición actualizada después del movimiento
        sf::Vector2f nuevaPos = sprite.getPosition();

        // Comprobar colisiones con todas las plataformas
        for (const Plataforma& plataforma : plataformas) {
            sf::FloatRect limitesPlataf = plataforma.getLimites();

            // Verificar si está cayendo (velocidad positiva) y la parte inferior del personaje
            // está dentro de los límites horizontales de la plataforma
            if (velocidadSalto > 0 &&
                nuevaPos.x + anchoHitbox/2 >= limitesPlataf.left &&
                nuevaPos.x - anchoHitbox/2 <= limitesPlataf.left + limitesPlataf.width) {

                // Si la posición anterior estaba por encima de la plataforma y ahora está por debajo o dentro
                if (posAnterior.y + altoHitbox <= limitesPlataf.top &&
                    nuevaPos.y + altoHitbox >= limitesPlataf.top) {

                    sobrePlataforma = true;
                    nuevaAltura = limitesPlataf.top - altoHitbox;
                    break; // Usar la primera plataforma encontrada
                }
            }
        }

        // Verificar si ha llegado a una plataforma o al suelo
        if (sobrePlataforma || sprite.getPosition().y >= alturaSuelo) {
            // Si llegó a una plataforma, usar la altura de la plataforma
            // Si no, usar la altura del suelo
            float alturaFinal = sobrePlataforma ? nuevaAltura : alturaSuelo;

            // Restablecer posición exacta al nivel correspondiente
            sprite.setPosition(sprite.getPosition().x, alturaFinal);
            saltando = false;
            velocidadSalto = 0.f;

            // Volver a la textura normal
            if (moviendoDerecha) {
                sprite.setTexture(texturasDerecha[0]);
            } else {
                sprite.setTexture(texturasIzquierda[0]);
            }
        }
    } else {
        // Si no está saltando, verificar si sigue estando sobre alguna plataforma
        // o si necesita caer (por ejemplo, al caminar fuera de una plataforma)
        bool sigueEnPlataforma = false;

        for (const Plataforma& plataforma : plataformas) {
            sf::FloatRect hitboxPersonaje = getHitbox();
            sf::FloatRect limitesPlataf = plataforma.getLimites();

            // Si está sobre esta plataforma
            if (hitboxPersonaje.top + hitboxPersonaje.height == limitesPlataf.top &&
                hitboxPersonaje.left + hitboxPersonaje.width >= limitesPlataf.left &&
                hitboxPersonaje.left <= limitesPlataf.left + limitesPlataf.width) {

                sigueEnPlataforma = true;
                break;
            }
        }

        // Si ya no está sobre una plataforma y no está en el suelo, comenzar a caer
        if (!sigueEnPlataforma && sprite.getPosition().y < alturaSuelo) {
            saltando = true;
            velocidadSalto = 0.1f; // Comenzar con una velocidad pequeña hacia abajo
            relojSalto.restart();   // Reiniciar el reloj de animación

            // Aplicar textura de salto según dirección
            if (moviendoDerecha) {
                sprite.setTexture(texturasSaltoDerecha[0]);
            } else {
                sprite.setTexture(texturasSaltoIzquierda[0]);
            }
        }
    }
}

void Ray::dibujar(sf::RenderWindow& ventana) {
    ventana.draw(sprite);
    sf::FloatRect hitbox = getHitbox();
    sf::RectangleShape rectHitbox;
    rectHitbox.setSize(sf::Vector2f(hitbox.width, hitbox.height));
    rectHitbox.setPosition(hitbox.left, hitbox.top);
    rectHitbox.setFillColor(sf::Color(255, 0, 0, 100));
    ventana.draw(rectHitbox);
}

sf::FloatRect Ray::getHitbox() const {
    sf::Vector2f pos = sprite.getPosition();
    // Centrar la hitbox en el sprite
    return sf::FloatRect(
        pos.x - anchoHitbox/20,
        pos.y - altoHitbox/12,
        anchoHitbox,
        altoHitbox
    );
}

sf::Vector2f Ray::getPosicion() const {
    return sprite.getPosition();
}

void Ray::setPosicion(float x, float y) {
    sprite.setPosition(x, y);
}