#ifndef KD_TREE
#define KD_TREE

#include <list>
#include "Point.hpp"

template <typename T>
class Kdtree
{
	typedef struct Node {
		T key;
		Node * left;
		Node * right;
	}Node_t;
	Node_t *root;
public:
	Kdtree ()
	{
	}
	~Kdtree ()
	{
	}

	int buildTree(std::list<T> points)
	{
		points.sort([](const T& lhs, const T& rhs){
			return (lhs.x < rhs.x);
		});
		root = new Node_t;
		root->key = median(points);
		split(0, root, *root->key, points);

		

	}

private:
	T median(std::list<T> sortedPoints)
	{
		
		int medianPoint = sortedPoints.size() / 2;
		return sortedPoints[medianPoint];
	}
	std::list<T> sortX(std::list<T> points)
	{
		points.sort([](const T& lhs, const T& rhs){
			return (lhs.x < rhs.x);
		});
		return points;
	}

	std::list<T> sortY(std::list<T> points)
	{
		points.sort([](const T& lhs, const T& rhs){
			return (lhs.y < rhs.y);
		});
		return points;

	}
	int split(int depth ,Node_t *parentNode,T medPoint ,std::list<T> points)
	{
		std::list<T> left;
		std::list<T> right;

		if(points.size() == 0) {
			return 0;
		} else if(points.size() == 1) {
			parentNode->key = points[0];
			return 0;
		}

		if(depth % 2 == 0) {
		/* X */
			auto it = points.begin();
			std::advance(it, medPoint.x);
			points.splice(it, left);
			right = points;

			sortY(right);
			sortY(left);

		} else {
		/* Y */
			auto it = points.begin();
			std::advance(it, medPoint.y);
			points.splice(it, right);
			left = points;

			sortX(right);
			sortX(left);
		}

		parentNode->right = new Node_t;
		T medRight = median(left);

		parentNode->left = new Node_t;
		T medLeft = median(left);

		split(depth + 1, parentNode->right, medRight, right);
		split(depth + 1, parentNode->left, medLeft, left);
	}
};

#endif 
