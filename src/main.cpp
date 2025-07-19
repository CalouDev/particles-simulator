#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "../include/constants.hpp"
#include "../include/particle.hpp"
#include "../include/sand.hpp"
#include "../include/spawner.hpp"
#include "../include/button_manager.hpp"

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

    sf::Clock clk;
    sf::Font font;
    sf::Text framerate_txt(font);
    framerate_txt.setPosition(sf::Vector2f(10.0f, 10.0f));

    if (font.openFromFile("font/pixelify_sans.ttf")) {
        framerate_txt.setFont(font);
        framerate_txt.setCharacterSize(FONT_SZ);
        framerate_txt.setPosition(sf::Vector2f(10.0f, 10.0f));
        framerate_txt.setFillColor(sf::Color::White);
    } else {
        throw std::runtime_error("Error: Could not load font. FPS counter disabled.\n");
    }

    while (window.isOpen()) {
        // UPDATE
        sf::Time delta_time_timer = clk.restart();
        double delta_time = delta_time_timer.asMilliseconds();

        framerate_txt.setString("FPS : " + std::to_string(static_cast<int>(1000 / delta_time)));

        mouse_coords = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        main_manager.eventHandler(mouse_coords, prev_mouse_coords, btn_choice.getCurrentParticleType());

        main_manager.updateParticles();

        btn_choice.update(mouse_coords);

        window.clear(CLR_BG);

        // UI - BEHIND
        window.draw(ui_panel);

        // DRAW
        main_manager.drawParticles(window);
        
        // UI - OVER
        
        btn_choice.draw(window);
        if (DEBUG) window.draw(framerate_txt);
    
        window.display();

        // END FRAME
        prev_mouse_coords = mouse_coords;
    }

    return 0;
}
