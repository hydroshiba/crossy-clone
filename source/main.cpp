#include <windows.h>
#include <filesystem>
#include <mmsystem.h>

#include "game.hpp"
#include "scene.hpp"
#include "player.hpp"

void test() {
	std::string path = std::filesystem::current_path().string() + "\\asset\\sound\\background.wav";
	std::string temp = "type waveaudio alias background";

	//mciSendString(("open " + path + " " + temp).c_str(), NULL, 0, NULL);
	//mciSendString("play background repeat", NULL, 0, NULL);
	//mciSendString("close background", NULL, 0, NULL);

	sndPlaySound(path.c_str(), SND_FILENAME | SND_ASYNC | SND_LOOP);
}

int main() {
	widestring path = std::filesystem::current_path();
	std::cout << std::string(path.begin(), path.end()) << std::endl;

	//std::thread t(test);
	//test();

	//Sound sound((path + L"\\asset\\sound\\background.wav").c_str(), "background");
	//Sound sound2((path + L"\\asset\\sound\\sfx\\long-honk.wav").c_str(), "background2");

	//sound2.play();

	Game game;
	game.run();
}