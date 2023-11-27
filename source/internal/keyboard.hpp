#ifndef KEYBOARD_HPP_
#define KEYBOARD_HPP_

#include <map>
#include <windows.h>

#include "typedef.hpp"

class Keyboard {
private:
	bool* toggle;
	Key last;
    
	bool pressed(Key key);

public:
	Keyboard();
	~Keyboard();

	void refresh();
	Key key();
};

#endif