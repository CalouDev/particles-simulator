#ifndef BUTTON_MANAGER_HPP
#define BUTTON_MANAGER_HPP

#include <vector>

#include <SFML/Graphics.hpp>

#include "button.hpp"
#include "constants.hpp"

class ButtonManager {
private:
    ParticlesType current_particle_type;
    sf::RectangleShape outline_box;
    sf::Font font;
    std::vector<std::unique_ptr<Button>> buttons;
public:
    ButtonManager();
    ~ButtonManager() = default;

    void update(sf::Vector2f mouse_coords);
    void draw(sf::RenderWindow& window) const;

    ParticlesType getCurrentParticleType() const;

    void setCurrentParticleType(ParticlesType new_particle_type);
};

#endif
