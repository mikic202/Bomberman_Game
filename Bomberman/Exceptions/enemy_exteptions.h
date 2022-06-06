#pragma once
#include <iostream>
class TextureCanNotBeLoadedException : public std::exception
{
public:
	TextureCanNotBeLoadedException(const char* msg) : std::exception(msg) { }
};

