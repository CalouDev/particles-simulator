#include "../include/sand.hpp"

Sand::Sand(sf::RectangleShape box, float x, float y)
    : Particle(box, x, y) {
        this->box.setFillColor(CLR_SAND);
        velocity = sf::Vector2f(0.f, 2.f);
}

void Sand::update() {
    box.move(velocity);
    lifetime -= 1.f;

    if (box.getPosition().y >= WIN_H) {
        // delete from particles manager
    }
}
