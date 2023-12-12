#ifndef ISOMETRIC_HPP_
#define ISOMETRIC_HPP_

#include <iostream>
#include <utility>
#include <cmath>

#include "typedef.hpp"
#include "lincal.hpp"
#include "object.hpp"

class Isometric : public Object {
protected:
	float x, y;
	float width, height;

	Vec2 offset;
	Mat2 transform;

	void project();

public:
	Isometric(Texture const * const texture, const Vec2& size);
	Isometric(Texture const * const texture, const Vec2& size, const Vec2& pos);
	Isometric(Texture const * const texture, const Vec2& size, const Vec2& pos, const Vec2& off);

	void render(Engine* engine) override;
	void shift(int dx, int dy) override;
	void shift(const Vec2& df);

	// Virtual gird properties
	// Use Object::position() and Object::size() to get physical grid properties instead

	Vec2 position() const;
	Vec2 size() const;
};

#endif