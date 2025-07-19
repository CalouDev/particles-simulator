#include "../include/framerate.hpp"

#include "../include/constants.hpp"

FrameRate::FrameRate(const sf::Font& font)
    : fps_text(font, "FPS : N/A", FONT_SZ)
{
    fps_text.setOrigin(fps_text.getLocalBounds().getCenter());
    fps_text.setPosition(POS_FPS);
    fps_text.setFillColor(sf::Color::White);
}

void FrameRate::update() {
    sf::Time delta_time_timer = clk.restart();
    double delta_time = delta_time_timer.asMilliseconds();

    if (interval.getElapsedTime().asMilliseconds() >= REFRESH_RATE_FPS_MS) {
        interval.restart();
        fps_text.setString("FPS : " + std::to_string(static_cast<int>(1000 / delta_time)));
    }
}

void FrameRate::draw(sf::RenderWindow& window) {
    window.draw(fps_text);
}
