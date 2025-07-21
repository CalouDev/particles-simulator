#include "../include/particle_manager.hpp"
#include "../include/constants.hpp"

ParticlesManager::ParticlesManager() 
    : grid(GRID_SZ.y + 1, std::vector<ParticlesType>(GRID_SZ.x + 1, EmptyType))
{}

void ParticlesManager::eventHandler(sf::Vector2f mouse_coords, sf::Vector2f previous_mouse_coords, sf::RectangleShape grid_delimitation, ParticlesType particle) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && grid_delimitation.getGlobalBounds().contains(mouse_coords)) {
        interpolateParticles(mouse_coords, previous_mouse_coords, grid_delimitation, particle);
    } else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
        for (size_t i = 0; i < GRID_SZ.y; ++i) {
            for (size_t j = 0; j < GRID_SZ.x; ++j) {
                if (EmptyType != grid[i][j]) {
                    removeParticle(sf::Vector2i(j, i));
                }
            }
        }
    }
}

void ParticlesManager::interpolateParticles(sf::Vector2f current_mouse_coords, sf::Vector2f previous_mouse_coords, sf::RectangleShape grid_delimitation, ParticlesType particle) {
    previous_mouse_coords -= POS_GRID;
    current_mouse_coords -= POS_GRID;
    sf::Vector2i icurrent_mouse_coords = sf::Vector2i(static_cast<int>(current_mouse_coords.x), static_cast<int>(current_mouse_coords.y));

    if (icurrent_mouse_coords.y >= 0 && icurrent_mouse_coords.y < GRID_SZ.y && icurrent_mouse_coords.x >= 0 &&  icurrent_mouse_coords.x < GRID_SZ.x && EmptyType == grid[icurrent_mouse_coords.y][icurrent_mouse_coords.x] && grid_delimitation.getGlobalBounds().contains(current_mouse_coords)) { 
        addParticles(particle, icurrent_mouse_coords);
    }

    sf::Vector2f delta = current_mouse_coords - previous_mouse_coords;
    float distance = std::sqrt(delta.x * delta.x + delta.y * delta.y);
    int steps = static_cast<int>(2 * distance);

    for (int i = 1; i <= steps; ++i) {
        float t = static_cast<float>(i) / steps;
        sf::Vector2f interpolated_pos = previous_mouse_coords + delta * t;
        sf::Vector2i int_interpolated_pos = sf::Vector2i(static_cast<int>(interpolated_pos.x), static_cast<int>(interpolated_pos.y));
        if (int_interpolated_pos.y >= 0 && int_interpolated_pos.y < GRID_SZ.y && int_interpolated_pos.x >= 0 && int_interpolated_pos.x < GRID_SZ.x && EmptyType == grid[int_interpolated_pos.y][int_interpolated_pos.x] && grid_delimitation.getGlobalBounds().contains(interpolated_pos)) {
            addParticles(particle, int_interpolated_pos);
        }
    }
}

void ParticlesManager::addParticles(ParticlesType particle, sf::Vector2i particle_coords) {
    grid[particle_coords.y][particle_coords.x] = particle;
}

void ParticlesManager::removeParticle(sf::Vector2i particle_coords) {
    grid[particle_coords.y][particle_coords.x] = EmptyType;
}

void ParticlesManager::drawParticles(sf::RenderWindow& window, ParticlesType particle, sf::Vector2f particle_pos) {
    sf::RectangleShape particle_shape(sf::Vector2f(PARTICLE_SZ, PARTICLE_SZ));

    particle_shape.setFillColor(PARTICLES_DATA[static_cast<int>(particle)].clr);
    particle_shape.setPosition(sf::Vector2f(particle_pos.x, particle_pos.y) + POS_GRID);
    window.draw(particle_shape);
    }

void ParticlesManager::updateParticles(sf::RenderWindow& window) {
    for (size_t i = 0; i < grid.size() - 1; ++i) {
        for (size_t j = 0; j < grid[0].size() - 1; ++j) {
            if (EmptyType != grid[i][j]) {
                drawParticles(window, grid[i][j], sf::Vector2f(j, i));
                updateParticleBehavior(sf::Vector2i(j, i));
            }
        }
    }
}

void ParticlesManager::updateParticleBehavior(sf::Vector2i particle_pos) {
    int y = particle_pos.y, x = particle_pos.x;
    ParticlesType current_particle = grid[particle_pos.y][particle_pos.x];

    switch (current_particle) {
        case SandType:
            if (EmptyType == grid[y + 1][x]) {
                std::swap(grid[y][x], grid[y + 1][x]);
            } else if (EmptyType == grid[y + 1][x - 1]) {
                std::swap(grid[y][x], grid[y + 1][x - 1]);
            } else if (EmptyType == grid[y + 1][x + 1]) {
                std::swap(grid[y][x], grid[y + 1][x + 1]);
            }
            break;
        case WaterType:
            if (grid[y + 1][x] == EmptyType) {
                std::swap(grid[y][x], grid[y + 1][x]);
            } else {
                int dir = ((rand() % 2) ? -1 : 1);

                if (grid[y][x + dir] == EmptyType) {
                    std::swap(grid[y][x], grid[y][x + dir]);
                } else if (grid[y][x - dir] == EmptyType) {
                    std::swap(grid[y][x], grid[y][x - dir]);
                } else if (grid[y + 1][x + dir] == EmptyType) {
                    std::swap(grid[y][x], grid[y + 1][x + dir]);
                } else if (grid[y + 1][x - dir] == EmptyType) {
                    std::swap(grid[y][x], grid[y + 1][x - dir]);
                }
            }
            break;
        default:
            break;
    }
}
