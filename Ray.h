//
// Created by Sebastian on 1/05/2025.
//

#ifndef RAY_H
#define RAY_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Plataforma.h"

class Ray {
private:
    sf::Sprite sprite;
    std::vector<sf::Texture> texturasDerecha;
    std::vector<sf::Texture> texturasIzquierda;
    std::vector<sf::Texture> texturasSaltoDerecha;  // Texturas de salto hacia la derecha
    std::vector<sf::Texture> texturasSaltoIzquierda; // Texturas de salto hacia la izquierda
    int frameActual = 0;
    bool moviendoDerecha = true;
    bool enMovimiento = false;

    bool saltando = false;
    float velocidadSalto = 0.f;
    float gravedad = 0.08f;
    float alturaSuelo = 950.f; // Ajusta esto según la altura del suelo en tu juego

    sf::Clock relojAnimacion;
    sf::Clock relojSalto;      // Reloj para controlar la animación de salto

    // Dimensiones de la hitbox del personaje (para colisiones)
    float anchoHitbox;
    float altoHitbox;

public:
    Ray();

    void moverDerecha();
    void moverIzquierda();
    void saltar();
    void actualizar();  // se llama cada frame
    void detener();     // se llama si no se mueve
    void dibujar(sf::RenderWindow& ventana);

    // Métodos nuevos para manejo de plataformas
    sf::FloatRect getHitbox() const;
    void actualizarConPlataformas(const std::vector<Plataforma>& plataformas);

    // Obtener la posición actual
    sf::Vector2f getPosicion() const;

    // Establecer posición
    void setPosicion(float x, float y);
};

#endif