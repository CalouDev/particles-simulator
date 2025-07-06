#ifndef UI_PARTICLES_CHOICE_HPP
#define UI_PARTICLES_CHOICE_HPP

#include <SFML/Graphics.hpp>

class ParticlesChoice {
public:
    enum ParticlesType {
        GroundType,
        SandType
    };

    ParticlesChoice();
    ~ParticlesChoice() = default;

    bool isHovered(sf::Vector2f mouse_coords) const;
    bool isPressed(sf::Vector2f mouse_coords) const;

    void update(sf::Vector2f mouse_coords);
    void draw(sf::RenderWindow& window) const;

    ParticlesType getCurrentParticleType();
private:
    sf::RectangleShape box;
    sf::Color default_clr;
    sf::Color hovered_clr;
    sf::Color pressed_clr;
    bool hovered;
    bool pressed;
    ParticlesType current_particle_type;
};

#endif
