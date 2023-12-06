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
	Mat2 transform;
	Vec2 size, pos, offset3D;

	void project();

public:
	Isometric(const Texture& texture, const Vec2& size);
	Isometric(const Texture& texture, const Vec2& size, const Vec2& pos);
	Isometric(const Texture& texture, const Vec2& size, const Vec2& pos, const Vec2& offset3D);

	void render(Engine* engine) override;

	// Logical position

	float width() const;
	float height() const;

	float X() const;
	float Y() const;
};

#endif