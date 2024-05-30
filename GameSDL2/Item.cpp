#include "Item.h"


Item::Item()
{
	x_val = 0;
	y_val = 0;
	is_move = false;
	is_out = false;

}

Item::~Item()
{

}

void Item::update()
{
	x_val -= 10;
	if (x_val < 0 || y_val< 0 || y_val > SCREEN_HEIGHT - rect_.h)
	{
		is_out = true;
	}

}