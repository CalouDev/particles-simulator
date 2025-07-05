#ifndef UI_PARTICLES_CHOICE_HPP
#define UI_PARTICLES_CHOICE_HPP

#include <SFML/Graphics.hpp>

class ParticlesChoice {
private:
    sf::RectangleShape box;
    sf::Color default_clr;
    sf::Color hovered_clr;
    sf::Color pressed_clr;
    bool hovered;
    bool pressed;
public:
    enum ParticlesType {
        GroundType,
        SandType
    };

    bool isHovered(float mouse_x, float mouse_y) const;
    bool isPressed(float mouse_x, float mouse_y) const;

    void update();
    void draw() const;
};

#endif
