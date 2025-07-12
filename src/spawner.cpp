#include "../include/spawner.hpp"
#include "../include/constants.hpp"

void ParticlesManager::eventHandler(sf::Vector2f mouse_coords, sf::Vector2f previous_mouse_coords, ParticlesType particle) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        interpolateParticles(particle, mouse_coords, previous_mouse_coords);
    } else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) { // Changer dans le futur par l'appui sur un bouton
        manager.clear();
    }
}

void ParticlesManager::interpolateParticles(ParticlesType particle, sf::Vector2f current_mouse_coords, sf::Vector2f previous_mouse_coords) {
    sf::RectangleShape particle_shape(sf::Vector2f(PARTICLE_SZ, PARTICLE_SZ));
    sf::Vector2f delta = current_mouse_coords - previous_mouse_coords;
    float distance = std::sqrt(delta.x * delta.x + delta.y * delta.y);
    int steps = static_cast<int>(distance / PARTICLE_SZ);
    switch (particle) {
    case GroundType:
        addParticles(Ground(particle_shape, current_mouse_coords));
        break;
    case SandType:
        addParticles(Sand(particle_shape, current_mouse_coords));
        break;
    default:
        break;
    }

    for (int i = 0; i <= steps; ++i) {
        float t = static_cast<float>(i) / steps;
        sf::Vector2f interpolated_pos = previous_mouse_coords + delta * t;
        switch (particle) {
            case GroundType:
                addParticles(Ground(particle_shape, interpolated_pos));
                break;
            case SandType:
                addParticles(Sand(particle_shape, interpolated_pos));
                break;
            default:
                break;
        }
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
