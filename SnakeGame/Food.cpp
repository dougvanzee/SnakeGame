#include "Food.h"

Food::Food()
{
	gen_food();
}

void Food::gen_food()
{
	pos.X = rand() % (WIDTH - 2) + 2;
	pos.Y = rand() % (HEIGHT - 2) + 2;
}

COORD Food::get_pos() { return pos; }
