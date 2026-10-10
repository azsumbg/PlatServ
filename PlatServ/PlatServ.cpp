#include "pch.h"
#include "PlatServ.h"

// EXCEPTION CLASS ***************************

indll::EXCEPTION::EXCEPTION(int what_happened) :what{ what_happened } {};

const wchar_t* indll::EXCEPTION::eGet() const
{
	switch (what)
	{
	case BAD_PTR:
		return L"Bad pointer passed to a BAG method !";

	case BAD_INDEX:
		return L"Bad index passed to a BAG method !";

	case BAD_PARAM:
		return L"Bad parameter passed to a BAG method !";

	case BAD_ITERATOR:
		return L"Iterator out of bounds passed to a BAG method !";
	}

	return L"Unknown error occurred in a BAG instance !";
}

//////////////////////////////////////////////

// CLASS RANDIT ******************************

indll::RANDIT::RANDIT()
{
	std::random_device rd{};
	std::seed_seq sq{ rd(),rd(), rd(), rd(), rd(), rd(), rd(), rd() };

	twister = new std::mt19937{ sq };
}

indll::RANDIT::~RANDIT()
{
	if (twister)delete twister;
}

int indll::RANDIT::operator()(int min, int max)
{
	if (max <= min)return -1;

	std::uniform_int_distribution distr(min, max);

	return distr(*twister);
}

float indll::RANDIT::operator()(float min, float max)
{
	if (max <= min)return -1;

	std::uniform_real_distribution<double> distr(min, max);

	return (float)(distr(*twister));
}

//////////////////////////////////////////////


// CLASS PROTON *****************************

indll::PROTON::PROTON()
{
	_width = 1.0f;
	_height = 1.0f;

	x_rad = _width / 2.0f;
	y_rad = _height / 2.0f;

	center.x = start.x + x_rad;
	center.y = start.y + y_rad;

	end.x = start.x + _width;
	end.y = start.y + _height;
}
indll::PROTON::PROTON(float sx, float sy)
{
	start.x = sx;
	start.y = sy;

	_width = 1.0f;
	_height = 1.0f;

	x_rad = _width / 2.0f;
	y_rad = _height / 2.0f;

	center.x = start.x + x_rad;
	center.y = start.y + y_rad;

	end.x = start.x + _width;
	end.y = start.y + _height;
}
indll::PROTON::PROTON(D2D1_POINT_2F start_point)
{
	start.x = start_point.x;
	start.y = start_point.y;

	_width = 1.0f;
	_height = 1.0f;

	x_rad = _width / 2.0f;
	y_rad = _height / 2.0f;

	center.x = start.x + x_rad;
	center.y = start.y + y_rad;

	end.x = start.x + _width;
	end.y = start.y + _height;
}
indll::PROTON::PROTON(float sx, float sy, float width, float height)
{
	start.x = sx;
	start.y = sy;

	_width = width;
	_height = height;

	x_rad = _width / 2.0f;
	y_rad = _height / 2.0f;

	center.x = start.x + x_rad;
	center.y = start.y + y_rad;

	end.x = start.x + _width;
	end.y = start.y + _height;
}
indll::PROTON::PROTON(D2D1_POINT_2F start_point, float width, float height)
{
	start.x = start_point.x;
	start.y = start_point.y;

	_width = width;
	_height = height;

	x_rad = _width / 2.0f;
	y_rad = _height / 2.0f;

	center.x = start.x + x_rad;
	center.y = start.y + y_rad;

	end.x = start.x + _width;
	end.y = start.y + _height;
}

float indll::PROTON::get_width() const
{
	return _width;
}
float indll::PROTON::get_height() const
{
	return _height;
}

void indll::PROTON::set_edges()
{
	center.x = start.x + x_rad;
	center.y = start.y + y_rad;

	end.x = start.x + _width;
	end.y = start.y + _height;
}

void indll::PROTON::set_width(float new_width)
{
	_width = new_width;
	
	x_rad = _width / 2.0f;
	
	center.x = start.x + x_rad;
	
	end.x = start.x + _width;
}
void indll::PROTON::set_height(float new_height)
{
	_height = new_height;

	y_rad = _height / 2.0f;

	center.y = start.y + y_rad;

	end.y = start.y + _height;
}
void indll::PROTON::set_dims(float new_width, float new_height)
{
	_width = new_width;
	_height = new_height;

	x_rad = _width / 2.0f;
	y_rad = _height / 2.0f;

	center.x = start.x + x_rad;
	center.y = start.y + y_rad;

	end.x = start.x + _width;
	end.y = start.y + _height;
}

/////////////////////////////////////////////