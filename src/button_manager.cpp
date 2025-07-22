#include "../include/button_manager.hpp"

#include <windows.h>
#include <filesystem>

ButtonManager::ButtonManager()
    : current_particle_type(GroundType)
    , outline_box(OUTLINE_BTN_SZ)
    , font()
    , buttons()
{
    wchar_t buffer[MAX_PATH];
    GetModuleFileNameW(nullptr, buffer, MAX_PATH);

    std::filesystem::path bin_path = std::filesystem::path(buffer).parent_path();
    std::filesystem::path font_path = bin_path / ".." / "font" / "pixelify_sans.ttf";

    if (!font.openFromFile(font_path)) {
        throw std::runtime_error("Error: Could not load font.\n");
    }

    for (int i = 0; i < N_PARTICLE_TYPES; ++i) {
        std::unique_ptr<Button> button = std::make_unique<Button>(font);
        button->setLabel(PARTICLES_DATA[i].name);
        button->setPos(sf::Vector2f(1205.f, 30.f + 60.f * i));
        button->setClr(PARTICLES_DATA[i].clr);
        buttons.push_back(std::move(button));
    }

    outline_box.setOrigin(outline_box.getGeometricCenter());
    outline_box.setPosition(buttons[0]->getPos());
    outline_box.setFillColor(sf::Color::Transparent);
    outline_box.setOutlineColor(sf::Color::White);
    outline_box.setOutlineThickness(1);
}

void ButtonManager::update(sf::Vector2f mouse_coords) {
    for (int i = 0; i < N_PARTICLE_TYPES; ++i) {
        buttons[i]->update(mouse_coords);

        if (buttons[i]->getIsPressed()) {
            current_particle_type = static_cast<ParticlesType>(i);
            outline_box.setPosition(buttons[i]->getPos());
        }
    }
}

void ButtonManager::draw(sf::RenderWindow& window) const {
    window.draw(outline_box);
 
    for (int i = 0; i < N_PARTICLE_TYPES; ++i) {
        buttons[i]->draw(window);
    }
}

ParticlesType ButtonManager::getCurrentParticleType() const {
    return current_particle_type;
}

void ButtonManager::setCurrentParticleType(ParticlesType new_particle_type) {
    current_particle_type = new_particle_type;
}
