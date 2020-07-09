#pragma once

#include "SnakeGlobal.h"
#include <Windows.h>
#include <cstdlib>

#define WIDTH 50
#define HEIGHT 25

class Food
{
private:
	COORD pos;

public:
	Food();
	void gen_food();
	COORD get_pos();


};

