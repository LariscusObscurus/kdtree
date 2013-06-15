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
	std::list<Node_t *> mNodeList;
public:
	Kdtree ()
	{
	}
	~Kdtree ()
	{
		for(auto& it : mNodeList) {
			delete it;
		}
	}

	int buildTree(std::list<T> points)
	{
		int pos;
		sortX(points);
		root = new Node_t;
		mNodeList.push_back(root);
		median(points, root->key, pos);
		split(0, root, pos, points);
		return 0;
	}

private:
	void median(std::list<T> sortedPoints, T& medPoint, int& pos)
	{
		
		int medianPoint = sortedPoints.size() / 2;
		pos = medianPoint;
		auto it = sortedPoints.begin();
		std::advance(it, medianPoint);
		*it = medPoint;
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
	int split(int depth ,Node_t *parentNode,int medPos,std::list<T> points)
	{
		std::list<T> left;
		std::list<T> right;
		T medRight; 
		T medLeft; 
		int posLeft;
		int posRight;

		if(points.size() == 0) {
			return 0;
		} else if(points.size() == 1) {
			parentNode->key = points.front();
			return 0;
		}

		if(depth % 2 == 0) {
		/* X */
			auto it = points.begin();
			std::advance(it, medPos);
			points.splice(it, left);
			right = points;

			sortY(right);
			sortY(left);

		} else {
		/* Y */
			auto it = points.begin();
			std::advance(it, medPos);
			points.splice(it, right);
			left = points;

			sortX(right);
			sortX(left);
		}

		parentNode->right = new Node_t;
		mNodeList.push_back(parentNode->right);
		median(left, medRight, posRight);
		parentNode->key = medRight;

		parentNode->left = new Node_t;
		mNodeList.push_back(parentNode->left);
		median(left, medLeft, posLeft);
		parentNode->key = medLeft;


		split(depth + 1, parentNode->right, posRight, right);
		split(depth + 1, parentNode->left, posLeft, left);
	}
};

#endif 
