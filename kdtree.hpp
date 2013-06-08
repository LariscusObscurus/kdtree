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
	kdtree ();
	virtual ~kdtree ();

private:

};

#endif 
