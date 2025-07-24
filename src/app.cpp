#include "../include/app.hpp"

#include <windows.h>
#include <filesystem>

App::App()
    : window(initWindowSettings())
    , grid_delimitation(GRID_SZ)
    , ui_panel(sf::Vector2f(WIN_Wf - POS_UI_PANEL.x, WIN_Hf))
    , main_font()
    , top_bar_text(main_font)
{
    wchar_t buffer[MAX_PATH];
    GetModuleFileNameW(nullptr, buffer, MAX_PATH);

    std::filesystem::path bin_path = std::filesystem::path(buffer).parent_path();
    std::filesystem::path font_path = bin_path / ".." / "font" / "roboto.ttf";

    if (!main_font.openFromFile(font_path)) {
        throw std::runtime_error("Error: Could not load font.\n");
    }

    grid_delimitation.setPosition(POS_GRID);
    grid_delimitation.setFillColor(sf::Color::Transparent);
    grid_delimitation.setOutlineColor(sf::Color::White);
    grid_delimitation.setOutlineThickness(1);

    ui_panel.setPosition(POS_UI_PANEL);
    ui_panel.setFillColor(CLR_PANEL);
}

sf::RenderWindow App::initWindowSettings() {
    sf::ContextSettings window_settings;
    window_settings.antiAliasingLevel = 8;

    return sf::RenderWindow(
        sf::VideoMode(sf::Vector2u(WIN_W, WIN_H)),
        "Particles simulator - SFML " + std::to_string(SFML_VERSION_MAJOR) + "." + std::to_string(SFML_VERSION_MINOR) + "." + std::to_string(SFML_VERSION_PATCH),
        sf::State::Windowed,
        window_settings);
}

void App::mainLoop() {
    while (window.isOpen()) {
        mouse_coords = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        window.clear(CLR_BG);
        
        main_manager.eventHandler(mouse_coords, prev_mouse_coords, grid_delimitation, button_panel.getCurrentParticleType());
        top_bar_text.update(main_manager);
        main_manager.updateParticles(window);
        button_panel.update(mouse_coords, main_manager);

        draw();
    }
}

void App::draw() {
    // UI - BEHIND
    window.draw(grid_delimitation);
    window.draw(ui_panel);

    // MAIN

    
    // UI - OVER
    button_panel.draw(window);
    top_bar_text.draw(window);

    window.display();

    // END FRAME
    prev_mouse_coords = mouse_coords;
}