#ifndef SAND_HPP
#define SAND_HPP

#include "particle.hpp"

class Sand : public Particle {
public:
    Sand(sf::RectangleShape box, float x, float y);
    ~Sand() = default;

    void update() override;
};

#endif
