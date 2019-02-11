#include "Point2D.h"

Point2D::Point2D()
{
	x = 0.0f;
	y = 0.0f;
}

Point2D::Point2D(float x, float y)
{
	this->x = x;
	this->y = y;
}

Point2D::~Point2D()
{ }

Point2D & Point2D::operator+=(const Point2D & p)
{
	this->x += p.x;
	this->y += p.y;
	return *this;
}

Point2D & Point2D::operator-=(const Point2D & p)
{
	this->x -= p.x;
	this->y -= p.y;
	return *this;
}

Point2D & Point2D::operator*=(const Point2D & p)
{
	this->x *= p.x;
	this->y *= p.y;
	return *this;
}

Point2D & Point2D::operator/=(const Point2D & p)
{
	this->x /= p.x;
	this->y /= p.y;
	return *this;
}

Point2D & Point2D::operator++()
{
	this->x++;
	this->y++;
	return *this;
}

Point2D & Point2D::operator--()
{
	this->x--;
	this->y--;
	return *this;
}

int Point2D::getSignX() const
{
	return (x < 0) ? -1 : +1;
}

int Point2D::getSignY() const
{
	return (y < 0) ? -1 : +1;
}

std::ostream & operator<<(std::ostream & os, const Point2D p)
{
	os << "(" << p.x << "," << p.y << ")" << std::endl;
	return os;
}
