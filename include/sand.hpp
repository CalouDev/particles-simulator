#ifndef SAND_HPP
#define SAND_HPP

#include "particle.hpp"

class Sand : public Particle {
public:
    Sand(sf::RectangleShape box, sf::Vector2f mouse_coords);
    ~Sand() = default;

    void update() override;
};

#endif
