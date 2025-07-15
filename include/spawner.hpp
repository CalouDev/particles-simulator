#ifndef SPAWNER_HPP
#define SPAWNER_HPP

#include <vector>
#include <cmath>

#include <SFML/Graphics.hpp>

#include "constants.hpp"
#include "sand.hpp"
#include "ground.hpp"

class ParticlesManager {
private:
    std::vector<std::vector<std::unique_ptr<Particle>>> grid;
public:
    ParticlesManager();
    void eventHandler(sf::Vector2f mouse_coords, sf::Vector2f previous_mouse_coords, ParticlesType particle);
    void interpolateParticles(ParticlesType particle, sf::Vector2f current_mouse_coords, sf::Vector2f previous_mouse_coords);
    void drawParticles(sf::RenderWindow& window);
    void addParticles(std::unique_ptr<Particle> particle);
    void updateParticles();
};

#endif
