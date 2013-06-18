#include "Conversion.hpp"
#include "kdtree.hpp"
#include "Point.hpp"
#include <cstdlib>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <list>

typedef int32_t s32;
typedef uint32_t u32;

void printErrorFileFormat();

int main(int argc, char** argv)
{
	using namespace std;
	
	Point<u32> point;
	s32 count = 0;
	s32 fileCount = 0;
	string str = "";
	std::list<Point<u32>> points(0);
	
	if (argc != 4) {
		cerr << "usage: " << argv[0] << " <filename> <x>,<y> <search_count>" << endl;
		return EXIT_FAILURE;
	}
	
	try {
		string str = argv[2];
		string lhs = str.substr(0, str.find(','));
		string rhs = str.substr(str.find(',')+1);
		u32 x = stringToNumber<u32>(lhs);
		u32 y = stringToNumber<u32>(rhs);
		point = Point<u32>(x,y);
		count = stringToNumber<s32>(argv[3]);
	} catch (...) {
		cerr << "error converting number." << endl;
		return EXIT_FAILURE;
	}
	ifstream inputFile(argv[1]);
	
	if (!inputFile.good()) {
		cerr << "Couldn't open input file: " << argv[1] << endl;
		return EXIT_FAILURE;
	}
	
	inputFile >> str;
	try {
		fileCount = stringToNumber<s32>(str);
	} catch (...) {
		cerr << "error converting number." << endl;
		return EXIT_FAILURE;
	}
	
	if (count > fileCount) {
		cerr << "One does simply not count more than the kdtree got on points." << '\n';
		cerr << "Point count in kdtree: " << fileCount << endl;
		return EXIT_FAILURE;
	}
	
	while (inputFile >> str) {
		try {
			string lhs = str.substr(0, str.find(','));
			string rhs = str.substr(str.find(',')+1);
			u32 x = stringToNumber<u32>(lhs);
			u32 y = stringToNumber<u32>(rhs);
			Point<u32> p(x,y);
			points.push_back(p);
			
			cout << "x: " << x << '\n';
			cout << "y: " << y << '\n' << endl;
		} catch (...) {
			cerr << "Couldn't convert number.\n" << endl;
			printErrorFileFormat();
			return EXIT_FAILURE;
		}
	}
	
	Kdtree<Point<u32>> kdtree;
	kdtree.buildTree(points);
	kdtree.nearestNeighbor(point, (int)count);
	return EXIT_SUCCESS;
}

void printErrorFileFormat()
{
	using namespace std;
	cerr << "File formating:\n";
	cerr << "<PointCount>\n";
	cerr << "<X_1>,<Y_1>\n";
	cerr << "<X_2>,<Y_2>\n";
	cerr << "...\n";
	cerr << "<X_n>,<Y_n>" << endl;
}
