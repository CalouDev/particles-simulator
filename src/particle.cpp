#include "../include/particle.hpp"

Particle::Particle(sf::RectangleShape box, float x, float y)
    : box(box), velocity(0.f, 0.f), lifetime(10000.f)
{
    this->setPos(sf::Vector2f(x, y));
}

void Particle::update() {
    this->box.move(velocity);
    this->lifetime -= 1.f;
}

void Particle::draw(sf::RenderWindow& window) {
    window.draw(box);
}

sf::Vector2f Particle::getPos() const {
    return box.getPosition();
}

void Particle::setPos(sf::Vector2f new_pos) {
    box.setPosition(new_pos);
}
