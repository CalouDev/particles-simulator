# Particles Simulator 1.0.0

A simple 2D particles simulator made with SFML 3.0 using C++

## Screenshots

![screenshot](./assets/screenshot.png)


## Features

- Ground, sand, water, powder, fire, smoke
- Run/stop system
- Delete all

## Run

You can clone the repo and compile by yourself, or run ./bin/app exectuable file compiled with
```
g++ src/*.cpp -o bin/app -I include -L lib -lmingw32 -lsfml-graphics -lsfml-window -lsfml-system -O2 -Wall
```


## Controls

Leftclick : add particles  
Rightclick : remove particles
Wheel : update the cursor size
