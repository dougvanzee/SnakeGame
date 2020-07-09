#include "Snake.h"

Snake::Snake(COORD pos, int vel)
{
	this->pos = pos;
	this->vel = vel;
	len = 2;
	direction = 'r';

	initialize_bodyparts();
}

void Snake::change_dir(char dir) { direction = dir; }

void Snake::move_snake()
{
	move_body();

	switch (direction)
	{
		case 'u': pos.Y--;
		break;

		case 'd': pos.Y++;
		break;

		case 'l': pos.X--;
		break;

		case 'r': pos.X++;
		break;
	}
}

void Snake::move_body()
{
	COORD new_bpart_pos;

	if (bGrow)
	{
		new_bpart_pos = bparts.back();
	}

	for (size_t i = bparts.size(); i--;)
	{
		if (i == 0)
		{
			bparts.at(i) = { pos.X, pos.Y };
		}
		else
		{
			bparts.at(i) = bparts.at(i - 1);
		}
	}

	if (bGrow)
	{
		bparts.push_back(new_bpart_pos);
		bGrow = false;
	}
	
}

COORD Snake::get_pos() { return pos; }

bool Snake::eaten(COORD food_pos)
{
	if (food_pos.X == pos.X && food_pos.Y == pos.Y) return true;
	else return false;
}

void Snake::grow()
{
	len++;
	bGrow = true;
}

bool Snake::collided()
{
	if (pos.X < 0 || pos.X >= WIDTH - 1 || pos.Y < 1 || pos.Y >= HEIGHT - 1) return true;
	else if (bIsBodyPartAtPos({ get_pos().X, get_pos().Y })) return true;
	return false;
}

bool Snake::bIsBodyPartAtPos(COORD pos)
{
	for (COORD part : bparts)
	{
		if (part.X == pos.X && part.Y == pos.Y) return true;
	}

	return false;
}

void Snake::initialize_bodyparts()
{
	for (int i = 0; i < len; i++)
	{
		bparts.push_back({ pos.X - (SHORT)(i + 1), pos.Y });
	}
}
