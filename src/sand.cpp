#include "../include/sand.hpp"

Sand::Sand(sf::RectangleShape box, sf::Vector2f mouse_coords)
    : Particle(box, mouse_coords) {
        this->box.setFillColor(CLR_SAND);
        velocity = sf::Vector2f(0.f, 2.f);
}

void Sand::update() {
    box.move(velocity);
    lifetime -= 1.f;

    if (box.getPosition().y >= WIN_H) {
        //delete this;
    }
}
