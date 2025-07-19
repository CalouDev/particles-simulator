#include "../include/spawner.hpp"
#include "../include/constants.hpp"

ParticlesManager::ParticlesManager() 
    : grid(WIN_H / PARTICLE_SZ + 1)
{
    for (std::vector<std::unique_ptr<Particle>>& row : grid) {
        row.resize(WIN_W / PARTICLE_SZ + 1);
    }
}

void ParticlesManager::eventHandler(sf::Vector2f mouse_coords, sf::Vector2f previous_mouse_coords, ParticlesType particle) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        interpolateParticles(particle, mouse_coords, previous_mouse_coords);
    } else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
        for (auto& row : grid)
            for (auto& cell : row)
                cell.reset();
    }
}

void ParticlesManager::interpolateParticles(ParticlesType particle, sf::Vector2f current_mouse_coords, sf::Vector2f previous_mouse_coords) {
    sf::RectangleShape particle_shape(sf::Vector2f(PARTICLE_SZ, PARTICLE_SZ));
    sf::Vector2i icurrent_mouse_coords = sf::Vector2i(std::floor(current_mouse_coords.x), std::floor(current_mouse_coords.y));
    //sf::Vector2i iprevious_mouse_coords = sf::Vector2i(std::floor(previous_mouse_coords.x / 8), std::floor(previous_mouse_coords.y / 8));

    if (icurrent_mouse_coords.y >= 0 && icurrent_mouse_coords.y < GRID_H && icurrent_mouse_coords.x >= 0 && icurrent_mouse_coords.x < GRID_W && grid[icurrent_mouse_coords.y][icurrent_mouse_coords.x] == nullptr) { 
        switch (particle) {
            case GroundType:
                for (int i = -1; i <= 1; ++i) {
                    for (int j = -1; j <= 1; ++j) {
                        addParticles(std::make_unique<Ground>(particle_shape, sf::Vector2f(static_cast<float>(icurrent_mouse_coords.x + i), static_cast<float>(icurrent_mouse_coords.y + j))));
                    }
                }
                break;
            case SandType:
                addParticles(std::make_unique<Sand>(particle_shape, sf::Vector2f(static_cast<float>(icurrent_mouse_coords.x), static_cast<float>(icurrent_mouse_coords.y))));
                break;
            default:
                break;
        }
    }

    sf::Vector2f delta = current_mouse_coords - previous_mouse_coords;
    float distance = std::sqrt(delta.x * delta.x + delta.y * delta.y);
    int steps = static_cast<int>(2 * distance);// / (PARTICLE_SZ/2));

    for (int i = 0; i <= steps; ++i) {
        float t = static_cast<float>(i) / steps;
        sf::Vector2f interpolated_pos = previous_mouse_coords + delta * t;
        sf::Vector2i int_interpolated_pos = sf::Vector2i(std::floor(interpolated_pos.x), std::floor(interpolated_pos.y));
        if (icurrent_mouse_coords.y >= 0 && icurrent_mouse_coords.y < GRID_H && icurrent_mouse_coords.x >= 0 && icurrent_mouse_coords.x < GRID_W && grid[icurrent_mouse_coords.y][icurrent_mouse_coords.x] == nullptr) { 
            switch (particle) {
                case GroundType:
                    for (int i = -1; i <= 1; ++i) {
                        for (int j = -1; j <= 1; ++j) {
                            addParticles(std::make_unique<Ground>(particle_shape, sf::Vector2f(static_cast<float>(int_interpolated_pos.x + i), static_cast<float>(int_interpolated_pos.y + j))));
                        }
                    }
                    break;
                case SandType:
                    addParticles(std::make_unique<Sand>(particle_shape, sf::Vector2f(static_cast<float>(int_interpolated_pos.x), static_cast<float>(int_interpolated_pos.y))));
                    break;
                default:
                    break;
            }
        }
    }
}

void ParticlesManager::addParticles(std::unique_ptr<Particle> particle) {
    if (particle != nullptr) {
        int gridY = static_cast<int>(particle->getPos().y) / PARTICLE_SZ;
        int gridX = static_cast<int>(particle->getPos().x) / PARTICLE_SZ;

        if (gridY >= 0 && gridY < GRID_H && gridX >= 0 && gridX < GRID_W) {
            grid[gridY][gridX] = std::move(particle);
        } else {
            //printf("gridY %lld ; gridX %lld\n", gridY, gridX);
        }
    }
}

void ParticlesManager::drawParticles(sf::RenderWindow& window) {
    for (int i = 0; i < GRID_H; ++i) {
        for (int j = 0; j < GRID_W; ++j) {
            if (grid[i][j] != nullptr) {
                grid[i][j]->draw(window);
            }
        }
    }
}

void ParticlesManager::updateParticles() {
    for (int i = 0; i < GRID_H; ++i) {
        for (int j = 0; j < GRID_W; ++j) {
            if (grid[i][j] != nullptr) {
                grid[i][j]->update();
            }
        }
    }
}
