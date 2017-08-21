#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H		  

#include <type_traits>

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
};

#endif // !HELPERFUNCTIONS_H