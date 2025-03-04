/*
 * Copyright (c) 2010-2024 OTClient <https://github.com/edubart/otclient>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#pragma once

#include <cmath>
#include <ostream>

template<class T>
class TSize;

template<class T>
class TPoint
{
public:
    TPoint() : x(0), y(0) {}
    TPoint(T xy) : x(xy), y(xy) {}
    TPoint(T x, T y) : x(x), y(y) {}
    TPoint(const TPoint& other) : x(other.x), y(other.y) {}

    bool isNull() const { return x == 0 && y == 0; }
    TSize<T> toSize() const { return TSize<T>(x, y); }
    TPoint translated(T dx, T dy) const { TPoint point = *this; point.x += dx; point.y += dy; return point; }

    TPoint scale(const float v) {
        if (v != 1.f) {
            float factor = (1.f - (1.f / v));
            x -= x * factor;
            y -= y * factor;
        }
        return *this;
    }

    TPoint operator-() const { return TPoint(-x, -y); }

    TPoint operator+(const TPoint& other) const { return TPoint(x + other.x, y + other.y); }
    TPoint& operator+=(const TPoint& other) { x += other.x; y += other.y; return *this; }
    TPoint operator-(const TPoint& other) const { return TPoint(x - other.x, y - other.y); }
    TPoint& operator-=(const TPoint& other) { x -= other.x; y -= other.y; return *this; }
    TPoint operator*(const TPoint& other) const { return TPoint(x * other.x, y * other.y); }
    TPoint& operator*=(const TPoint& other) { x *= other.x; y *= other.y; return *this; }
    TPoint operator/(const TPoint& other) const { return TPoint(x / other.x, y / other.y); }
    TPoint& operator/=(const TPoint& other) { x /= other.x; y /= other.y; return *this; }

    TPoint operator+(T other) const { return TPoint(x + other, y + other); }
    TPoint& operator+=(T other) { x += other; y += other; return *this; }
    TPoint operator-(T other) const { return TPoint(x - other, y - other); }
    TPoint& operator-=(T other) { x -= other; y -= other; return *this; }
    TPoint operator*(float v) const { return TPoint(x * v, y * v); }
    TPoint& operator*=(float v) { x *= v; y *= v; return *this; }
    TPoint operator/(float v) const { return TPoint(x / v, y / v); }
    TPoint& operator/=(float v) { x /= v; y /= v; return *this; }

    TPoint operator&(int a) { return TPoint(x & a, y & a); }
    TPoint& operator&=(int a) { x &= a; y &= a; return *this; }

    bool operator<=(const TPoint& other) const { return x <= other.x && y <= other.y; }
    bool operator>=(const TPoint& other) const { return x >= other.x && y >= other.y; }
    bool operator<(const TPoint& other) const { return x < other.x && y < other.y; }
    bool operator>(const TPoint& other) const { return x > other.x && y > other.y; }

    TPoint& operator=(const TPoint& other) = default;
    bool operator==(const TPoint& other) const { return other.x == x && other.y == y; }
    bool operator!=(const TPoint& other) const { return other.x != x || other.y != y; }

    float length() const { return sqrt(static_cast<float>(x * x + y * y)); }
    T manhattanLength() const { return std::abs(x) + std::abs(y); }

    float distanceFrom(const TPoint& other) const { return TPoint(x - other.x, y - other.y).length(); }

    std::size_t hash() const { return (7 * 15 + x) * 15 + y; }

    T x, y;
};

using Point = TPoint<int>;
using PointF = TPoint<float>;

template<class T>
std::ostream& operator<<(std::ostream& out, const TPoint<T>& point)
{
    out << point.x << " " << point.y;
    return out;
}

template<class T>
std::istream& operator>>(std::istream& in, TPoint<T>& point)
{
    in >> point.x;
    in >> point.y;
    return in;
}
