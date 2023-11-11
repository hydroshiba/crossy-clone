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
	std::cout << std::filesystem::current_path().string() << std::endl;

	//playSoundFromResource();

	std::string path = "asset\\sound\\background.mp3";
	
	mciSendStringA(("open \"" + path + "\" type mpegvideo alias background").c_str(), NULL, 0, NULL);
	mciSendStringA("setaudio background volume to -1", NULL, 0, NULL);
	mciSendStringA("play background", NULL, 0, NULL);

	Game game;
	game.run();

	mciSendStringA("close background", NULL, 0, NULL);

	return 0;
}