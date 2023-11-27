#include "keyboard.hpp"

Keyboard::Keyboard() {
	toggle = new bool[256];
	last = VK_NONAME;
}

Keyboard::~Keyboard() {
	delete[] toggle;
}

void Keyboard::refresh() {
	for(int i = 0; i < 256; i++)
		if(pressed(i)) last = i;
}

bool Keyboard::pressed(byte key) {
	bool down = GetAsyncKeyState(key);
	bool pressed = !down && toggle[key];

	toggle[key] = down;
	return pressed;
}

byte Keyboard::key() {
	byte key = last;
	last = VK_NONAME;
	return key;
}