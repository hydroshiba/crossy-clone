#ifndef OBJECT_HPP_
#define OBJECT_HPP_

#include "typedef.hpp"
#include "texture.hpp"
#include "engine.hpp"

class Object {
private:
	int x, y;
	Texture texture;

public:
	Object(int x, int y, const Texture& texture);
	~Object();

	virtual void render(Engine* engine);
};

#endif