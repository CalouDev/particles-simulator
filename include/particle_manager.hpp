#ifndef PARTICLE_MANAGER_HPP
#define PARTICLE_MANAGER_HPP

#include <vector>
#include <cmath>

#include <SFML/Graphics.hpp>

#include "constants.hpp"
#include "button_manager.hpp"

class ParticlesManager {
private:
    int num_particles;
    bool is_mouse_visible;
    sf::RectangleShape cursor;
    std::vector<std::vector<ParticleCell>> grid;
public:
    ParticlesManager();

    void eventHandler(sf::RenderWindow& window, sf::Vector2f mouse_coords, sf::Vector2f previous_mouse_coords, sf::RectangleShape grid_delimitation, ParticlesType particle);
    void interpolateParticles(sf::Vector2f mouse_coords, sf::Vector2f previous_mouse_coords, sf::RectangleShape grid_delimitation, ParticlesType particle);
    void drawParticles(sf::RenderWindow& window, sf::Color clr, sf::Vector2f particle_pos);
    void addParticles(ParticlesType particle, sf::Vector2i particle_coords);
    void removeParticle(sf::Vector2i particle_coords);
    void updateParticleBehavior(sf::Vector2i particle_pos);
    void updateParticles(sf::RenderWindow& window, ButtonManager& manager);

    void setCursorSize(sf::Vector2f sz);

    inline ParticleCell getParticleAtPos(sf::Vector2i pos) const { return grid[pos.y][pos.x]; }
    inline int getNumParticles() const { return num_particles; }
};

#endif
