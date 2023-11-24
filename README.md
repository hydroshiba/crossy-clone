# CSC100003 Project: Crossy Road clone

**Group 01 - 22CLC06**  
**Members:**

- Phan Hải Minh - 22127273
- Bùi Tá Phát - 22127320
- Đặng Thanh Tú - 22127432
- Nguyễn Ngọc Anh Tú - 22127433

This is the project from our **Object-Oriented Programming** course, which is a clone of the popular game Crossy Road with similar gameplay and graphics. Programmed in C++, the project adopted the Object-Oriented paradigm (which we studied throughout the course) with the use of the Windows API for graphics and audio playback.

The game is about us, the character, who wants to cross roads and rivers to get to the grocery store but was intervened by the neverending traffic. We, the player, have to get our character safely to the other side, and we gain points as we progress through the roads. The player can use buttons from their keyboard for controlling the character, and the game is over once the character got hit by an obstacle or the time limit is up.

## Requirements

- A Windows environment, preferably Windows 10 and above.
- For building project from source:
  - [C++17 compliant](https://en.cppreference.com/w/cpp/compiler_support/17) compiler
  - [CMake 3.20](https://cmake.org/download/) or newer

## Building this project

This section is for building the project from source files. A compiled executable of the project can be found in the [Releases](#releases) section alternatively.

### Manually

- Clone this repository.
- Navigate to this directory in a console.
- `cmake -S . -B ./build`
- `cmake --build ./build`
  - An optional `-j` flag can be added after this command to enable the use of multithreaded compiling with arbitrary amount of cores, e.g. `cmake --build ./build -j 4`
- The executable `crossy` will appear, run it by typing `./crossy` (or `crossy`) in your console.

### IDEs with CMake integration

These IDEs can automatically configure the project from CMake files, simply clone this repository and open the project folder in your IDE.

### Other IDEs

- Clone this repository.
- Navigate to this directory in a console.
- Run `cmake -S . -B ./build -G "IDE name"`
  - Type `cmake -G` for a list of supported IDEs.
  - Replace `IDE name` with the name of your IDE as shown in the list, e.g. `cmake -S . -B ./build -G "Visual Studio 16 2019"` for Visual Studio 2019.
- A project file for your IDE will be generated in the `build` folder, launch the project and build from there.

## Releases

To be added

## Acknowledgement

We would like to thank our lecturer, Mr. Truong Toan Thinh, for providing us the opportunity, as well as the guidance and valuable materials we needed to complete this project.
