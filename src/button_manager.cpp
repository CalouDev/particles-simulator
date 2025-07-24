#include "../include/button_manager.hpp"

#include <windows.h>
#include <filesystem>

ButtonManager::ButtonManager()
    : removing(false)
    , current_particle_type(GroundType)
    , outline_box(OUTLINE_BTN_SZ)
    , font()
    , sprite_btn_play(texture_btn_play)
    , sprite_btn_remove(texture_btn_remove)
    , btn_play(std::make_unique<Button>(font))
    , btn_remove(std::make_unique<Button>(font))
    , buttons()
{
    wchar_t buffer[MAX_PATH];
    GetModuleFileNameW(nullptr, buffer, MAX_PATH);

    std::filesystem::path bin_path = std::filesystem::path(buffer).parent_path();
    std::filesystem::path font_path = bin_path / ".." / "font" / "roboto.ttf";
    std::filesystem::path img_btn_play_path = bin_path / ".." / "images" / "button_play.png";
    std::filesystem::path img_btn_remove_path = bin_path / ".." / "images" / "button_remove.png";

    if (!font.openFromFile(font_path) || !texture_btn_remove.loadFromFile(img_btn_remove_path) || !texture_btn_play.loadFromFile(img_btn_play_path)) {
        throw std::runtime_error("Error: Could not load media.\n");
    }

    btn_remove->setPos(POS_GRID + sf::Vector2f(GRID_SZ.x - TOP_BTN_SZ.x/2, -TOP_BTN_SZ.y/2 - 3.F));
    btn_remove->setSz(TOP_BTN_SZ);
    btn_remove->setClr(sf::Color::Transparent);

    btn_play->setPos(btn_remove->getPos() - sf::Vector2f(TOP_BTN_SZ.x + 5.f, 0.f));
    btn_play->setSz(TOP_BTN_SZ);
    btn_play->setClr(sf::Color::Transparent);

    sprite_btn_play.setTexture(texture_btn_play);
    sprite_btn_play.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), TOP_BTN_SZi));
    sprite_btn_remove.setTexture(texture_btn_remove);
    sprite_btn_remove.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), TOP_BTN_SZi));
    sprite_btn_play.setOrigin(sprite_btn_play.getLocalBounds().getCenter());
    sprite_btn_remove.setOrigin(sprite_btn_remove.getLocalBounds().getCenter());
    sprite_btn_remove.setPosition(btn_remove->getPos());
    sprite_btn_play.setPosition(btn_play->getPos());

    for (int i = 0; i < N_PARTICLE_TYPES; ++i) {
        std::unique_ptr<Button> button = std::make_unique<Button>(font);
        button->setLabel(PARTICLES_DATA[i].name);
        button->setPos(sf::Vector2f(1205.f, POS_GRID.y + OUTLINE_BTN_SZ.y/2 + BTN_VERTICAL_OFFSET * i));
        button->setClr(PARTICLES_DATA[i].clr);
        buttons.push_back(std::move(button));
    }

    outline_box.setOrigin(outline_box.getGeometricCenter());
    outline_box.setPosition(buttons[0]->getPos());
    outline_box.setFillColor(sf::Color::Transparent);
    outline_box.setOutlineColor(sf::Color::White);
    outline_box.setOutlineThickness(1);
}

void ButtonManager::update(sf::Vector2f mouse_coords, ParticlesManager manager) {
    btn_play->update(mouse_coords);
    btn_remove->update(mouse_coords);

    if (!removing && btn_remove->getIsPressed()) {
        removing = true;

        for (size_t i = 0; i < GRID_SZ.y && manager.getNumParticles() > 0; ++i) {
            for (size_t j = 0; j < (GRID_SZ.x / PARTICLE_SZ) && manager.getNumParticles() > 0; ++j) {
                if (EmptyType != manager.getParticleAtPos(sf::Vector2i(j, i))) {
                    manager.removeParticle(sf::Vector2i(j, i));
                }
            }
        }

        removing = false;
    }

    if (btn_play->getIsPressed()) {
        //
    }

    for (int i = 0; i < N_PARTICLE_TYPES; ++i) {
        buttons[i]->update(mouse_coords);

        if (buttons[i]->getIsPressed()) {
            current_particle_type = static_cast<ParticlesType>(i);
            outline_box.setPosition(buttons[i]->getPos());
        }
    }
}

void ButtonManager::draw(sf::RenderWindow& window) const {
    btn_play->draw(window);
    btn_remove->draw(window);
    window.draw(sprite_btn_play);
    window.draw(sprite_btn_remove);
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
