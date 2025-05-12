#include <iostream>
#include <SFML/Graphics.hpp>
#include "Ray.h"
#include "Plataforma.h"
#include <vector>

#include "Hormiga.h"

int main() {
    sf::RenderWindow ventana(sf::VideoMode(800, 600), "Juego de plataformas");

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
        800.0f / texturaFondo.getSize().x,
        600.0f / texturaFondo.getSize().y
    );

    // Crear personaje
    Ray ray;
    ray.setPosicion(100.f, 500.f); // Posición inicial

    Hormiga hormiga;
    ray.setPosicion(100.f, 500.f);

    // Crear plataformas
    std::vector<Plataforma> plataformas;

    // Textura para las plataformas
    std::string texturaPlataforma = "plataforma.png";

    // Suelo principal - usando color en lugar de textura
    plataformas.push_back(Plataforma(1200, 1000, 500, 112, sf::Color(100, 50, 0))); // Color marrón para el suelo

    // Plataformas adicionales con textura
    plataformas.push_back(Plataforma(1200, 1000, 500, 112, texturaPlataforma));
    plataformas.push_back(Plataforma(350, 350, 500, 112, texturaPlataforma));
    plataformas.push_back(Plataforma(100, 250, 500, 112, texturaPlataforma));
    plataformas.push_back(Plataforma(500, 200, 500, 112, texturaPlataforma));

    while (ventana.isOpen()) {
        sf::Event evento;
        while (ventana.pollEvent(evento)) {
            if (evento.type == sf::Event::Closed)
                ventana.close();

            // Ajustar la vista al nuevo tamaño
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

        // Actualiza animación y física con plataformas
        ray.actualizarConPlataformas(plataformas);

        ventana.clear();

        // Dibujar el fondo primero
        ventana.draw(spriteFondo);

        // Dibujar todas las plataformas
        for (const auto& plataforma : plataformas) {
            plataforma.dibujar(ventana);
        }

        // Dibujar el personaje
        ray.dibujar(ventana);
        hormiga.dibujar(ventana);

        ventana.display();
    }

    return 0;
}
