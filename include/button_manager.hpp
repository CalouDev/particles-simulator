#ifndef BUTTON_MANAGER_HPP
#define BUTTON_MANAGER_HPP

#include <vector>

#include <SFML/Graphics.hpp>

#include "button.hpp"
#include "constants.hpp"
#include "particle_manager.hpp"

class ButtonManager {
private:
    bool removing;
    ParticlesType current_particle_type;
    sf::RectangleShape outline_box;
    sf::Font font;
    sf::Texture texture_btn_play;
    sf::Texture texture_btn_remove;
    sf::Sprite sprite_btn_play;
    sf::Sprite sprite_btn_remove;
    std::unique_ptr<Button> btn_play;
    std::unique_ptr<Button> btn_remove;
    std::vector<std::unique_ptr<Button>> buttons;
public:
    ButtonManager();
    ~ButtonManager() = default;

    void update(sf::Vector2f mouse_coords, ParticlesManager& manager);
    void draw(sf::RenderWindow& window) const;

    ParticlesType getCurrentParticleType() const;

    void setCurrentParticleType(ParticlesType new_particle_type);
};

#endif
