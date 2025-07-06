#include "../include/spawner.hpp"
#include "../include/constants.hpp"

void ParticlesManager::eventHandler(sf::Vector2f mouse_coords, ParticlesType particle) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        sf::RectangleShape particle_shape(sf::Vector2f(PARTICLE_SZ, PARTICLE_SZ));

        switch (particle) {
            case GroundType:
                addParticles(Ground(particle_shape, mouse_coords));
                break;
            case SandType:
                addParticles(Sand(particle_shape, mouse_coords));
                break;
            default:
                break;
        }
    } else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
        // Erase particles
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
