#pragma once

#include <iostream>
#include <string>

class Point {
public:
	float X, Y;
public:

	Point(float X=0, float Y=0) :X(X), Y(Y) {};

	inline Point operator+(const Point& p) const{
		return Point(X + p.X, Y + p.Y);
	}

	inline friend Point operator+=(Point& p1, const Point& p2) {
		p1.X += p2.X;
		p1.Y += p2.Y;
		return p1;
	}

	inline Point operator*(const float scalar) const{
		return Point(X * scalar, Y * scalar);
	}

	inline Point operator-(const Point& p) const{
		return Point(X - p.X, Y - p.Y);
	}

	inline friend Point operator-=(Point& p1, const Point& p2) {
		p1.X -= p2.X;
		p1.Y -= p2.Y;
		return p1;
	}

	void Log(std::string msg = "") {
		std::cout << msg << " (X Y) = (" << X << " " << Y << ")" << std::endl;
	}

};