#ifndef BUTTON_HPP_
#define BUTTON_HPP_

#include "texture.hpp"
#include "object.hpp"

class Button : public Object {
private:
	bool selected = false;
	const Texture& pressed;

public:
	Button(const Texture& idle, const Texture& pressed, int x, int y);

	void press();
	void release();
	
	void render(Engine* engine);
};

#endif