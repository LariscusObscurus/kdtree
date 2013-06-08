#ifndef CONVERSION_HPP
#define CONVERSION_HPP

#include <sstream>
#include <string>

template <typename T>
std::string numberToString (T Number)
{
	std::stringstream ss;
	ss << Number;
	return ss.str();
}

template <typename T>
T stringToNumber (const std::string &Text)
{
	std::stringstream ss(Text);
	T result;
	return ss >> result ? result : 0;
} 
#endif