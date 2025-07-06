#include "../include/ground.hpp"

Ground::Ground(sf::RectangleShape box, sf::Vector2f mouse_coords)
    : Particle(box, mouse_coords) {
        this->box.setFillColor(CLR_GROUND);
}

void Ground::update() {
    if (box.getPosition().y >= WIN_H) {
        // delete from particles manager
    }
}
