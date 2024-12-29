# Pong Clone written in C using SDL2

## Main Clone Features
- No game AI
- Left paddle is controlled by w/s keys, right paddle by using up/down arrows


## TODO list
- Improved ball physics that takes into account paddle and ball collision angle
- Sizes of paddles and ball that look more like original
- Reworked speed of the game
- AI opponent

## Build
The game uses SDL2 and SDL TTF libraries, build with GCC using
```
gcc -o pong *.c -lSDL2_ttf `sdl2-config --cflags --libs`
```
You can download font used [here](https://font.download/font/nasa21), it is not
included in this repo

