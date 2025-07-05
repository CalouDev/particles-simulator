#include "../include/ground.hpp"

Ground::Ground(sf::RectangleShape box, float x, float y)
    : Particle(box, x, y) {
        this->box.setFillColor(CLR_GROUND);
}

void Ground::update() {
    if (box.getPosition().y >= WIN_H) {
        // delete from particles manager
    }
}
