#pragma once
#include <iostream>
class MenuFontCanNotBeLoadedException : public std::exception
{
public:
	MenuFontCanNotBeLoadedException(const char* msg) : std::exception(msg) { }
};

class MenuFieldsCanNotBeEmpty : public std::exception
{
public:
	MenuFieldsCanNotBeEmpty(const char* msg) : std::exception(msg) { }
};

class MenuBackgroundCanNotBeEmpty : public std::exception
{
public:
	MenuBackgroundCanNotBeEmpty(const char* msg) : std::exception(msg) { }
};
