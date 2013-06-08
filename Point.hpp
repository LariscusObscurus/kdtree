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
	
	bool lessX(const T& value)
	{
		return (x < value);
	}
	
	bool lessY(const T& value)
	{
		return (y < value);
	}
	
	bool greaterX(const T& value)
	{
		return (x > value);
	}
	
	bool greaterY(const T& value)
	{
		return (y > value);
	}
	
	bool operator<(const Point& p)
	{
		return (lessX(p.x) && lessY(p.y));
	}
	
	bool operator<=(const Point& p)
	{
		return ((lessX(p.x) || x == p.x) && (lessY(p.y) || y == p.y));
	}
	
	bool operator>(const Point& p)
	{
		return (greaterX(p.x) && greaterY(p.y));
	}
	
	bool operator>=(const Point& p)
	{
		return ((greaterX(p.x) || x == p.x) && (greaterY(p.y) || y == p.y));
	}
	
	static bool less(const Point& rhs, const Point& lhs)
	{
		return (rhs < lhs);
	}
	
	static bool greater(const Point& rhs, const Point& lhs)
	{
		return (rhs > lhs);
	}
};

#endif