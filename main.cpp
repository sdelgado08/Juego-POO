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

    spriteFondo.setScale(
        800.0f / texturaFondo.getSize().x,
        600.0f / texturaFondo.getSize().y
    );

    // Crear personaje
    Ray ray;
    ray.setPosicion(100.f, 500.f); // Posición inicial

    // Crear enemigo
    Hormiga hormiga;
    hormiga.setPosicion(1000.f, 1300.f); // Posición inicial de la hormiga

    // Crear plataformas
    std::vector<Plataforma> plataformas;

    // Dimensiones de plataformas
    const float ANCHO_PLATAFORMA = 150.f;
    const float ALTO_PLATAFORMA = 20.f;
    const sf::Color COLOR_PLATAFORMA = sf::Color(128, 128, 128); // Color gris

    // Plataformas en el aire
    plataformas.push_back(Plataforma(500, 900, ANCHO_PLATAFORMA, ALTO_PLATAFORMA));
    plataformas.back().setColor(COLOR_PLATAFORMA);

    plataformas.push_back(Plataforma(400, 700, ANCHO_PLATAFORMA, ALTO_PLATAFORMA));
    plataformas.back().setColor(COLOR_PLATAFORMA);

    plataformas.push_back(Plataforma(1500, 1200, ANCHO_PLATAFORMA, ALTO_PLATAFORMA));
    plataformas.back().setColor(COLOR_PLATAFORMA);

    plataformas.push_back(Plataforma(2000, 1000, ANCHO_PLATAFORMA, ALTO_PLATAFORMA));
    plataformas.back().setColor(COLOR_PLATAFORMA);

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

        // Actualizar el personaje con las plataformas
        ray.actualizarConPlataformas(plataformas);

        ventana.clear();

        // Dibujar el fondo primero
        ventana.draw(spriteFondo);

        // Dibujar todas las plataformas
        for (auto& plataforma : plataformas) {
            plataforma.dibujar(ventana);
        }

        // Dibujar el personaje y enemigos
        ray.dibujar(ventana);
        hormiga.dibujar(ventana);

        ventana.display();
    }

    return 0;
}