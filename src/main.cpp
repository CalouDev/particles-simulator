#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "../include/constants.hpp"
#include "../include/particle.hpp"
#include "../include/sand.hpp"
#include "../include/spawner.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode({WIN_W, WIN_H}), "Particles simulator - SFML " + std::to_string(SFML_VERSION_MAJOR) + "." + std::to_string(SFML_VERSION_MINOR) + "." + std::to_string(SFML_VERSION_PATCH));
    window.setFramerateLimit(FRAMERATE);

    // INITIALIZE
    ParticlesManager main_manager;

    // LOAD
    sf::Vector2f mouse_coords = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    sf::Clock clk;
    sf::Font font("font/sans.ttf");
    sf::Text framerate_txt(font, "", FONT_SZ);
    framerate_txt.setPosition(sf::Vector2f(0.0f, 0.0f));

    while (window.isOpen()) {
        // UPDATE
        sf::Time delta_time_timer = clk.restart();
        double delta_time = delta_time_timer.asMilliseconds();

        framerate_txt.setString(std::to_string(static_cast<int>(1000 / delta_time)) + " fps");

        mouse_coords = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        main_manager.eventHandler(mouse_coords);

        main_manager.updateParticles();

        // DRAW
        window.clear(CLR_BG);

        main_manager.drawParticles(window);

        // UI

        if (DEBUG) window.draw(framerate_txt);
    
        window.display();
    }
}
