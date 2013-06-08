#ifndef KD_TREE
#define KD_TREE

#include <list>
#include "Point.hpp"

template <typename T>
class Kdtree
{
	struct Node {
		T key;
		Node * left;
		Node * right;
	};
	std::list<T> points;
public:
	Kdtree (std::list<T>& inPoints)
	{
		points = inPoints;
	}
	~Kdtree ()
	{
	}

	int buildTree() 
	{
		points.sort();
		
	}

private:
	int medianX()
	{

	}
	int medianY();
	int split(int value, std::list<T> sortedPoints);
};

#endif 
