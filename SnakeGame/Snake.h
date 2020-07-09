#pragma once

#include "SnakeGlobal.h"
#include <Windows.h>
#include "SnakeBodyPart.h"
#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

class Snake
{

private:
	COORD pos;
	int len = 2;
	int vel;
	char direction;
	vector<COORD> bparts;
	
	bool bGrow = false;

	void move_body();

public:
	Snake(COORD pos, int vel);
	void change_dir(char dir);
	void move_snake();
	COORD get_pos();
	
	bool eaten(COORD food_pos);
	void grow();
	bool collided();

	bool bIsBodyPartAtPos(COORD pos);
	void initialize_bodyparts();
};

