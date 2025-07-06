#include "../include/ui_particles_choice.hpp"
#include "../include/constants.hpp"

ParticlesChoice::ParticlesChoice()
    : box(sf::Vector2f(BTN_CHOICE_SZ_W, BTN_CHOICE_SZ_H))
    , hovered(false)
    , pressed(false)
    , current_particle_type(GroundType)
{
    box.setFillColor(CLR_BTN_BG);
    box.setOutlineThickness(1);
    box.setOutlineColor(sf::Color::White);
    box.setPosition(sf::Vector2f(1155.f, 20.f));
}

bool ParticlesChoice::isHovered(sf::Vector2f mouse_coords) const {
    sf::Vector2f btn_pos = box.getPosition();
    return (mouse_coords.x >= btn_pos.x && mouse_coords.x <= (btn_pos.x + BTN_CHOICE_SZ_W) && mouse_coords.y >= btn_pos.y && mouse_coords.y <= (btn_pos.y + BTN_CHOICE_SZ_H));
}

bool ParticlesChoice::isPressed(sf::Vector2f mouse_coords) const {
    return (isHovered(mouse_coords) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
}

void ParticlesChoice::update(sf::Vector2f mouse_coords) {
    if (isHovered(mouse_coords)) {
        box.setFillColor(CLR_BTN_HOVERED);
    } else if (isPressed(mouse_coords)) {
        box.setFillColor(CLR_BTN_PRESSED);
    } else {
        box.setFillColor(CLR_BTN_BG);
    }
}

void ParticlesChoice::draw(sf::RenderWindow& window) const {
    sf::RectangleShape rect_current_particles(sf::Vector2f(BTN_CHOICE_SZ_W - 10, BTN_CHOICE_SZ_H - 10));
    sf::Font font("font/pixelify_sans.ttf");
    sf::Text particles_name(font, std::string(NAMES_PARTICLES[current_particle_type]), FONT_SZ);

    rect_current_particles.setFillColor(CLRS_PARTICLES[current_particle_type]);
    rect_current_particles.setPosition(sf::Vector2f(1160.f, 25.f));

    particles_name.setPosition(sf::Vector2f(1170.f, 25.f));
    
    window.draw(box);
    window.draw(rect_current_particles);
    window.draw(particles_name);
}
