#ifndef UI_PARTICLES_CHOICE_HPP
#define UI_PARTICLES_CHOICE_HPP

#include <SFML/Graphics.hpp>
#include "constants.hpp"

class ParticlesChoice {
public:
    ParticlesChoice();
    ~ParticlesChoice() = default;

    bool isHovered(sf::Vector2f mouse_coords) const;
    bool isPressed(sf::Vector2f mouse_coords) const;

    void update(sf::Vector2f mouse_coords);
    void draw(sf::RenderWindow& window) const;

    ParticlesType getCurrentParticleType() const;

    void setCurrentParticleType(ParticlesType new_type);
private:
    sf::RectangleShape outline_box;
    sf::RectangleShape clred_box;
    bool hovered;
    bool pressed;
    bool menu_open;
    ParticlesType current_particle_type;
    sf::Font font;
    sf::Text particle_name;
};

#endif
