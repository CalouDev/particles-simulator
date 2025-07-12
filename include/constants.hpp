#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#include <SFML/Graphics.hpp>

enum ParticlesType {
    GroundType,
    SandType,
    WaterType,
    FireType
};

constexpr int WIN_W = 1280;
constexpr int WIN_H = 640;
constexpr int FRAMERATE = 120;
constexpr int DEBUG = 1;
constexpr int N_PARTICLE_TYPES = 4;

constexpr sf::Color CLR_BG = {16, 18, 28, 255};
constexpr sf::Color CLR_GROUND = {77, 53, 51, 255};
constexpr sf::Color CLR_SAND = {194, 178, 128, 255};
constexpr sf::Color CLR_WATER = {83, 132, 165, 255};
constexpr sf::Color CLR_FIRE = {255, 51, 0, 255};
constexpr sf::Color CLRS_PARTICLES[N_PARTICLE_TYPES] = {CLR_GROUND, CLR_SAND, CLR_WATER, CLR_FIRE};
constexpr std::string_view NAMES_PARTICLES[N_PARTICLE_TYPES] = {"Ground", "Sand", "Water", "Fire"};

constexpr sf::Color CLR_BTN_BG = {51, 51, 51, 255};
constexpr sf::Color CLR_BTN_HOVERED = {153, 153, 153, 255};
constexpr sf::Color CLR_BTN_PRESSED = {204, 204, 204, 255};

constexpr int FONT_SZ = 20;
constexpr float BTN_CHOICE_SZ_W = 100;
constexpr float BTN_CHOICE_SZ_H = 40;

constexpr int PARTICLE_SZ = 8;

#endif
