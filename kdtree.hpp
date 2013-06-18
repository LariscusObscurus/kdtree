#ifndef KD_TREE
#define KD_TREE

#include <list>
#include <cmath>
#include <limits>
#include <iostream>
#include <queue>

enum axis_t {
	X,
	Y
};

template <typename T>
class Kdtree
{
	typedef struct Node {
		int key;
		/* leaves haben key -1 */
		T leave;
		axis_t axis;
		Node * left;
		Node * right;
	}Node_t;

	typedef struct foundCandidate {
		float distance;
		T point;
		int operator < (const foundCandidate& other) const {
			return (distance > other.distance);
		}
	} foundCandidate_t;

	Node_t *root;
	std::list<Node_t *> mNodeList;

	T mQueryPoint;
	int mCount;
	float mDist;
	std::priority_queue<foundCandidate_t> mNearPoints;
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

	void nearestNeighbor(T& point, int count)
	{
		mQueryPoint = point;
		mCount = count;
		mDist = std::numeric_limits<float>::infinity();
		recursiveSearch(root);
		for (int i = 0; i < count; i++) {
			foundCandidate_t tmp = mNearPoints.top();
			std::cout << "Nearest: x " << tmp.point.x << " y " 
			<< tmp.point.y << std::endl;
			mNearPoints.pop();
		}
	}

private:
	float checkDistance(T& pointA, T& pointB) {
		T vectAB = pointB - pointA;
		return (sqrt(pow(vectAB.x, 2) + pow(vectAB.y, 2)));
	}
	void sortX(std::list<T>& points)
	{
		points.sort([](const T& lhs, const T& rhs){
			return (lhs.x < rhs.x);
		});
	}

	void sortY(std::list<T>& points)
	{
		points.sort([](const T& lhs, const T& rhs){
			return (lhs.y < rhs.y);
		});
	}

	int recursiveSearch(Node_t * curNode)
	{
		int pointAxisVal = 0;
		if (curNode == nullptr) {
			return 0;
		}
		if(curNode->key == -1) {
			float dist = checkDistance(mQueryPoint, curNode->leave);
			if(dist < mDist) {
				foundCandidate_t newCandidate = {dist, curNode->leave};
				mNearPoints.push(newCandidate);
				if(mCount == mNearPoints.size()) {
					mDist = dist;
				}
			}
			return 1;
		} 
		
		if(curNode->axis == X) {
			pointAxisVal = mQueryPoint.x;
		} else {
			pointAxisVal = mQueryPoint.y;
		}

		if(pointAxisVal <= curNode->key) {
			if ((pointAxisVal - mDist) <= curNode->key) {
				recursiveSearch(curNode->left);
			} 
			if ((pointAxisVal + mDist) > curNode->key) {
				recursiveSearch(curNode->right);

			}
		} else {
			if ((pointAxisVal + mDist) > curNode->key) {
				recursiveSearch(curNode->right);
			}
			if ((pointAxisVal - mDist) <= curNode->key) {
				recursiveSearch(curNode->left);
			} 
		}
		return 0;
	}

	int medianX(std::list<T> points, std::list<T>& leftPoints, std::list<T>& rightPoints)
	{
		sortX(points);
		int splitValue = 0;
		int medianPoint = (int) points.size() / 2;
		auto it = points.begin();
		std::advance(it, medianPoint);

		if(points.size() % 2 == 0){
		/* gerade Anzahl an Punkten -> durchschnitt als splitValue */
			auto it2 = points.begin();
			std::advance(it2, (medianPoint-1));
			splitValue = (int)(it->x + it2->x) / 2;
			splitValue = (int)it->x;
		} else {
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
			auto it2 = points.begin();
			std::advance(it2, (medianPoint-1));
			splitValue = (int)(it->y + it2->y) / 2;
			splitValue = (int)it->y;
		} else {
			splitValue = (int)it->y;
		}
		rightPoints.splice(rightPoints.begin(), points, it, points.end());
		leftPoints = points;
		return splitValue;
	}

	int split(int depth ,Node_t*& curNode ,std::list<T> points)
	{
		std::list<T> left;
		std::list<T> right;
		int key = 0;

		if(points.size() == 0) {
			curNode = nullptr;
			return 0;
		}

		curNode = new Node_t;
		mNodeList.push_back(curNode);

		if(points.size() == 1) {
			curNode->key = -1;
			curNode->leave = points.front();
			curNode->right = nullptr;
			curNode->left = nullptr;
			return 0;
		}

		if(depth % 2 == 0) {
		/* X */
			key = medianX(points, left, right);
			curNode->axis = X;
		} else {
		/* Y */
			key = medianY(points, left, right);
			curNode->axis = Y;
		}
		curNode->key = key;

		split(depth + 1, curNode->right, right);
		split(depth + 1, curNode->left, left);
		return 0;
	}
};

#endif 
