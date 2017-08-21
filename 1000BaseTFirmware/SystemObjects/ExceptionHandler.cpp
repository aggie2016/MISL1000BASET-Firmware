#include "ExceptionHandler.h"



ExceptionHandler::ExceptionHandler()
{
}


ExceptionHandler::~ExceptionHandler()
{
}

void ExceptionHandler::ThrowException(std::string message) {
	printf("Exception Thrown: %s", message.c_str());
	while (true)
	{

	}
}