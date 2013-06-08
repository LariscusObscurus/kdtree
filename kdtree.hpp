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
	std::list<
public:
	kdtree ();
	virtual ~kdtree ();

private:
	int medianX;
	int medianY;
};

#endif 
