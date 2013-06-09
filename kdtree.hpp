#ifndef KD_TREE
#define KD_TREE

#include <list>
#include "Point.hpp"
#include <iostream>

template <typename T>
class Kdtree
{
	typedef struct Node {
		int key;
		/* leaves haben key -1 */
		T leave;
		Node * left;
		Node * right;
	}Node_t;
	Node_t *root;
	std::list<Node_t *> mNodeList;
public:
	Kdtree ()
	{
	}
	~Kdtree ()
	{
		for(auto& it : mNodeList) {
			std::cout << "Nodekey: key = " << it->key << std::endl;
			delete it;

		}
	}

	int buildTree(std::list<T> points)
	{
		split(0, root, points);
		return 0;
	}

private:
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
	int medianX(std::list<T> points, std::list<T>& leftPoints, std::list<T>& rightPoints)
	{
		sortX(points);
		int splitValue = 0;
		int medianPoint = (int) points.size() / 2;
		auto it = points.begin();

		if(points.size() % 2 == 0){
		/* gerade Anzahl an Punkten -> durchschnitt als splitValue */
			/*auto it2 = points.begin();
			std::advance(it2, (medianPoint-1));
		TODO: Fehler hier 
			splitValue = (int)(it->x + it2->x) / 2; */
			splitValue = (int)it->x;
		} else {
			std::advance(it, medianPoint);
			splitValue = (int)it->x;
		}
		rightPoints.splice(rightPoints.begin(), points, it, points.end());
		leftPoints = points;
		return splitValue;
	}

	int medianY(std::list<T> points, std::list<T>& leftPoints, std::list<T>& rightPoints)
	{
		sortY(points);
		int splitValue = 0;
		int medianPoint = (int) points.size() / 2;
		auto it = points.begin();
		std::advance(it, medianPoint);

		if(points.size() % 2 == 0){
		/* gerade Anzahl an Punkten -> durchschnitt als splitValue */
			/*auto it2 = points.begin();
			std::advance(it2, (medianPoint-1));
			splitValue = (int)(it->y + it2->y) / 2; */
			splitValue = (int)it->y;
		} else {
			splitValue = (int)it->y;
		}
		rightPoints.splice(rightPoints.begin(), points, it, points.end());
		leftPoints = points;
		return splitValue;
	}

	int split(int depth ,Node_t *parentNode ,std::list<T> points)
	{
		std::list<T> left;
		std::list<T> right;
		int key = 0;

		if(points.size() == 0) {
			parentNode = nullptr;
			return 0;
		}

		parentNode = new Node_t;
		mNodeList.push_back(parentNode);

		if(points.size() == 1) {
			parentNode->key = -1;
			parentNode->leave = points.front();
			parentNode->right = nullptr;
			parentNode->left = nullptr;
			return 0;
		}

		if((depth % 2 == 0) && (depth !=0)) {
		/* X */
			key = medianX(points, left, right);
		} else {
		/* Y */
			key = medianY(points, left, right);
		}
		parentNode->key = key;

		split(depth + 1, parentNode->right, right);
		split(depth + 1, parentNode->left, left);
		return 0;
	}
};

#endif 
