#include "../include/app.hpp"

App::App()
    : window(initWindowSettings())
    , grid_delimitation(sf::Vector2f(POS_UI_PANEL.x - 10.f, WIN_Hf - POS_FPS.y - FONT_SZ/2 - 10.f))
    , ui_panel(sf::Vector2f(WIN_Wf - POS_UI_PANEL.x, WIN_Hf))
    , main_font()
    , framerate(main_font)
{
    //window.setFramerateLimit(FRAMERATE);

    if (!main_font.openFromFile("font/pixelify_sans.ttf")) {
        throw std::runtime_error("Error: Could not load font. FPS counter disabled.\n");
    }

    grid_delimitation.setPosition(sf::Vector2f(5.f, POS_FPS.y + FONT_SZ/2));
    grid_delimitation.setFillColor(sf::Color::Transparent);
    grid_delimitation.setOutlineColor(sf::Color::White);
    grid_delimitation.setOutlineThickness(1);

    ui_panel.setPosition(POS_UI_PANEL);
    ui_panel.setFillColor(CLR_PANEL);
}

App::~App() {
    // In case of manual free alloc
}

sf::RenderWindow App::initWindowSettings() {
    sf::ContextSettings window_settings;
    window_settings.antiAliasingLevel = 8;

    return sf::RenderWindow(
        sf::VideoMode({WIN_W, WIN_H}),
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
        
        main_manager.eventHandler(mouse_coords, prev_mouse_coords, button_panel.getCurrentParticleType());
        framerate.update();
        main_manager.updateParticles();
        button_panel.update(mouse_coords);

        draw();
    }
}

void App::draw() {
    window.clear(CLR_BG);

    // UI - BEHIND
    window.draw(grid_delimitation);
    window.draw(ui_panel);

    // MAIN
    main_manager.drawParticles(window);
    
    // UI - OVER
    button_panel.draw(window);
    framerate.draw(window);

    window.display();

    // END FRAME
    prev_mouse_coords = mouse_coords;
}