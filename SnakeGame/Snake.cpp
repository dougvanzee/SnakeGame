#include "Snake.h"

// Constructor
Snake::Snake(COORD pos, int vel)
{
	this->pos = pos;
	this->vel = vel;
	len = 2;
	direction = 'r';

	initialize_bodyparts();
}

// Changes direction that the snake is moving
void Snake::change_dir(char dir) { direction = dir; }

// Moves body and head of the snake
void Snake::move_snake()
{
	// Move the body first so the head doesn't detect any incorrect collisions with body
	move_body();

	// Move the head
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

// Moves body
void Snake::move_body()
{
	COORD new_bpart_pos;

	// If growing, record last body part location
	if (bGrow)
	{
		new_bpart_pos = bparts.back();
	}

	// Move body parts
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

	// Add the new body part if growing
	if (bGrow)
	{
		bparts.push_back(new_bpart_pos);
		bGrow = false;
	}
	
}

// Gets snake position
COORD Snake::get_pos() { return pos; }

// If the snake head is at the same position as food, return true
bool Snake::eaten(COORD food_pos)
{
	if (food_pos.X == pos.X && food_pos.Y == pos.Y) return true;
	else return false;
}

// Grow snake on next move
void Snake::grow()
{
	len++;
	bGrow = true;
}

// Detect whether snake has collided with a wall or it's body
bool Snake::collided()
{
	if (pos.X < 0 || pos.X >= WIDTH - 1 || pos.Y < 1 || pos.Y >= HEIGHT - 1) return true;
	else if (bIsBodyPartAtPos({ get_pos().X, get_pos().Y })) return true;
	return false;
}

// Is position overlapping body part, not head
bool Snake::bIsBodyPartAtPos(COORD pos)
{
	for (COORD part : bparts)
	{
		if (part.X == pos.X && part.Y == pos.Y) return true;
	}

	return false;
}

// Setup body parts at beginning
void Snake::initialize_bodyparts()
{
	for (int i = 0; i < len; i++)
	{
		bparts.push_back({ pos.X - (SHORT)(i + 1), pos.Y });
	}
}
