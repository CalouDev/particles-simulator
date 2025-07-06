#ifndef GROUND_HPP
#define GROUND_HPP

#include "particle.hpp"

class Ground : public Particle {
public:
    Ground(sf::RectangleShape box, sf::Vector2f mouse_coords);
    ~Ground() = default;

    void update() override;
};

#endif