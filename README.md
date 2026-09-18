# Pacman Console Game (C)

A console based Pacman clone built in C. Final project for BNCC's C Programming course, completed with a High Distinction predicate.

Demo video: https://www.youtube.com/watch?v=HX-yae14GAk

## Features

- ASCII maze rendered directly in the console from a 2D character grid
- Player controlled Pacman movement
- A ghost enemy with randomized movement
- Dot eating scoring, with a win condition once every dot is cleared
- Persistent high score saved to and loaded from `highscore.txt`

## How to build and run

Only the C standard library is used (`stdio.h`, `stdlib.h`, `time.h`), no external dependencies.

```
g++ Pacman.cpp -o Pacman
./Pacman
```

Plain `gcc` also compiles this file, since the code only uses C syntax despite the `.cpp` extension.

**Windows only as written**: the game clears the console with `system("cls")`. On Linux or macOS, change that line to `system("clear")` so the maze redraws correctly each frame.

## Controls

`w` `a` `s` `d` to move up, left, down, and right.
