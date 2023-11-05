#include <windows.h>
#include <filesystem>
#include <mmsystem.h>

#include "game.hpp"
#include "scene.hpp"
#include "player.hpp"

void test() {
	std::string path = "C:\\Users\\hydroshiba\\Desktop\\Code\\crossy-clone\\asset\\sound\\background.wav";
	std::string temp = "type waveaudio alias background";

	//mciSendString(("open " + path + " " + temp).c_str(), NULL, 0, NULL);
	//mciSendString("play background repeat", NULL, 0, NULL);
	//mciSendString("close background", NULL, 0, NULL);

	sndPlaySound(path.c_str(), SND_FILENAME | SND_ASYNC | SND_LOOP);
}

int main() {
	std::cout << std::filesystem::current_path();

	//std::thread t(test);
	test();

	Game game;
	game.run();

	//t.join();
}