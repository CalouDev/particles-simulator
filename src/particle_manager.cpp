#include "../include/particle_manager.hpp"
#include "../include/constants.hpp"

#include <algorithm>

ParticlesManager::ParticlesManager() 
    : num_particles(0)
    , is_mouse_visible(true)
    , cursor(sf::Vector2f(6.f, 6.f))
    , grid(GRID_SZ.y + 1, std::vector<ParticleCell>(GRID_SZ.x / PARTICLE_SZ + 1, ParticleCell({EmptyType, sf::Color::Transparent, -1})))
{
    cursor.setOrigin(cursor.getGeometricCenter());
    cursor.setFillColor(sf::Color::Transparent);
    cursor.setOutlineColor(sf::Color::White);
    cursor.setOutlineThickness(1);
}

void ParticlesManager::eventHandler(sf::RenderWindow& window, sf::Vector2f mouse_coords, sf::Vector2f previous_mouse_coords, sf::RectangleShape grid_delimitation, ParticlesType particle) {
    if (grid_delimitation.getGlobalBounds().contains(mouse_coords)) {
        cursor.setPosition(sf::Vector2f(static_cast<int>(mouse_coords.x / PARTICLE_SZ) * PARTICLE_SZ, static_cast<int>(mouse_coords.y / PARTICLE_SZ) * PARTICLE_SZ));
        window.setMouseCursorVisible(false);
        is_mouse_visible = false;

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            interpolateParticles(mouse_coords, previous_mouse_coords, grid_delimitation, particle);
        } else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
            sf::Vector2i remove_particle_pos(static_cast<int>(mouse_coords.x - POS_GRID.x) / PARTICLE_SZ, static_cast<int>(mouse_coords.y - POS_GRID.y) / PARTICLE_SZ);
            if (EmptyType != grid[remove_particle_pos.y][remove_particle_pos.x].type) {
                removeParticle(remove_particle_pos);
            }
        }
    } else {
        window.setMouseCursorVisible(true);
        is_mouse_visible = true;
    }
}

void ParticlesManager::interpolateParticles(sf::Vector2f current_mouse_coords, sf::Vector2f previous_mouse_coords, sf::RectangleShape grid_delimitation, ParticlesType particle) {
    previous_mouse_coords -= POS_GRID;
    current_mouse_coords -= POS_GRID;
    sf::Vector2i icurrent_mouse_coords = sf::Vector2i(static_cast<int>(current_mouse_coords.x / PARTICLE_SZ) * PARTICLE_SZ, static_cast<int>(current_mouse_coords.y / PARTICLE_SZ) * PARTICLE_SZ);
    if (grid_delimitation.getGlobalBounds().contains(current_mouse_coords + POS_GRID) && EmptyType == grid[icurrent_mouse_coords.y/PARTICLE_SZ][icurrent_mouse_coords.x/PARTICLE_SZ].type) { 
        addParticles(particle, icurrent_mouse_coords / PARTICLE_SZ);
    }

    sf::Vector2f delta = current_mouse_coords - previous_mouse_coords;
    float distance = std::sqrt(delta.x * delta.x + delta.y * delta.y);
    int steps = static_cast<int>(distance / (PARTICLE_SZ / 2));

    for (int i = 1; i <= steps; ++i) {
        float t = static_cast<float>(i) / steps;
        sf::Vector2f interpolated_pos = previous_mouse_coords + delta * t;
        sf::Vector2i int_interpolated_pos = sf::Vector2i(static_cast<int>(interpolated_pos.x / PARTICLE_SZ), static_cast<int>(interpolated_pos.y / PARTICLE_SZ));
        if (grid_delimitation.getGlobalBounds().contains(interpolated_pos + POS_GRID) && EmptyType == grid[int_interpolated_pos.y][int_interpolated_pos.x].type) {
            addParticles(particle, int_interpolated_pos);
        }
    }
}

void ParticlesManager::addParticles(ParticlesType particle, sf::Vector2i particle_coords) {
    int rand_clr_index = (rand() % 3);

    grid[particle_coords.y][particle_coords.x].type = particle;
    grid[particle_coords.y][particle_coords.x].clr = PARTICLES_DATA[particle].clr[rand_clr_index];
    num_particles++;
}

void ParticlesManager::removeParticle(sf::Vector2i particle_coords) {
    grid[particle_coords.y][particle_coords.x].type = EmptyType;
    grid[particle_coords.y][particle_coords.x].clr = sf::Color(sf::Color::Transparent);
    grid[particle_coords.y][particle_coords.x].lifetime = 0;
    num_particles--;
}

void ParticlesManager::drawParticles(sf::RenderWindow& window, sf::Color clr, sf::Vector2f particle_pos) {
    sf::RectangleShape particle_shape(sf::Vector2f(PARTICLE_SZ, PARTICLE_SZ));

    particle_shape.setFillColor(clr);
    particle_shape.setPosition(sf::Vector2f(particle_pos.x, particle_pos.y) + POS_GRID);
    window.draw(particle_shape);
}

void ParticlesManager::updateParticleBehavior(sf::Vector2i particle_pos) {
    int y = particle_pos.y, x = particle_pos.x;
    ParticlesType current_particle = grid[particle_pos.y][particle_pos.x].type;

    switch (current_particle) {
        case SandType:
            if ((y + 1) < GRID_SZ.y && x < GRID_SZ.x && EmptyType == grid[y + 1][x].type) {
                std::swap(grid[y][x], grid[y + 1][x]);
            } else if ((y + 1) < GRID_SZ.y && (x - 1) < GRID_SZ.x && EmptyType == grid[y + 1][x - 1].type && GroundType != grid[y][x - 1].type) {
                std::swap(grid[y][x], grid[y + 1][x - 1]);
            } else if ((y + 1) < GRID_SZ.y && (x + 1) < GRID_SZ.x && EmptyType == grid[y + 1][x + 1].type && GroundType != grid[y][x + 1].type) {
                std::swap(grid[y][x], grid[y + 1][x + 1]);
            }
            break;
        case WaterType:
            if (EmptyType == grid[y + 1][x].type) {
                std::swap(grid[y][x], grid[y + 1][x]);
            } else {
                int rand_dir = ((rand() % 2) ? -1 : 1);

                if (y < GRID_SZ.y && (x + rand_dir) < GRID_SZ.x && EmptyType == grid[y][x + rand_dir].type) {
                    std::swap(grid[y][x], grid[y][x + rand_dir]);
                } else if (y < GRID_SZ.y && (x - rand_dir) < GRID_SZ.x && EmptyType == grid[y][x - rand_dir].type) {
                    std::swap(grid[y][x], grid[y][x - rand_dir]);
                } else if ((y + 1) < GRID_SZ.y && (x + rand_dir) < GRID_SZ.x && EmptyType == grid[y + 1][x + rand_dir].type && GroundType != grid[y][x + rand_dir].type) {
                    std::swap(grid[y][x], grid[y + 1][x + rand_dir]);
                } else if ((y + 1) < GRID_SZ.y && (x - rand_dir) < GRID_SZ.x && EmptyType == grid[y + 1][x - rand_dir].type && GroundType != grid[y][x - rand_dir].type) {
                    std::swap(grid[y][x], grid[y + 1][x - rand_dir]);
                }
            }
            break;
        case PowderType:
            if ((y + 1) < GRID_SZ.y && x < GRID_SZ.x && EmptyType == grid[y + 1][x].type) {
                std::swap(grid[y][x], grid[y + 1][x]);
            } else if ((y + 1) < GRID_SZ.y && (x - 1) < GRID_SZ.x && EmptyType == grid[y + 1][x - 1].type && GroundType != grid[y][x - 1].type) {
                std::swap(grid[y][x], grid[y + 1][x - 1]);
            } else if ((y + 1) < GRID_SZ.y && (x + 1) < GRID_SZ.x && EmptyType == grid[y + 1][x + 1].type && GroundType != grid[y][x + 1].type) {
                std::swap(grid[y][x], grid[y + 1][x + 1]);
            }
            break;
        case FireType:
            grid[y][x].lifetime--;
            if (grid[y][x].lifetime <= -50) {
                removeParticle(sf::Vector2i(x, y));
            } else if (grid[y][x].lifetime == 0) {
                if (grid[y][x].clr == CLR_FIRE_DARK) grid[y][x].clr = PARTICLES_DATA[SmokeType].clr[0];
                else if (grid[y][x].clr == CLR_FIRE_DARK2) grid[y][x].clr = PARTICLES_DATA[SmokeType].clr[1];
                else grid[y][x].clr = PARTICLES_DATA[SmokeType].clr[2];

                grid[y][x].type = SmokeType;
                grid[y][x].lifetime = INFINITE_LIFETIME;
            } else if (grid[y][x].lifetime <= PARTICLES_DATA[FireType].lifetime/2) {
                if (grid[y][x].clr == CLR_FIRE) grid[y][x].clr = CLR_FIRE_DARK;
                else if (grid[y][x].clr == CLR_FIRE2) grid[y][x].clr = CLR_FIRE_DARK2;
                else grid[y][x].clr = CLR_FIRE_DARK3;
                
                for (int i = -1; i <= 1; ++i) {
                    for (int j = -1; j <= 1; ++j) {
                        if (PowderType == grid[y + i][x + j].type) {
                            int test = rand() % 7;
                            if ((y + i) < GRID_SZ.y && (x + j) < GRID_SZ.x && test < 1) {
                                int rand_clr_index = (rand() % 3);

                                grid[y + i][x + j].type = FireType;
                                grid[y + i][x + j].clr = PARTICLES_DATA[FireType].clr[rand_clr_index];
                                grid[y + i][x + j].lifetime = PARTICLES_DATA[FireType].lifetime;
                            }
                        }
                    }
                }
            }

            break;
        case SmokeType:
            if ((y - 1) >= 0 && EmptyType == grid[y - 1][x].type) {
                std::swap(grid[y][x], grid[y - 1][x]);
            } else {
                int rand_dir = ((rand() % 2) ? -1 : 1);

                if (y < GRID_SZ.y && (x + rand_dir) < GRID_SZ.x && EmptyType == grid[y][x + rand_dir].type) {
                    std::swap(grid[y][x], grid[y][x + rand_dir]);
                } else if (y < GRID_SZ.y && (x - rand_dir) < GRID_SZ.x && EmptyType == grid[y][x - rand_dir].type) {
                    std::swap(grid[y][x], grid[y][x - rand_dir]);
                } else if ((y - 1) >= 0 && (x + rand_dir) < GRID_SZ.x && EmptyType == grid[y - 1][x + rand_dir].type && GroundType != grid[y][x + rand_dir].type) {
                    std::swap(grid[y][x], grid[y - 1][x + rand_dir]);
                } else if ((y - 1) >= 0 && (x - rand_dir) < GRID_SZ.x && EmptyType == grid[y - 1][x - rand_dir].type && GroundType != grid[y][x - rand_dir].type) {
                    std::swap(grid[y][x], grid[y - 1][x - rand_dir]);
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
            if (EmptyType != grid[i][j].type) {
                drawParticles(window, grid[i][j].clr, sf::Vector2f(j, i) * static_cast<float>(PARTICLE_SZ));
                
                if (manager.getPlaying()) {
                    updateParticleBehavior(sf::Vector2i(j, i));
                }
            }
        }
    }

    if (!is_mouse_visible) {
        window.draw(cursor);
    }
}

void ParticlesManager::setCursorSize(sf::Vector2f sz) {
    sf::Vector2f cursor_sz = cursor.getSize();

    cursor.setSize(sf::Vector2f(std::clamp(sz.x + cursor_sz.x, MIN_CURSOR_SZ.x, MAX_CURSOR_SZ.x), std::clamp(sz.y + cursor_sz.y, MIN_CURSOR_SZ.y, MAX_CURSOR_SZ.y)));
    cursor.setOrigin(cursor.getGeometricCenter());
}
