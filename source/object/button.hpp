#ifndef BUTTON_HPP_
#define BUTTON_HPP_

#include "texture.hpp"
#include "object.hpp"

class Button : public Object {
private:
	bool selected = false;
	Texture const * const pressed;

public:
	Button(Texture const * const idle, Texture const * const pressed, int x, int y);

	void press();
	void release();
	
	void render(Engine* engine);
};

#endif