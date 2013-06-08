#include "Conversion.hpp"
#include <cstdlib>
#include <cstdint>
#include <fstream>
#include <iostream>

int main(int argc, char** argv)
{
	using namespace std;
	typedef int32_t s32;
	
	s32 count = 0;
	string str = "";
	
	if (argc != 2) {
		cerr << "usage: " << argv[0] << " filename" << endl;
		return EXIT_FAILURE;
	}
	
	ifstream inputFile(argv[1]);
	
	if (!inputFile.good()) {
		cerr << "Couldn't open input file: " << argv[1] << endl;
		return EXIT_FAILURE;
	}
	
	inputFile >> str;
	try {
		count = stringToNumber<s32>(str);
	} catch (...) {
		cerr << "File formating:\n\n";
		cerr << "<PointCount>\n";
		cerr << "<X_1>,<Y_1>\n";
		cerr << "<X_2>,<Y_2>\n";
		cerr << "...\n";
		cerr << "<X_n>,<Y_n>" << endl;
		return EXIT_FAILURE;
	}
	
	while (inputFile >> str) {
		try {
			string lhs = str.substr(0, str.find(','));
			string rhs = str.substr(str.find(',')+1);
			cout << str << '\n';
			cout << stringToNumber<int64_t>(lhs) << '\n';
			cout << stringToNumber<int64_t>(rhs) << '\n' << endl;
		} catch (...) {
		}
	}
	return EXIT_SUCCESS;
}
