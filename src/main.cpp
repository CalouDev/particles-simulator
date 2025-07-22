#include "../include/app.hpp"

/* TODO
TO FIX:

- removeParticle() not working in particle_manager.cpp

- Sand particle behavior on ground

TO ADD: 

- Make a button to delete all on the top bar :

for (size_t i = 0; i < GRID_SZ.y; ++i) {
    for (size_t j = 0; j < GRID_SZ.x; ++j) {
        if (EmptyType != grid[i][j]) {
            removeParticle(sf::Vector2i(j, i));
        }
    }
}

- Custom cursor

- load once the font for all component (instead of load it twice in app.cpp and particle_manager.cpp)

*/

int main(void) {
    App app;

    app.mainLoop();

    return 0;
}
