#ifndef GROUND_HPP
#define GROUND_HPP

#include "particle.hpp"

class Ground : public Particle {
public:
    Ground(sf::RectangleShape box, float x, float y);
    ~Ground() = default;

    void update() override;
};

#endif