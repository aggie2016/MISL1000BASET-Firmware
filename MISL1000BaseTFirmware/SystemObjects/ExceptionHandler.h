//#include <iostream>
#include <stdint.h>
#include <string>
#include <stdio.h>

#ifndef EXCEPTIONHANDLER_H
#define EXCEPTIONHANDLER_H



class ExceptionHandler
{
public:
	ExceptionHandler();
	virtual ~ExceptionHandler();

	static void ThrowException(std::string);
};


#endif // !EXCEPTIONHANDLER_H



