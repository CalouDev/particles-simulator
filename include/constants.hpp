#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <SFML/Graphics.hpp>

enum ParticlesType : short {
    EmptyType = -1,
    GroundType,
    SandType,
    WaterType,
    PowderType,
    FireType,
    SmokeType
};


struct ParticleCell {
    ParticlesType type;
    sf::Color clr;
    int lifetime;
};

constexpr int WIN_W = 1280;
constexpr int WIN_H = 640;
constexpr float WIN_Wf = static_cast<float>(WIN_W);
constexpr float WIN_Hf = static_cast<float>(WIN_H);
constexpr int FRAMERATE = 120;

constexpr int INFINITE_LIFETIME = -1;
constexpr int FIRE_LIFETIME = 25;

constexpr sf::Color CLR_BG = {16, 18, 28, 255};
constexpr sf::Color CLR_PANEL = {28, 28, 28, 255};
constexpr sf::Color CLR_GROUND = {77, 53, 51, 255};
constexpr sf::Color CLR_GROUND2 = {89, 61, 56, 255};
constexpr sf::Color CLR_GROUND3 = {65, 45, 42, 255};
constexpr sf::Color CLR_SAND = {194, 178, 128, 255};
constexpr sf::Color CLR_SAND2 = {210, 195, 140, 255};
constexpr sf::Color CLR_SAND3 = {170, 160, 110, 255};
constexpr sf::Color CLR_WATER = {83, 132, 165, 255};
constexpr sf::Color CLR_POWDER = {72, 71, 83, 255};
constexpr sf::Color CLR_POWDER2 = {80, 78, 90, 255};
constexpr sf::Color CLR_POWDER3 = {60, 60, 70, 255};
constexpr sf::Color CLR_FIRE = {255, 51, 0, 255};
constexpr sf::Color CLR_FIRE2 = {255, 80, 30, 255};
constexpr sf::Color CLR_FIRE3 = {200, 40, 0, 255};
constexpr sf::Color CLR_FIRE_DARK = {130, 30, 0, 255};
constexpr sf::Color CLR_FIRE_DARK2 = {100, 20, 0, 255};
constexpr sf::Color CLR_FIRE_DARK3 = {80, 10, 5, 255};
constexpr sf::Color CLR_SMOKE = {120, 120, 130, 160};
constexpr sf::Color CLR_SMOKE2 = {150, 150, 160, 130};
constexpr sf::Color CLR_SMOKE3 = {180, 180, 190, 100};

struct ParticleInfo {
    std::array<sf::Color, 3> clr;
    std::string_view name;
    int lifetime;
};

constexpr int N_PARTICLE_TYPES = 6;
constexpr std::array<ParticleInfo, N_PARTICLE_TYPES> PARTICLES_DATA = {{
    {{CLR_GROUND, CLR_GROUND2, CLR_GROUND3}, "Ground", INFINITE_LIFETIME},
    {{CLR_SAND, CLR_SAND2, CLR_SAND3}, "Sand", INFINITE_LIFETIME},
    {{CLR_WATER, CLR_WATER, CLR_WATER}, "Water", INFINITE_LIFETIME},
    {{CLR_POWDER, CLR_POWDER2, CLR_POWDER3}, "Powder", INFINITE_LIFETIME},
    {{CLR_FIRE, CLR_FIRE2, CLR_FIRE3}, "Fire", FIRE_LIFETIME},
    {{CLR_SMOKE, CLR_SMOKE2, CLR_SMOKE3}, "Smoke", INFINITE_LIFETIME}
}};

constexpr int FONT_SZ = 20;

constexpr float TOP_BAR_TEXT_HORIZONTAL_OFFSET = 20.f;
constexpr float BTN_VERTICAL_OFFSET = 60.f;

constexpr sf::Vector2f POS_TEXT_FPS = {10.f, 20.f};
constexpr sf::Vector2f POS_UI_PANEL = {1130.f, 0.f};
constexpr sf::Vector2f POS_GRID = {5.f, POS_TEXT_FPS.y + FONT_SZ/2};
constexpr sf::Vector2i POS_GRIDi = {static_cast<int>(POS_GRID.x), static_cast<int>(POS_GRID.y)};

constexpr int PARTICLE_SZ = 4;
constexpr sf::Vector2f MIN_CURSOR_SZ = {2.f, 2.f};
constexpr sf::Vector2f MAX_CURSOR_SZ = {48.f, 48.f};
constexpr sf::Vector2f TOP_BTN_SZ = {25.f, 25.f};
constexpr sf::Vector2i TOP_BTN_SZi = {25, 25};
constexpr sf::Vector2f GRID_SZ = {(POS_UI_PANEL.x - 10.f), (WIN_Hf - POS_TEXT_FPS.y - FONT_SZ/2 - 10.f)};
constexpr sf::Vector2u GRID_SZu = {static_cast<unsigned int>(GRID_SZ.x), static_cast<unsigned int>(GRID_SZ.y)};
constexpr sf::Vector2f BTN_SZ = {100.f, 40.f};
constexpr sf::Vector2f OUTLINE_BTN_SZ = BTN_SZ + sf::Vector2f(10.f, 10.f);

constexpr int32_t REFRESH_RATE_FPS_MS = 1000;

#endif
