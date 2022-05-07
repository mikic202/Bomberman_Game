#ifndef Item_Exceptions_H
#define Item_Exceptions_H
#include <stdexcept>


class FliePathException : public std::invalid_argument
{
public:
	FliePathException() :
		std::invalid_argument("Path to the texture file is incorect") {};
};


class DelayException : public std::invalid_argument
{
public:
	DelayException() :
		std::invalid_argument("Given delay exceeds max delay") {};
};


#endif // !Item_Exceptions_H

