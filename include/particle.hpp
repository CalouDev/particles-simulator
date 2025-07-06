#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <SFML/Graphics.hpp>
#include "constants.hpp"

class Particle {
protected:
    sf::RectangleShape box;
    sf::Vector2f velocity;
    float lifetime;
public:
    Particle(sf::RectangleShape box, sf::Vector2f mouse_coords);
    virtual ~Particle() = default;
    
    virtual void update();
    void draw(sf::RenderWindow& window) const;

    sf::Vector2f getPos() const;

    void setPos(sf::Vector2f new_pos);
};

#endif
