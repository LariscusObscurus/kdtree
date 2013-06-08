#ifndef POINT_HPP
#define POINT_HPP
	
template <typename T>
struct Point
{
	T x;
	T y;
	
	Point(T x = (T)0, T y = (T)0) : x(x), y(y)
	{
	}
	
	Point(const Point& point) : x(point.x), y(point.y)
	{
	}
	
	bool operator==(const Point& p)
	{
		return (x == p.x && y == p.y);
	}
	
	bool operator!=(const Point& p)
	{
		return (x != p.x || y != p.y);
	}
	
	void operator!()
	{
		x = (-1) * x;
		y = (-1) * y;
	}
	
	Point& operator=(const Point& p)
	{
		x = p.x;
		y = p.y;
		return *this;
	}
	
	Point operator+(const Point& p)
	{
		return Point(x + p.x, y + p.y);
	}
	
	Point operator-(const Point& p)
	{
		return Point(x - p.x, y - p.y);
	}
	
	Point operator*(const Point& p)
	{
		return Point(x * p.x, y * p.y);
	}
	
	Point operator/(const Point& p)
	{
		return Point(x / p.x, y / p.y);
	}
	
	Point& operator+=(const Point& p)
	{
		x += p.x;
		y += p.y;
		return *this;
	}
	
	Point& operator-=(const Point& p)
	{
		x -= p.x;
		y -= p.y;
		return *this;
	}
	
	Point& operator*=(const Point& p)
	{
		x /= p.x;
		y /= p.y;
		return *this;
	}
	
	Point& operator/=(const Point& p)
	{
		x *= p.x;
		y *= p.y;
		return *this;
	}
};

#endif