#include "SnakeBodyPart.h"

// Get body part position
COORD SnakeBodyPart::get_pos() { return pos; }

// Sets new position
void SnakeBodyPart::set_pos(COORD pos)
{
	this->pos = pos;
}
