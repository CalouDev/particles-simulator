#include "../include/top_bar_text.hpp"

#include "../include/constants.hpp"
#include "../include/particle_manager.hpp"

TopBarText::TopBarText(const sf::Font& font)
    : init(true)
    , fps_text(font, "fps : N/A", FONT_SZ)
    , num_particles_text(font, "number of particles : N/A", FONT_SZ)
{
    fps_text.setOrigin(fps_text.getLocalBounds().getCenter());
    fps_text.setPosition(POS_TEXT_FPS);
    fps_text.setFillColor(sf::Color::White);

    num_particles_text.setOrigin(num_particles_text.getLocalBounds().getCenter());
    num_particles_text.setFillColor(sf::Color::White);
}

void TopBarText::updateNumParticlesText(ParticlesManager& manager) {
    num_particles_text.setString("number of particles : " + std::to_string(manager.getNumParticles()));
}

void TopBarText::updateFramerate() {
    sf::Time delta_time_timer = clk.restart();
    int32_t delta_time = delta_time_timer.asMilliseconds();

    if (init || (delta_time != 0 && interval.getElapsedTime().asMilliseconds() >= REFRESH_RATE_FPS_MS)) {
        if (init) init = false;
        interval.restart();
        fps_text.setString("fps : " + std::to_string(static_cast<int>(1000 / delta_time)));
        num_particles_text.setPosition(sf::Vector2f(fps_text.getPosition().x + fps_text.getGlobalBounds().size.x + TOP_BAR_TEXT_HORIZONTAL_OFFSET, fps_text.getPosition().y));
    }
}

void TopBarText::update(ParticlesManager& manager) {
    updateNumParticlesText(manager);
    updateFramerate();
}

void TopBarText::draw(sf::RenderWindow& window) {
    window.draw(fps_text);
    window.draw(num_particles_text);
}
