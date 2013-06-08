#ifndef KD_TREE
#define KD_TREE


template <typename T>
class KdTree
{
	struct Node {
		T key;
		Node * left;
		Node * right;
	};
public:
	KdTree ();
	virtual ~KdTree ();

private:

};

#endif 
