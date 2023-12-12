#include "lincal.hpp"

Vec2 Vec2::operator+(const Vec2& other) const {
	return {x + other.x, y + other.y};
}

Vec2& Vec2::operator=(std::initializer_list<float> list) {
	this->x = *list.begin();
	this->y = *(list.begin() + 1);
	return *this;
}

Mat2::Mat2() : data{0, 0, 0, 0} {}

Mat2::Mat2(std::initializer_list<float> list) {
	int i = 0;
	for (auto& item : list) {
		data[i++] = item;
	}
}

float& Mat2::operator[](int index) {
	return data[index];
}

const float& Mat2::operator[](int index) const {
	return data[index];
}

Mat2 Mat2::operator~() const {
	const float invdet = 1 / (data[0] * data[3] - data[1] * data[2]);
	return {data[0] * invdet, -data[1] * invdet, -data[2] * invdet, data[3] * invdet};
}

Mat2 Mat2::operator*(const Mat2& other) const {
	return {
		data[0] * other[0] + data[1] * other[2],
		data[0] * other[1] + data[1] * other[3],
		data[2] * other[0] + data[3] * other[2],
		data[2] * other[1] + data[3] * other[3]
	};
}

Vec2 Mat2::operator*(const Vec2& other) const {
	return {
		data[0] * other.x + data[1] * other.y,
		data[2] * other.x + data[3] * other.y
	};
}