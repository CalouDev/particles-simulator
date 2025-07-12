#ifndef UI_PARTICLES_CHOICE_HPP
#define UI_PARTICLES_CHOICE_HPP

#include <SFML/Graphics.hpp>
#include "constants.hpp"

class ParticlesChoice {
public:
    ParticlesChoice();
    ~ParticlesChoice() = default;

    bool isHovered(sf::Vector2f mouse_coords, sf::RectangleShape outline_box) const;
    bool isPressed(sf::Vector2f mouse_coords, sf::RectangleShape outline_box) const;

    void update(sf::Vector2f mouse_coords, std::vector<sf::RectangleShape> outline_boxes);
    void draw(sf::RenderWindow& window) const;

    ParticlesType getCurrentParticleType() const;
    std::vector<sf::RectangleShape> getOutlineBoxes() const;

    void setCurrentParticleType(ParticlesType new_type);
private:
    std::vector<sf::RectangleShape> outline_boxes;
    std::vector<sf::RectangleShape> clred_boxes;
    std::vector<ParticlesType> particles_type;
    bool hovered;
    bool pressed;
    bool menu_open;
    ParticlesType current_particle_type;
    sf::Font font;
    std::vector<sf::Text> particle_names;
};

#endif
