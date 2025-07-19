#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "../include/constants.hpp"
#include "../include/particle.hpp"
#include "../include/sand.hpp"
#include "../include/spawner.hpp"
#include "../include/button_manager.hpp"
#include "../include/framerate.hpp"

int main(void) {
    sf::ContextSettings window_settings;
    window_settings.antiAliasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode({WIN_W, WIN_H}), "Particles simulator - SFML " + std::to_string(SFML_VERSION_MAJOR) + "." + std::to_string(SFML_VERSION_MINOR) + "." + std::to_string(SFML_VERSION_PATCH), sf::State::Windowed, window_settings);
    window.setFramerateLimit(FRAMERATE);

    // INITIALIZE
    ParticlesManager main_manager;
    ButtonManager btn_choice;

    // LOAD
    sf::Vector2f mouse_coords, prev_mouse_coords;
    sf::RectangleShape ui_panel(sf::Vector2f(180.f, WIN_Hf));
    ui_panel.setPosition(sf::Vector2f(1130.f, 0.f));
    ui_panel.setFillColor(CLR_PANEL);

    sf::Font main_font;
    
    if (!main_font.openFromFile("font/pixelify_sans.ttf")) {
        throw std::runtime_error("Error: Could not load font. FPS counter disabled.\n");
    }
    
    FrameRate framerate(main_font);

    while (window.isOpen()) {
        // UPDATE
        mouse_coords = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }
        
        main_manager.eventHandler(mouse_coords, prev_mouse_coords, btn_choice.getCurrentParticleType());
        framerate.update();
        main_manager.updateParticles();
        btn_choice.update(mouse_coords);

        // DRAW

        window.clear(CLR_BG);

        // UI - BEHIND
        window.draw(ui_panel);

        // MAIN
        main_manager.drawParticles(window);
        
        // UI - OVER
        
        btn_choice.draw(window);
        framerate.draw(window);
    
        window.display();

        // END FRAME
        prev_mouse_coords = mouse_coords;
    }

    return 0;
}
