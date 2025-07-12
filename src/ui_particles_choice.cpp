#include "../include/ui_particles_choice.hpp"
#include "../include/constants.hpp"

ParticlesChoice::ParticlesChoice()
    : outline_boxes(N_PARTICLE_TYPES)
    , clred_boxes(N_PARTICLE_TYPES)
    , particles_type(N_PARTICLE_TYPES)
    , hovered(false)
    , pressed(false)
    , menu_open(false)
    , current_particle_type(GroundType)
    , font()
    , particle_names(N_PARTICLE_TYPES, sf::Text(font, std::string(NAMES_PARTICLES[current_particle_type]), FONT_SZ))
{
    if (!font.openFromFile("font/pixelify_sans.ttf")) {
        throw std::runtime_error("Error : Couldn't load font/pixelify_sans.ttf");
    }

    for (int i = 0; i < N_PARTICLE_TYPES; ++i) {
        outline_boxes[i].setSize(sf::Vector2f(BTN_CHOICE_SZ_W, BTN_CHOICE_SZ_H));
        outline_boxes[i].setFillColor(CLR_BTN_BG);
        outline_boxes[i].setOutlineThickness(1);
        outline_boxes[i].setOutlineColor(sf::Color::White);
        outline_boxes[i].setOrigin(outline_boxes[i].getGeometricCenter());
        outline_boxes[i].setPosition(sf::Vector2f(1205.f, 30.f + 60.f * i));

        clred_boxes[i].setSize(sf::Vector2f(BTN_CHOICE_SZ_W - 10, BTN_CHOICE_SZ_H - 10));
        clred_boxes[i].setFillColor(CLRS_PARTICLES[i]);
        clred_boxes[i].setOrigin(clred_boxes[i].getGeometricCenter());
        clred_boxes[i].setPosition(outline_boxes[i].getPosition());

        particle_names[i].setFont(font);
        particle_names[i].setString(std::string(NAMES_PARTICLES[i]));
        particle_names[i].setCharacterSize(FONT_SZ);
        particle_names[i].setOrigin(particle_names[i].getLocalBounds().getCenter());
        particle_names[i].setPosition(outline_boxes[i].getPosition());

        particles_type[i] = static_cast<ParticlesType>(i);
    }
}

bool ParticlesChoice::isHovered(sf::Vector2f mouse_coords, sf::RectangleShape outline_box) const {
    sf::Vector2f btn_pos = outline_box.getPosition();
    return (mouse_coords.x >= (btn_pos.x - BTN_CHOICE_SZ_W/2) && mouse_coords.x <= (btn_pos.x + BTN_CHOICE_SZ_W/2) && mouse_coords.y >= (btn_pos.y - BTN_CHOICE_SZ_H/2) && mouse_coords.y <= (btn_pos.y + BTN_CHOICE_SZ_H/2));
}

bool ParticlesChoice::isPressed(sf::Vector2f mouse_coords, sf::RectangleShape outline_box) const {
    return (isHovered(mouse_coords, outline_box) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
}

void ParticlesChoice::update(sf::Vector2f mouse_coords, std::vector<sf::RectangleShape> outline_boxes) {
    for (int i = 0; i < N_PARTICLE_TYPES; ++i) {
        if (isPressed(mouse_coords, outline_boxes[i])) {
            outline_boxes[i].setFillColor(CLR_BTN_PRESSED);
            if (i == 0) {
                menu_open = true;
            } else if (menu_open) {
                std::swap(particles_type[i], particles_type[0]);
                setCurrentParticleType(particles_type[0]);
                std::swap(outline_boxes[i], outline_boxes[0]);
                std::swap(clred_boxes[i], clred_boxes[0]);
                sf::Vector2f temp_pos = clred_boxes[0].getPosition();
                clred_boxes[0].setPosition(clred_boxes[i].getPosition());
                clred_boxes[i].setPosition(temp_pos);
                std::swap(particle_names[i], particle_names[0]);
                temp_pos = particle_names[0].getPosition();
                particle_names[0].setPosition(particle_names[i].getPosition());
                particle_names[i].setPosition(temp_pos);
                menu_open = false;
            }
        } else if (isHovered(mouse_coords, outline_boxes[i])) {
            outline_boxes[i].setFillColor(CLR_BTN_HOVERED);
        } else {
            outline_boxes[i].setFillColor(CLR_BTN_BG);
        }
    }
}

void ParticlesChoice::draw(sf::RenderWindow& window) const {
    window.draw(outline_boxes[0]);
    window.draw(clred_boxes[0]);
    window.draw(particle_names[0]);

    if (menu_open) {    
        for (int i = 1; i < N_PARTICLE_TYPES; ++i) {
            window.draw(outline_boxes[i]);
            window.draw(clred_boxes[i]);
            window.draw(particle_names[i]);
        }
    }
}

ParticlesType ParticlesChoice::getCurrentParticleType() const {
    return current_particle_type;
}

std::vector<sf::RectangleShape> ParticlesChoice::getOutlineBoxes() const {
    return outline_boxes;
}

void ParticlesChoice::setCurrentParticleType(ParticlesType new_type) {
    current_particle_type = new_type;
}
