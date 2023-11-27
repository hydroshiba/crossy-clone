#ifndef KEYBOARD_HPP_
#define KEYBOARD_HPP_

#include <map>
#include <windows.h>

#include "typedef.hpp"

class Keyboard {
private:
	bool* toggle;
	byte last;
    
	bool pressed(byte key);

public:
	Keyboard();
	~Keyboard();

	void refresh();
	byte key();
};

#endif