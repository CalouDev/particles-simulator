#ifndef FRAMERATE_HPP
#define FRAMERATE_HPP

#include <SFML/Graphics.hpp>

class FrameRate {
private:
    sf::Clock clk;
    sf::Clock interval;
    sf::Font font;
    sf::Text fps_text;
public:
    FrameRate(const sf::Font& font);

    void update();
    void draw(sf::RenderWindow& window);
};

#endif
