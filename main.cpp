#include <iostream>
#include <SFML/Graphics.hpp>
#include "Ray.h"
#include "Plataforma.h"
#include "PuertaEscenario.h"
#include <vector>
#include "Hormiga.h"

int main() {
    sf::RenderWindow ventana(sf::VideoMode(800, 600), "Las aventuras de Ray");

    // Variable para controlar el escenario actual
    int escenarioActual = 1;
    bool cambioEscenario = false;
    sf::Clock timerCambio; // Para evitar cambios muy rápidos

    // Texturas de fondos para diferentes escenarios
    sf::Texture texturaFondo1, texturaFondo2;
    if (!texturaFondo1.loadFromFile("Fondo inicial.jpg")) {
        std::cerr << "Error al cargar la imagen de fondo 1!\n";
        return -1;
    }
    if (!texturaFondo2.loadFromFile("Antesala.jpg")) {
        std::cerr << "Error al cargar la imagen de fondo 2!\n";
        // Si no hay segundo fondo, usar el mismo
        texturaFondo2 = texturaFondo1;
    }

    // Sprite para el fondo
    sf::Sprite spriteFondo;

    // Función para configurar el escenario
    auto configurarEscenario = [&](int numeroEscenario) {
        if (numeroEscenario == 1) {
            spriteFondo.setTexture(texturaFondo1);
        } else {
            spriteFondo.setTexture(texturaFondo2);
        }

        spriteFondo.setScale(
            800.0f / spriteFondo.getTexture()->getSize().x,
            600.0f / spriteFondo.getTexture()->getSize().y
        );
    };

    // Configurar escenario inicial
    configurarEscenario(escenarioActual);

    // Crear personaje
    Ray ray;

    // Posiciones iniciales para cada escenario
    sf::Vector2f posicionEscenario1(50.f, 500.f);
    sf::Vector2f posicionEscenario2(1000.f, 500.f); // Posición diferente en escenario 2

    ray.setPosicion(posicionEscenario1.x, posicionEscenario1.y);

    // Crear enemigo
    Hormiga hormiga;
    hormiga.setPosicion(2200.f, 470.f);

    // Crear puertas para cada escenario
    PuertaEscenario puerta1("Portal.png");
    PuertaEscenario puerta2("Portal.png");

    // Posiciones de las puertas en cada escenario
    puerta1.setPosition(sf::Vector2f(1500.f, 1300.f)); // Puerta en escenario 1
    puerta2.setPosition(sf::Vector2f(100.f, 200.f)); // Puerta en escenario 2

    // Crear plataformas para escenario 1
    std::vector<Plataforma> plataformasEscenario1;
    std::vector<Plataforma> plataformasEscenario2;

    // Dimensiones de plataformas
    const float ANCHO_PLATAFORMA = 150.f;
    const float ALTO_PLATAFORMA = 20.f;
    const sf::Color COLOR_PLATAFORMA = sf::Color(128, 128, 128);

    // Plataformas del escenario 1
    plataformasEscenario1.push_back(Plataforma(500, 900, ANCHO_PLATAFORMA, ALTO_PLATAFORMA));
    plataformasEscenario1.back().setColor(COLOR_PLATAFORMA);
    plataformasEscenario1.push_back(Plataforma(400, 700, ANCHO_PLATAFORMA, ALTO_PLATAFORMA));
    plataformasEscenario1.back().setColor(COLOR_PLATAFORMA);
    plataformasEscenario1.push_back(Plataforma(1500, 1200, ANCHO_PLATAFORMA, ALTO_PLATAFORMA));
    plataformasEscenario1.back().setColor(COLOR_PLATAFORMA);
    plataformasEscenario1.push_back(Plataforma(2000, 1000, ANCHO_PLATAFORMA, ALTO_PLATAFORMA));
    plataformasEscenario1.back().setColor(COLOR_PLATAFORMA);

    // Plataformas del escenario 2 (diferentes posiciones)
    plataformasEscenario2.push_back(Plataforma(200, 400, ANCHO_PLATAFORMA, ALTO_PLATAFORMA));
    plataformasEscenario2.back().setColor(sf::Color::Blue);
    plataformasEscenario2.push_back(Plataforma(600, 300, ANCHO_PLATAFORMA, ALTO_PLATAFORMA));
    plataformasEscenario2.back().setColor(sf::Color::Blue);
    plataformasEscenario2.push_back(Plataforma(300, 550, ANCHO_PLATAFORMA, ALTO_PLATAFORMA));
    plataformasEscenario2.back().setColor(sf::Color::Blue);

    // Referencia a las plataformas actuales
    std::vector<Plataforma>* plataformasActuales = &plataformasEscenario1;

    while (ventana.isOpen()) {
        sf::Event evento;
        while (ventana.pollEvent(evento)) {
            if (evento.type == sf::Event::Closed)
                ventana.close();

            if (evento.type == sf::Event::Resized) {
                sf::FloatRect visibleArea(0, 0, evento.size.width, evento.size.height);
                ventana.setView(sf::View(visibleArea));

                spriteFondo.setScale(
                    evento.size.width / (float)spriteFondo.getTexture()->getSize().x,
                    evento.size.height / (float)spriteFondo.getTexture()->getSize().y
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

        // Actualizar el personaje con las plataformas del escenario actual
        ray.actualizarConPlataformas(*plataformasActuales);

        // Verificar colisión con la puerta (solo si ha pasado tiempo suficiente)
        if (timerCambio.getElapsedTime().asSeconds() > 1.0f) {
            bool colisionPuerta = false;

            if (escenarioActual == 1) {
                colisionPuerta = ray.getHitbox().intersects(puerta1.getBounds());
            } else {
                colisionPuerta = ray.getHitbox().intersects(puerta2.getBounds());
            }

            if (colisionPuerta) {
                // Cambiar de escenario
                if (escenarioActual == 1) {
                    escenarioActual = 2;
                    plataformasActuales = &plataformasEscenario2;
                    ray.setPosicion(posicionEscenario2.x, posicionEscenario2.y);
                    std::cout << "Cambiando al escenario 2" << std::endl;
                } else {
                    escenarioActual = 1;
                    plataformasActuales = &plataformasEscenario1;
                    ray.setPosicion(posicionEscenario1.x, posicionEscenario1.y);
                    std::cout << "Cambiando al escenario 1" << std::endl;
                }

                // Configurar el nuevo escenario
                configurarEscenario(escenarioActual);

                // Reiniciar timer para evitar cambios muy rápidos
                timerCambio.restart();
            }
        }

        ventana.clear();

        // Dibujar el fondo del escenario actual
        ventana.draw(spriteFondo);

        // Dibujar las plataformas del escenario actual
        for (auto& plataforma : *plataformasActuales) {
            plataforma.dibujar(ventana);
        }

        // Dibujar la puerta correspondiente al escenario actual
        if (escenarioActual == 1) {
            puerta1.dibujar(ventana);
        } else {
            puerta2.dibujar(ventana);
        }

        // Dibujar el personaje
        ray.dibujar(ventana);

        // Solo dibujar la hormiga en el escenario 1 (o ajusta según tu preferencia)
        if (escenarioActual == 1) {
            hormiga.dibujar(ventana);
        }

        ventana.display();
    }

    return 0;
}