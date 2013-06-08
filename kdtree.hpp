#ifndef KD_TREE
#define KD_TREE


template <typename T>
class Kdtree
{
	struct Node {
		T key;
		Node * left;
		Node * right;
	};
public:
	Kdtree ();
	virtual ~Kdtree ();

private:
	int medianX;
	int medianY;
};

#endif 
