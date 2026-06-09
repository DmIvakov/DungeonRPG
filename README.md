# DungeonRPG

A terminal-based 2D rogue-like RPG game written in C++. 

> ⚠️ **Project Status:** Early development (Pre-Alpha / MVP). The codebase currently contains temporary solutions, temporary workarounds, and basic mechanics. It is subject to heavy changes and refactoring.

## Current Features
* Procedural or basic grid map rendering.
* Player movement (`P`) and enemy placement (`M`).
* Core stats tracking (Floor, Level, Exp, HP, Damage).
* Automatic terminal screen clearing (via ANSI escape codes).
* Immersive looping background music (Windows only).
* Cross-platform code structure (core game logic runs on both Windows and Linux).

## Project Structure
* `/src` — Source files (`.cpp`).
* `/include` — Header files (`.h`).
* `/assets` — Game assets (audio, track file `DungeonRPG.wav`).
* `/build` — Local compilation directory (will be ignored by Git soon, managed automatically).

## Getting Started

### Requirements
* A C++ compiler supporting C++11 or higher (e.g., `g++` via MinGW/Strawberry Perl on Windows, or native `g++` on Linux).
* OS: Windows (for full audio support via `winmm`) or Linux (headless/silent build).

### Building and Running in VS Code (Windows)
1. Clone the repository and open the root folder in VS Code.
2. Make sure you have the official Microsoft **C/C++** extension installed.
3. Press **`Ctrl + Shift + B`** to trigger the automated task. This will compile the binaries into the `/build` folder and automatically copy all media assets.
4. Go to the **Run and Debug** tab (`Ctrl + Shift + D`) and select **Run DungeonRPG**.
5. Press **`Ctrl + F5`** to launch the game inside an external console window with working audio.

### Building manually via Terminal (Linux)
The core loop is cross-platform, but audio features are skipped on Linux platforms. Run the following commands from the root directory:
```bash
mkdir -p build
g++ src/*.cpp -Iinclude -o build/DungeonRPG
cp -r assets build/
./build/DungeonRPG
```

## Upcoming Roadmap
* Advanced procedural level generation.
* Combat system and turn-based AI behavior.
* Inventory system and interactive item drops.
* Cross-platform audio engine support.
* And much more!
