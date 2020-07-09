#include "SnakeBodyPart.h"

COORD SnakeBodyPart::get_pos() { return pos; }

void SnakeBodyPart::set_pos(COORD pos)
{
	this->pos = pos;
}
