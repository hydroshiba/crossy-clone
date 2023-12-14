#ifndef LINCAL_HPP_
#define LINCAL_HPP_

#include <initializer_list>
#include <utility>

struct Vec2 {
    float x, y;
    Vec2 operator+(const Vec2& other) const;
    Vec2& operator=(std::initializer_list<float> list);
};

class Mat2 {
private:
    float data[4];

public:
    Mat2();
    Mat2(std::initializer_list<float> list);

    float& operator[](int index);
    const float& operator[](int index) const;

    Mat2 operator~() const;
    Mat2 operator*(const Mat2& other) const;
    Vec2 operator*(const Vec2& other) const;
};

#endif