#include "../include/ui_particles_choice.hpp"
#include "../include/constants.hpp"

ParticlesChoice::ParticlesChoice()
    : outline_box(sf::Vector2f(BTN_CHOICE_SZ_W, BTN_CHOICE_SZ_H))
    , clred_box(sf::Vector2f(BTN_CHOICE_SZ_W - 10, BTN_CHOICE_SZ_H - 10))
    , hovered(false)
    , pressed(false)
    , menu_open(false)
    , current_particle_type(GroundType)
    , font()
    , particle_name(font, std::string(NAMES_PARTICLES[current_particle_type]), FONT_SZ)
{
    outline_box.setFillColor(CLR_BTN_BG);
    outline_box.setOutlineThickness(1);
    outline_box.setOutlineColor(sf::Color::White);
    outline_box.setOrigin(outline_box.getGeometricCenter());
    outline_box.setPosition(sf::Vector2f(1205.f, 40.f));

    clred_box.setFillColor(CLRS_PARTICLES[current_particle_type]);
    clred_box.setOrigin(clred_box.getGeometricCenter());
    clred_box.setPosition(outline_box.getPosition());

    if (!font.openFromFile("font/pixelify_sans.ttf")) {
        throw std::runtime_error("Error : Couldn't load font/pixelify_sans.ttf");
    }

    particle_name.setFont(font);
    particle_name.setString(std::string(NAMES_PARTICLES[current_particle_type]));
    particle_name.setCharacterSize(FONT_SZ);
    particle_name.setOrigin(particle_name.getLocalBounds().getCenter());
    particle_name.setPosition(outline_box.getPosition());
}

bool ParticlesChoice::isHovered(sf::Vector2f mouse_coords) const {
    sf::Vector2f btn_pos = outline_box.getPosition();
    return (mouse_coords.x >= (btn_pos.x - BTN_CHOICE_SZ_W/2) && mouse_coords.x <= (btn_pos.x + BTN_CHOICE_SZ_W/2) && mouse_coords.y >= (btn_pos.y - BTN_CHOICE_SZ_H/2) && mouse_coords.y <= (btn_pos.y + BTN_CHOICE_SZ_H/2));
}

bool ParticlesChoice::isPressed(sf::Vector2f mouse_coords) const {
    return (isHovered(mouse_coords) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
}

void ParticlesChoice::update(sf::Vector2f mouse_coords) {
    if (isHovered(mouse_coords)) {
        outline_box.setFillColor(CLR_BTN_HOVERED);
    } else if (isPressed(mouse_coords)) {
        outline_box.setFillColor(CLR_BTN_PRESSED);
    } else {
        outline_box.setFillColor(CLR_BTN_BG);
    }
}

void ParticlesChoice::draw(sf::RenderWindow& window) const {
    window.draw(outline_box);
    window.draw(clred_box);
    window.draw(particle_name);
    // if (menu) { draw() }
}

ParticlesType ParticlesChoice::getCurrentParticleType() const {
    return current_particle_type;
}

void ParticlesChoice::setCurrentParticleType(ParticlesType new_type) {
    current_particle_type = new_type;
}
