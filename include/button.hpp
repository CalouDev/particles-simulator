#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <string_view>

#include <SFML/Graphics.hpp>

class Button {
private:
    bool is_hovered;
    bool is_pressed;
    std::string label;

    sf::RectangleShape box;
    sf::RectangleShape white_box;
    sf::Font font;
    sf::Text text;
    sf::Color clr;
private:
    bool isHovered(sf::Vector2f mouse_coords) const;
    bool isPressed(sf::Vector2f mouse_coords) const;
public:
    Button(const sf::Font& pixel_font);
    virtual ~Button() = default;

    void update(sf::Vector2f mouse_coords);
    void draw(sf::RenderWindow& window) const;

    bool getIsHovered() const { return is_hovered; };
    bool getIsPressed() const { return is_pressed; };
    sf::Vector2f getPos() const { return box.getPosition(); }

    void setClr(sf::Color _clr);
    void setLabel(std::string_view _label);
    void setPos(sf::Vector2f pos);
};

#endif
