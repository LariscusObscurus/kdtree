#ifndef KD_TREE
#define KD_TREE

#include <list>
#include <cmath>
#include <limits>
#include <iostream>
#include <queue>
#include <cstdint>

typedef int32_t s32;
typedef uint32_t u32;

enum axis_t {
	X,
	Y
};

template <typename T>
class Kdtree
{
	/**
	 * Blätter haben key -1 
	 * Punkte werden nur in Blättern gespeichert
	 */
	typedef struct Node {
		int key;
		T leave;
		axis_t axis;
		Node * left;
		Node * right;
	}Node_t;

	/**
	 * Alle gefundenen Nachbarn werden in diesem struct gespeichert
	 * "Falsch" definiertert operator wegen der Sortierreihenfolge
	 */
	typedef struct foundCandidate {
		double distance;
		T point;
		int operator < (const foundCandidate& other) const {
			return (distance > other.distance);
		}
	} foundCandidate_t;

	Node_t *root;
	/**
	 * Pointer liste auf alle Nodes um einfach 
	 * Speicher freigeben zu können
	 */
	std::list<Node_t *> mNodeList;

	T mQueryPoint;
	int mCount;
	double mDist;
	std::priority_queue<foundCandidate_t> mNearPoints;
public:
	Kdtree ()
	{
	}
	~Kdtree ()
	{
		for(auto& it : mNodeList) {
			/*std::cout << "Nodekey: key = " << it->key << std::endl;*/
			delete it;
		}
	}
	
	void buildTree(std::list<T> points)
	{
		split(0, root, points);
	}

	void nearestNeighbor(T& point, int count)
	{
		mQueryPoint = point;
		mCount = count;
		mDist = std::numeric_limits<double>::infinity();
		recursiveSearch(root);

		std::cout << "Visited " << mNearPoints.size() 
		<< " Points." << std::endl;

		for (int i = 0; i < count; i++) {
			foundCandidate_t tmp = mNearPoints.top();
			std::cout << "Nearest: x " << tmp.point.x << " y " 
			<< tmp.point.y << std::endl;
			mNearPoints.pop();
		}
	}

private:
	/**
	 * Die Distanz zwischen zwei punkten brechenen.
	 */
	double checkDistance(T& pointA, T& pointB) {
		T vectAB = pointB - pointA;
		if(vectAB.x == 0){
			return pow(vectAB.y,2.0);
		}
		if(vectAB.y == 0) {
			return pow(vectAB.x,2.0);
		}
		return (pow(vectAB.x, 2.0) + pow(vectAB.y, 2.0));
	}

	/**
	 * sortieren der eingegebenen Liste.
	 */
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
		s32 pointAxisVal = 0;
		
		if (curNode == nullptr) {
			return 0;
		}
		if(curNode->key == -1) {
			double dist = checkDistance(mQueryPoint, curNode->leave);
			if(dist < mDist) {
				foundCandidate_t newCandidate = {dist, curNode->leave};
				mNearPoints.push(newCandidate);
				/**
				 * mDist wird erst gesetzt wenn genug Nachbarn
				 * gefunden wurden.
				 */
				if(mCount == (int) mNearPoints.size()) {
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
		/**
		 * Abfrage ob zuerst links oder rechts gesucht wird.
		 */
		if(pointAxisVal <= curNode->key) {
			if (((double)pointAxisVal - mDist) <= (double)curNode->key) {
				recursiveSearch(curNode->left);
			} 
			if (((double)pointAxisVal + mDist) > (double)curNode->key) {
				recursiveSearch(curNode->right);
				
			}
		} else {
			if (((double)pointAxisVal + mDist) > (double)curNode->key) {
				recursiveSearch(curNode->right);
			}
			if (((double)pointAxisVal - mDist) <= (double)curNode->key) {
				recursiveSearch(curNode->left);
			} 
		}
		return 0;
	}
	/**
	 * medianX & medianY berechnen den Median und teilen die input Liste
	 * entsprechend auf zwei Listen auf
	 */
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
		} else {
			splitValue = (int)it->y;
		}
		rightPoints.splice(rightPoints.begin(), points, it, points.end());
		leftPoints = points;
		return splitValue;
	}
	/**
	 *  rekursives aufbauen des kd-Baums
	 */
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
