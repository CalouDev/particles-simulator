#include "../include/particle_manager.hpp"
#include "../include/constants.hpp"

ParticlesManager::ParticlesManager() 
    : grid(GRID_SZ.y + 1, std::vector<ParticlesType>(GRID_SZ.x / PARTICLE_SZ + 1, EmptyType))
{
    for (size_t i = 0; i < grid.size(); ++i) {
        for (size_t j = 0; j < grid[0].size(); ++j) {
            if (EmptyType != grid[i][j])
                printf("%d, ", grid[i][j]);
        }
    }
}

void ParticlesManager::eventHandler(sf::Vector2f mouse_coords, sf::Vector2f previous_mouse_coords, sf::RectangleShape grid_delimitation, ParticlesType particle) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && grid_delimitation.getGlobalBounds().contains(mouse_coords)) {
        interpolateParticles(mouse_coords, previous_mouse_coords, grid_delimitation, particle);
    } else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
        sf::Vector2i remove_particle_pos(static_cast<int>(mouse_coords.x - POS_GRID.x) / PARTICLE_SZ, static_cast<int>(mouse_coords.y - POS_GRID.y) / PARTICLE_SZ);
        if (EmptyType != grid[remove_particle_pos.y][remove_particle_pos.x]) {
            removeParticle(remove_particle_pos);
        }
    }
}

void ParticlesManager::interpolateParticles(sf::Vector2f current_mouse_coords, sf::Vector2f previous_mouse_coords, sf::RectangleShape grid_delimitation, ParticlesType particle) {
    previous_mouse_coords -= POS_GRID;
    current_mouse_coords -= POS_GRID;
    sf::Vector2i icurrent_mouse_coords = sf::Vector2i(static_cast<int>(current_mouse_coords.x / PARTICLE_SZ) * PARTICLE_SZ, static_cast<int>(current_mouse_coords.y / PARTICLE_SZ) * PARTICLE_SZ);
    if (grid_delimitation.getGlobalBounds().contains(current_mouse_coords + POS_GRID) && EmptyType == grid[icurrent_mouse_coords.y/PARTICLE_SZ][icurrent_mouse_coords.x/PARTICLE_SZ]) { 
        addParticles(particle, icurrent_mouse_coords / PARTICLE_SZ);
    }

    sf::Vector2f delta = current_mouse_coords - previous_mouse_coords;
    float distance = std::sqrt(delta.x * delta.x + delta.y * delta.y);
    int steps = static_cast<int>(distance / (PARTICLE_SZ / 2));

    for (int i = 1; i <= steps; ++i) {
        float t = static_cast<float>(i) / steps;
        sf::Vector2f interpolated_pos = previous_mouse_coords + delta * t;
        sf::Vector2i int_interpolated_pos = sf::Vector2i(static_cast<int>(interpolated_pos.x / PARTICLE_SZ), static_cast<int>(interpolated_pos.y / PARTICLE_SZ));
        if (grid_delimitation.getGlobalBounds().contains(interpolated_pos + POS_GRID) && EmptyType == grid[int_interpolated_pos.y][int_interpolated_pos.x]) {
            addParticles(particle, int_interpolated_pos);
        }
    }
}

void ParticlesManager::addParticles(ParticlesType particle, sf::Vector2i particle_coords) {
    grid[particle_coords.y][particle_coords.x] = particle;
    num_particles++;
}

void ParticlesManager::removeParticle(sf::Vector2i particle_coords) {
    grid[particle_coords.y][particle_coords.x] = EmptyType;
    num_particles--;
}

void ParticlesManager::drawParticles(sf::RenderWindow& window, ParticlesType particle, sf::Vector2f particle_pos) {
    sf::RectangleShape particle_shape(sf::Vector2f(PARTICLE_SZ, PARTICLE_SZ));

    particle_shape.setFillColor(PARTICLES_DATA[static_cast<int>(particle)].clr);
    particle_shape.setPosition(sf::Vector2f(particle_pos.x, particle_pos.y) + POS_GRID);
    window.draw(particle_shape);
}

void ParticlesManager::updateParticleBehavior(sf::Vector2i particle_pos) {
    int y = particle_pos.y, x = particle_pos.x;
    ParticlesType current_particle = grid[particle_pos.y][particle_pos.x];

    switch (current_particle) {
        case SandType:
            if ((y + 1) < GRID_SZ.y && x < GRID_SZ.x && EmptyType == grid[y + 1][x]) {
                std::swap(grid[y][x], grid[y + 1][x]);
            } else if ((y + 1) < GRID_SZ.y && (x - 1) < GRID_SZ.x && EmptyType == grid[y + 1][x - 1]) {
                std::swap(grid[y][x], grid[y + 1][x - 1]);
            } else if ((y + 1) < GRID_SZ.y && (x + 1) < GRID_SZ.x && EmptyType == grid[y + 1][x + 1]) {
                std::swap(grid[y][x], grid[y + 1][x + 1]);
            }
            break;
        case WaterType:
            if (EmptyType == grid[y + 1][x]) {
                std::swap(grid[y][x], grid[y + 1][x]);
            } else {
                int dir = ((rand() % 2) ? -1 : 1);

                if (y < GRID_SZ.y && (x + dir) < GRID_SZ.x && EmptyType == grid[y][x + dir]) {
                    std::swap(grid[y][x], grid[y][x + dir]);
                } else if (y < GRID_SZ.y && (x - dir) < GRID_SZ.x && EmptyType == grid[y][x - dir]) {
                    std::swap(grid[y][x], grid[y][x - dir]);
                } else if ((y + 1) < GRID_SZ.y && (x + dir) < GRID_SZ.x && EmptyType == grid[y + 1][x + dir]) {
                    std::swap(grid[y][x], grid[y + 1][x + dir]);
                } else if ((y + 1) < GRID_SZ.y && (x - dir) < GRID_SZ.x && EmptyType == grid[y + 1][x - dir]) {
                    std::swap(grid[y][x], grid[y + 1][x - dir]);
                }
            }
            break;
        default:
            break;
    }
}

void ParticlesManager::updateParticles(sf::RenderWindow& window, ButtonManager& manager) {
    for (size_t i = 0; i < GRID_SZ.y / PARTICLE_SZ - 1; ++i) {
        for (size_t j = 0; j < GRID_SZ.x / PARTICLE_SZ - 1; ++j) {
            if (EmptyType != grid[i][j]) {
                drawParticles(window, grid[i][j], sf::Vector2f(j, i) * static_cast<float>(PARTICLE_SZ));
                if (manager.getPlaying()) {
                    updateParticleBehavior(sf::Vector2i(j, i));
                }
            }
        }
    }
}
