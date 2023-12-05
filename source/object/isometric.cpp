#include "isometric.hpp"

Isometric::Isometric(const Texture& texture, const Vec2& size) : Object(texture), size(size), pos({0, 0}), offset3D({0, 0}) {
	transform = {
		0.5f * size.x, -0.5f * size.x,
		0.5f * size.y, 0.5f * size.y
	};

	project();
}

Isometric::Isometric(const Texture& texture, const Vec2& size, const Vec2& pos) : Object(texture), size(size), pos(pos), offset3D({0, 0}) {
	transform = {
		0.5f * size.x, -0.5f * size.x,
		0.5f * size.y, 0.5f * size.y
	};

	project();
}

Isometric::Isometric(const Texture& texture, const Vec2& size, const Vec2& pos, const Vec2& offset3D) : Object(texture), size(size), pos(pos), offset3D(offset3D) {
	transform = {
		0.5f * size.x, -0.5f * size.x,
		0.5f * size.y, 0.5f * size.y
	};

	project();
}

void Isometric::project() {
	Vec2 res = transform * pos + offset3D;
	x = res.x;
	y = res.y;
}

float Isometric::width() const {
	return size.x;
}

float Isometric::height() const {
	return size.y;
}

float Isometric::X() const {
	return pos.x;
}

float Isometric::Y() const {
	return pos.y;
}