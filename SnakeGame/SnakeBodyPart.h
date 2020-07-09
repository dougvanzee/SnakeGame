#pragma once

#include "SnakeGlobal.h"
#include <Windows.h>

class SnakeBodyPart
{
private:
	COORD pos;

public:
	COORD get_pos();
	void set_pos(COORD pos);
	
};

