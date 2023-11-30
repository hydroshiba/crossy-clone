#ifndef OBJECT_HPP_
#define OBJECT_HPP_

#include "typedef.hpp"
#include "texture.hpp"
#include "engine.hpp"

class Object {
private:
	const Texture& texture;
	
protected:
	int x, y;

public:
	Object(int x, int y, const Texture& texture);
	~Object() = default;

	int getX();
	int getY();

	int getWidth();
	int getHeight();

	virtual void render(Engine* engine);
};

#endif