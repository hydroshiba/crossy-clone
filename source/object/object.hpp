#ifndef OBJECT_HPP_
#define OBJECT_HPP_

#include "typedef.hpp"
#include "texture.hpp"
#include "engine.hpp"

class Object {
protected:
	const Texture& texture;
	int x, y;

public:
	Object(const Texture& texture);
	Object(const Texture& texture, int x, int y);

	int getX();
	int getY();

	int getWidth();
	int getHeight();

	void setOffset(int x, int y);
	virtual void render(Engine* engine);
};

#endif