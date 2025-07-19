#include "../include/button.hpp"

#include "../include/constants.hpp"

Button::Button()
    : is_hovered(false)
    , is_pressed(false)
    , font()
    , text(font, "", FONT_SZ)
{
    if (!font.openFromFile("font/pixelify_sans.ttf")) {
        throw std::runtime_error("Error : Couldn't load font/pixelify_sans.ttf");
    }

    box.setSize(BTN_SZ);
    box.setOrigin(box.getGeometricCenter());

    white_box.setSize(BTN_SZ);
    white_box.setOrigin(white_box.getGeometricCenter());
    white_box.setPosition(box.getPosition());
    white_box.setFillColor(sf::Color::Transparent);

    text.setFillColor(sf::Color::White);
    text.setOrigin(box.getGeometricCenter());
    text.setPosition(box.getPosition());
}

void Button::update(sf::Vector2f mouse_coords) {
    is_hovered = isHovered(mouse_coords);
    is_pressed = isPressed(mouse_coords);

    if (is_pressed) {
        white_box.setFillColor(sf::Color::White);
    } else if (is_hovered) {
        white_box.setFillColor(CLR_BTN_WHITE_HOVERED);
    } else {
        white_box.setFillColor(sf::Color::Transparent);
    }
}

void Button::draw(sf::RenderWindow& window) const {
    window.draw(box);
    window.draw(text);
}

bool Button::isHovered(sf::Vector2f mouse_coords) const {
    return (box.getGlobalBounds().contains(mouse_coords));
}

bool Button::isPressed(sf::Vector2f mouse_coords) const {
    return (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && is_hovered);
}

void Button::setLabel(std::string_view _label) {
    label = _label;
    text.setString(label.data());
}

void Button::setPos(sf::Vector2f pos) {
    box.setPosition(pos);
    white_box.setPosition(pos);
    text.setPosition(pos);
}
