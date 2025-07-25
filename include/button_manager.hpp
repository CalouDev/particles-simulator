#ifndef BUTTON_MANAGER_HPP
#define BUTTON_MANAGER_HPP

#include <vector>

#include <SFML/Graphics.hpp>

#include "button.hpp"
#include "constants.hpp"

class ParticlesManager;

class ButtonManager {
private:
    bool playing;
    bool btn_play_press_release;
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

    ParticlesType getCurrentParticleType() const { return current_particle_type; };
    bool getPlaying() const { return playing; }

    void setCurrentParticleType(ParticlesType new_particle_type);
};

#endif
