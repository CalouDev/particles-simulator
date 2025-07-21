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
    std::vector<std::vector<ParticlesType>> grid;
public:
    ParticlesManager();
    void eventHandler(sf::Vector2f mouse_coords, sf::Vector2f previous_mouse_coords, sf::RectangleShape grid_delimitation, ParticlesType particle);
    void interpolateParticles(sf::Vector2f mouse_coords, sf::Vector2f previous_mouse_coords, sf::RectangleShape grid_delimitation, ParticlesType particle);
    void drawParticles(sf::RenderWindow& window, ParticlesType particle, sf::Vector2f particle_pos);
    void addParticles(ParticlesType particle, sf::Vector2i particle_coords);
    void removeParticle(sf::Vector2i particle_coords);
    void updateParticles(sf::RenderWindow& window);
};

#endif
