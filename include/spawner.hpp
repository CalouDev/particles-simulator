#ifndef SPAWNER_HPP
#define SPAWNER_HPP

#include <vector>
#include <SFML/Graphics.hpp>
#include "sand.hpp"
#include "ground.hpp"

class ParticlesManager {
private:
    std::vector<Particle> manager;
public:
    void eventHandler(sf::Vector2f mouse_coords);
    void drawParticles(sf::RenderWindow& window);
    void addParticles(Particle particle);
    void updateParticles();
};

#endif
