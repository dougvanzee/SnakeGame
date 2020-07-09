#include "Food.h"

// Constructor
Food::Food()
{
	gen_food();
}

// Move food to random position
void Food::gen_food()
{
	pos.X = rand() % (WIDTH - 2) + 2;
	pos.Y = rand() % (HEIGHT - 2) + 2;
}

// Get food position
COORD Food::get_pos() { return pos; }
