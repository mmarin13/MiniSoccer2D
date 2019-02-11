#pragma once
#include <iostream>

class Point2D
{
public:
	float x;
	float y;
	
	Point2D();
	Point2D(float x, float y);
	~Point2D();

	Point2D(const Point2D&) = default;
	Point2D(Point2D&&) = default;
	Point2D& operator=(const Point2D&) = default;
	Point2D& operator=(Point2D&&) = default;

	Point2D& operator+=(const Point2D& p);
	Point2D& operator-=(const Point2D& p);
	Point2D& operator*=(const Point2D& p);
	Point2D& operator/=(const Point2D& p);
	Point2D& operator++();
	Point2D& operator--();
	friend std::ostream& operator<<(std::ostream& os, const Point2D p);

	int getSignX() const;
	int getSignY() const;
};

