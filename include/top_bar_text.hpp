#ifndef TOP_BAR_TEXT
#define TOP_BAR_TEXT

#include <SFML/Graphics.hpp>

#include "particle_manager.hpp"

class TopBarText {
private:
    bool init;
    sf::Clock clk;
    sf::Clock interval;
    sf::Font font;
    sf::Text fps_text;
    sf::Text num_particles_text;
public:
    TopBarText(const sf::Font& font);

    void updateNumParticlesText(ParticlesManager manager);
    void updateFramerate();
    void update(ParticlesManager manager);
    void draw(sf::RenderWindow& window);
};

#endif
