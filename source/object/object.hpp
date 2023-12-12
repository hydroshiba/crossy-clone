#ifndef OBJECT_HPP_
#define OBJECT_HPP_

#include "typedef.hpp"
#include "texture.hpp"
#include "engine.hpp"
#include "lincal.hpp"

class Object {
protected:
	Texture const * const texture;
	int x, y;

public:
	Object(Texture const * const texture);
	Object(Texture const * const texture, int x, int y);

	Vec2 position() const;
	Vec2 size() const;

	virtual void shift(int dx, int dy);
	virtual void render(Engine* engine);
};

#endif