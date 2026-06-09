# DungeonRPG

A 2D rogue-like RPG game written in C++ using CMake.

> ⚠️ **Project Status:** Early development (Pre-Alpha / MVP). The codebase currently contains temporary solutions, temporary workarounds, and basic mechanics. It is subject to heavy changes, refactoring, and an upcoming migration to SFML for graphical rendering.

## Current Features
* Procedural or basic grid map rendering.
* Player movement (`P`) and enemy placement (`M`).
* Core stats tracking (Floor, Level, Exp, HP, Damage).
* Automatic terminal screen clearing (via ANSI escape codes).
* Immersive looping background music (Windows only).
* Modern build system via **CMake** (handles compilation and assets automatically).
* Cross-platform code structure (core game logic runs on both Windows and Linux).

## Project Structure
* `/src` — Source files (`.cpp`).
* `/include` — Header files (`.h`).
* `/assets` — Game assets (audio, track file `DungeonRPG.wav`).
* `CMakeLists.txt` — Main CMake configuration file.

## Getting Started

### Requirements
* A C++ compiler supporting C++17 or higher (e.g., `g++` via MinGW/Strawberry Perl on Windows, or native `g++` on Linux).
* **CMake** (version 3.15 or higher).
* OS: Windows (for full audio support via `winmm`) or Linux (headless/silent build).

### Building and Running in VS Code (All Platforms)
1. Clone the repository and open the root folder in VS Code.
2. Install the official extensions: **C/C++** and **CMake Tools** from Microsoft.
3. Select your compiler kit (e.g., `GCC MinGW` or Clang/MSVC) when prompted by CMake Tools.
4. Press **`F7`** to build the project. CMake will automatically compile the code and copy the `/assets` folder to the build output directory.
5. Press **`Shift + F5`** (or click the **Play** button on the bottom status bar) to launch the game.

### Building manually via Terminal
You can build the project from the command line using standard CMake commands:
```bash
# 1. Configure the project and generate build files
cmake -B build

# 2. Compile the project
cmake --build build

# 3. Run the game
# On Windows:
./build/DungeonRPG.exe
# On Linux:
./build/DungeonRPG
```

### Building a Production Release (Packaging)
If you want to package the game into a clean, ready-to-share ZIP archive without any source code or compiler clutter, run these commands:

1. Configure the project in Release mode:
   ```bash
   cmake -B build -DCMAKE_BUILD_TYPE=Release
   ```
2. Build the optimized binaries:
   ```bash
   cmake --build build --config Release
   ```
3. Generate the distribution package via CPack:
   ```bash
   cd build && cpack
   ```

After CPack finishes, a brand new `/releases` folder will automatically appear in the project root containing a clean **`DungeonRPG-1.0.0-win64.zip`** archive, fully ignored by Git and ready to be sent to players.

## Upcoming Roadmap
* 🚀 **SFML Graphics Integration:** Migration from console ASCII output to a fully graphical 2D window, keeping the console for debugging/logging.
* Advanced procedural level generation.
* Combat system and turn-based AI behavior.
* Inventory system and interactive item drops.
* Cross-platform audio engine support.
