#include "../include/spawner.hpp"

void ParticlesManager::eventHandler(sf::Vector2f mouse_coords) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        addParticles(Ground(sf::RectangleShape(sf::Vector2f(PARTICLE_SZ, PARTICLE_SZ)), mouse_coords.x, mouse_coords.y));
    } else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
        addParticles(Sand(sf::RectangleShape(sf::Vector2f(PARTICLE_SZ, PARTICLE_SZ)), mouse_coords.x, mouse_coords.y));
    }
}

void ParticlesManager::addParticles(Particle particle) {
    manager.push_back(particle);
}

void ParticlesManager::drawParticles(sf::RenderWindow& window) {
    for (Particle& p : manager) {
        p.draw(window);
    }
}

void ParticlesManager::updateParticles() {
    for (Particle& p : manager) {
        p.update();
    }
}
