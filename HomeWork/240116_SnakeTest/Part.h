#pragma once
#include <ConsoleEngine/ConsoleObject.h>

class Part : public ConsoleObject
{
public:

protected:
	Part* Front = nullptr;
	Part* Back = nullptr;

};

