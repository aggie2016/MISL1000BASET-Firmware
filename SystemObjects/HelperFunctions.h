#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H		  

#include <algorithm>
#include <iterator>
#include <sstream>
#include <string>
#include <type_traits>
#include <vector>

class HelperFunctions
{
public:
	HelperFunctions();
	~HelperFunctions();
	
	template <typename Enumeration>
	static auto enumToType(Enumeration const value)
	    ->typename std::underlying_type<Enumeration>::type
	{
		return static_cast<typename std::underlying_type<Enumeration>::type>(value);
	}
	
	static std::vector<std::string> splitString(std::string value)
	{
		std::vector<std::string> tokens;
		
		std::istringstream iss(value);
		
		std::copy(std::istream_iterator<std::string>(iss),
			std::istream_iterator<std::string>(),
			back_inserter(tokens));
		
		return tokens;
	}
};

#endif // !HELPERFUNCTIONS_H