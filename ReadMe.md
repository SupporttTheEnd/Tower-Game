Here's a revised version of the README for your SDL2 game project:

---

# SDL2 Game Project

## Introduction

This project is a 2D game developed using SDL2. The game features player movement, collision detection with a castle, and a HUD with heart icons. The player can move in four directions and attack, while the game handles sprite animations and collision logic.

## Project Structure

```
project/
├── .vscode/
├── assets/
│   ├── background.png
│   ├── player_sheet.png
│   ├── heart.png
│   └── Castle_Blue.png
├── inc/
│   ├── Game.h
│   └── TextureManager.h
├── lib/
├── Game.cpp
├── TextureManager.cpp
├── SDL2.dll
├── SDL2_image.dll
├── main.cpp
└── game.exe
```

## How to Run the Project

1. **Ensure Dependencies are in Place**:
   - Verify that `SDL2.dll` and `SDL2_image.dll` are in the project directory.
   - Make sure the executable `game.exe` is present.

2. **Run the Game**:
   - Double-click `game.exe` to start the game.

3. **Gameplay Controls**:
   - **Movement**: Use the arrow keys (`Up`, `Down`, `Left`, `Right`) to move the player.
   - **Attack**: Press the `Space` key to attack in the current direction.
   - **Exit**: Close the game window or use the appropriate command to quit.

## Files and Directories

- **`.vscode/`**: Contains VS Code configuration files.
- **`assets/`**: Holds image files used in the game, including player sprites, hearts, and background images.
- **`inc/`**: Header files for the game.
- **`lib/`**: Placeholder for library files if any are used.
- **`Game.cpp`**: Source code for the game logic.
- **`TextureManager.cpp`**: Source code for texture management.
- **`SDL2.dll`**: SDL2 dynamic link library required to run the game.
- **`SDL2_image.dll`**: SDL2_image dynamic link library required for image handling.
- **`main.cpp`**: Entry point of the game.
- **`game.exe`**: Executable file for running the game.

## Building the Project

To build the project, follow these steps:

1. **Install SDL2 and SDL2_image**:
   - Ensure SDL2 and SDL2_image libraries are installed on your system.

2. **Compile the Code**:
   - Use a compatible compiler to compile the `Game.cpp`, `TextureManager.cpp`, and `main.cpp` files.
   - Link against SDL2 and SDL2_image libraries.

3. **Run the Game**:
   - After building, execute the generated `.exe` file to run the game.

## Troubleshooting

- **If the game does not start**: Ensure all required DLLs are present in the project directory.
- **If you encounter graphical issues**: Verify that the image files are correctly placed in the `assets/` directory and are accessible.

## License

This project is licensed under the [MIT License](LICENSE).

## Contact

For questions or feedback, please contact [Your Name](mailto:your.email@example.com).

---

Feel free to customize the contact information and license details as needed!
