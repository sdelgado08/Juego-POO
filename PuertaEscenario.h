//
// Created by Sebastian on 24/05/2025.
//

#ifndef PUERTAESCENARIO_H
#define PUERTAESCENARIO_H
#include <SFML/Graphics.hpp>
using namespace sf;



class PuertaEscenario {
    Sprite sprite;
    Texture texture;
    Vector2f position;

public:
    PuertaEscenario(const std::string& texturePat);
    void draw(RenderWindow& ventana) const;
    FloatRect getBounds() const;
    void setPosition(const Vector2f& position);
    void dibujar(RenderWindow& ventana) const;

};

#endif //PUERTAESCENARIO_H