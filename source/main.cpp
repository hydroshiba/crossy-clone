#include <windows.h>
#include <filesystem>

#include "resource.h"
#include "game.hpp"
#include "scene.hpp"
#include "player.hpp"
#include "sound.hpp"

#include <mmsystem.h>

int main() {
	// Assuming you have a resource ID for your WAV file in the resource file.
    int wavResourceID = background;

    // Find the module handle of your application.
    HMODULE hModule = GetModuleHandle(NULL);

    // Load the WAV resource.
    HRSRC hResInfo = FindResource(hModule, MAKEINTRESOURCE(wavResourceID), RT_RCDATA);
    HGLOBAL hResData = LoadResource(hModule, hResInfo);
    LPVOID lpRes = LockResource(hResData);
    DWORD dataSize = SizeofResource(hModule, hResInfo);

	// Play the WAV resource.
	sndPlaySoundW((LPCWSTR)lpRes, SND_MEMORY | SND_ASYNC | SND_LOOP);

    // Release resources.
    FreeResource(hResData);
	
	Game game;
	game.run();

    return 0;
}