#include <windows.h>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <iomanip>

#include "resource.hpp"
#include "game.hpp"
#include "scene.hpp"
#include "player.hpp"
#include "sound.hpp"

#include <mmsystem.h>
#include <vector>

int main() {
    Game game;
    game.run();

    return 0;
}