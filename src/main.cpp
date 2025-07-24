#include "../include/app.hpp"

/* TODO
TO FIX:

- Sand particle behavior on ground

TO ADD: 

- Custom cursor

- load once the font for all component (instead of load it twice in app.cpp and particle_manager.cpp)

*/

int main(void) {
    App app;

    app.mainLoop();

    return 0;
}
