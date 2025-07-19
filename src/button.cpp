#include "../include/button.hpp"

#include "../include/constants.hpp"

Button::Button(const sf::Font& pixel_font)
    : is_hovered(false)
    , is_pressed(false)
    , font(pixel_font)
    , text(font, "N/A", FONT_SZ)
{
    box.setSize(BTN_SZ);
    box.setOrigin(box.getGeometricCenter());

    white_box.setSize(BTN_SZ);
    white_box.setOrigin(white_box.getGeometricCenter());
    white_box.setFillColor(sf::Color::Transparent);
    white_box.setOutlineThickness(1);
    white_box.setOutlineColor(sf::Color::White);

    text.setOrigin(text.getLocalBounds().getCenter());
}

void Button::update(sf::Vector2f mouse_coords) {
    is_hovered = isHovered(mouse_coords);
    is_pressed = isPressed(mouse_coords);

    if (is_hovered) {
        white_box.setOutlineThickness(1);
    } else {
        white_box.setOutlineThickness(0);
    }
}

void Button::draw(sf::RenderWindow& window) const {
    window.draw(box);
    window.draw(white_box);
    window.draw(text);
}

bool Button::isHovered(sf::Vector2f mouse_coords) const {
    return (box.getGlobalBounds().contains(mouse_coords));
}

bool Button::isPressed(sf::Vector2f mouse_coords) const {
    return (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && is_hovered);
}

void Button::setClr(sf::Color _clr) {
    clr = _clr;
    box.setFillColor(_clr);
}

void Button::setLabel(std::string_view _label) {
    label = std::string(_label);
    text.setString(label);
    text.setOrigin(text.getLocalBounds().getCenter());
}

void Button::setPos(sf::Vector2f pos) {
    box.setPosition(pos);
    white_box.setPosition(pos);
    text.setPosition(pos);
}
