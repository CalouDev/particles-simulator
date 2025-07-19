#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <SFML/Graphics.hpp>

enum ParticlesType {
    GroundType,
    SandType,
    WaterType,
    FireType
};

struct ParticleInfo {
    sf::Color clr;
    std::string_view name;
};

constexpr int WIN_W = 1280;
constexpr int WIN_H = 640;
constexpr float WIN_Wf = static_cast<float>(WIN_W);
constexpr float WIN_Hf = static_cast<float>(WIN_H);
constexpr int GRID_W = WIN_W;
constexpr int GRID_H = WIN_H;
constexpr int FRAMERATE = 120;

constexpr sf::Color CLR_BG = {16, 18, 28, 255};
constexpr sf::Color CLR_PANEL = {28, 28, 28, 255};
constexpr sf::Color CLR_GROUND = {77, 53, 51, 255};
constexpr sf::Color CLR_SAND = {194, 178, 128, 255};
constexpr sf::Color CLR_WATER = {83, 132, 165, 255};
constexpr sf::Color CLR_FIRE = {255, 51, 0, 255};
constexpr sf::Color CLR_BTN_WHITE_HOVERED = {255, 255, 255, 180};

constexpr int N_PARTICLE_TYPES = 4;
constexpr sf::Color CLRS_PARTICLES[N_PARTICLE_TYPES] = {CLR_GROUND, CLR_SAND, CLR_WATER, CLR_FIRE};
constexpr std::string_view NAMES_PARTICLES[N_PARTICLE_TYPES] = {"Ground", "Sand", "Water", "Fire"};
constexpr std::array<ParticleInfo, N_PARTICLE_TYPES> PARTICLES_DATA = {{
    {CLR_GROUND, "Ground"},
    {CLR_SAND,   "Sand"},
    {CLR_WATER,  "Water"},
    {CLR_FIRE,   "Fire"},
}};

constexpr int FONT_SZ = 20;
constexpr sf::Vector2f BTN_SZ = {100.f, 40.f};
constexpr int PARTICLE_SZ = 1;

constexpr sf::Vector2f POS_FPS = {10.f, 20.f};
constexpr sf::Vector2f POS_UI_PANEL = {1130.f, 0.f};

constexpr int32_t REFRESH_RATE_FPS_MS = 1000;

#endif
