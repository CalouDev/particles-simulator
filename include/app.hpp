#ifndef APP_HPP
#define APP_HPP

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "../include/constants.hpp"
#include "../include/particle_manager.hpp"
#include "../include/button_manager.hpp"
#include "../include/top_bar_text.hpp"

class App {
private:
    sf::ContextSettings window_settings;
    sf::RenderWindow window;
    sf::Vector2f mouse_coords, prev_mouse_coords;
    sf::RectangleShape grid_delimitation;
    sf::RectangleShape ui_panel;
    sf::Font main_font;
    ParticlesManager main_manager;
    ButtonManager button_panel;
    TopBarText top_bar_text;
private:
    sf::RenderWindow initWindowSettings();

    void draw();
public:
    App();

    void mainLoop();
};

#endif
