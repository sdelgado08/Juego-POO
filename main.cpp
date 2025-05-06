#include <iostream>
#include <SFML/Graphics.hpp>
#include "Ray.h"

int main() {
    sf::RenderWindow ventana(sf::VideoMode(240, 180), "Juego hormigas");

    // Carga de la imagen de fondo
    sf::Texture texturaFondo;
    if (!texturaFondo.loadFromFile("Fondo1.png")) {
        std::cerr << "Error al cargar la imagen de fondo!\n";
        return -1;
    }

    // Crear sprite para el fondo
    sf::Sprite spriteFondo;
    spriteFondo.setTexture(texturaFondo);

    // Opcional: escalar el fondo para que se ajuste exactamente a la ventana
    spriteFondo.setScale(
        240.0f / texturaFondo.getSize().x,
        180.0f / texturaFondo.getSize().y
    );

    Ray ray;

    while (ventana.isOpen()) {
        sf::Event evento;
        while (ventana.pollEvent(evento)) {
            if (evento.type == sf::Event::Closed)
                ventana.close();

            // 🔧 Ajustar la vista al nuevo tamaño
            if (evento.type == sf::Event::Resized) {
                sf::FloatRect visibleArea(0, 0, evento.size.width, evento.size.height);
                ventana.setView(sf::View(visibleArea));

                // Reajustar el fondo también si la ventana cambia de tamaño
                spriteFondo.setScale(
                    evento.size.width / (float)texturaFondo.getSize().x,
                    evento.size.height / (float)texturaFondo.getSize().y
                );
            }
        }

        // Por defecto está quieto, a menos que se mueva
        ray.detener();

        // Movimiento con teclas
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            ray.moverIzquierda();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            ray.moverDerecha();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            ray.saltar();

        // Actualiza animación si está en movimiento
        ray.actualizar();

        ventana.clear();

        // Dibujar el fondo primero (antes que cualquier otro elemento)
        ventana.draw(spriteFondo);

        // Dibujar el personaje
        ray.dibujar(ventana);

        ventana.display();
    }

    return 0;
}