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

	rect.left = start.x;
	rect.right = end.x;
	rect.top = start.y;
	rect.bottom = end.y;
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

	rect.left = start.x;
	rect.right = end.x;
	rect.top = start.y;
	rect.bottom = end.y;
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

	rect.left = start.x;
	rect.right = end.x;
	rect.top = start.y;
	rect.bottom = end.y;
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

	rect.left = start.x;
	rect.right = end.x;
	rect.top = start.y;
	rect.bottom = end.y;
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

	rect.left = start.x;
	rect.right = end.x;
	rect.top = start.y;
	rect.bottom = end.y;
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

	rect.left = start.x;
	rect.right = end.x;
	rect.top = start.y;
	rect.bottom = end.y;
}

void indll::PROTON::set_width(float new_width)
{
	_width = new_width;
	
	x_rad = _width / 2.0f;
	
	center.x = start.x + x_rad;
	
	end.x = start.x + _width;

	rect.left = start.x;
	rect.right = end.x;
	rect.top = start.y;
	rect.bottom = end.y;
}
void indll::PROTON::set_height(float new_height)
{
	_height = new_height;

	y_rad = _height / 2.0f;

	center.y = start.y + y_rad;

	end.y = start.y + _height;

	rect.left = start.x;
	rect.right = end.x;
	rect.top = start.y;
	rect.bottom = end.y;
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

	rect.left = start.x;
	rect.right = end.x;
	rect.top = start.y;
	rect.bottom = end.y;
}

/////////////////////////////////////////////

// CLASS FIELD ******************************

indll::FIELD::FIELD(fields _what_type, float _sx, float _sy) :PROTON(_sx, _sy)
{
	type = _what_type;

	switch (type)
	{
	case fields::background1:
		set_dims(1000.0f, 700.0f);
		max_frames = 5;
		frame_delay = 13;
		break;

	case fields::background2:
		set_dims(1000.0f, 700.0f);
		max_frames = 2;
		frame_delay = 30;
		break;

	case fields::intro:
		set_dims(1000.0f, 800.0f);
		max_frames = 17;
		frame_delay = 4;
		break;

	case fields::pause:
		set_dims(1000.0f, 800.0f);
		max_frames = 16;
		frame_delay = 4;
		break;

	case fields::castle:
		set_dims(200.0f, 310.0f);
		break;

	case fields::ground:
		set_dims(1000.0f, 42.0f);
		break;

	case fields::platform1:
		set_dims(100.0f, 17.0f);
		break;

	case fields::platform2:
		set_dims(120.0f, 18.0f);
		break;

	case fields::platform3:
		set_dims(90.0f, 18.0f);
		break;
	}

	max_frame_delay = frame_delay;
}

bool indll::FIELD::move(float gear, dirs to_where)
{
	float my_speed = linear + gear / 10.0f;

	switch (to_where)
	{
	case dirs::left:
		start.x -= my_speed;
		set_edges();
		if (end.x <= -scr_width)return false;
		break;

	case dirs::right:
		start.x += my_speed;
		set_edges();
		if (start.x <= 2.0f * scr_width)return false;
		break;
	}

	return true;
}

int indll::FIELD::get_frame()
{
	--frame_delay;

	if (frame_delay <= 0)
	{
		frame_delay = max_frame_delay;

		++frame;

		if (frame > max_frames)frame = 0;
	}

	return frame;
}

void indll::FIELD::Release()
{
	delete this;
}

indll::FIELD* indll::FIELD::create(fields what_type, float sx, float sy)
{
	return new FIELD(what_type, sx, sy);
}

/////////////////////////////////////////////

// CLASS SHOT *******************************

indll::SHOT::SHOT(float _sx, float _sy, float _ex, float _ey) :PROTON(_sx, _sy, 15.0f, 15.0f)
{
	float vector_delta_x{ _ex - _sx };
	float vector_delta_y{ _ey - _sy };

	float vector_delta_lenght = (float)(sqrt((float)(pow(vector_delta_x, 2) + pow(vector_delta_y, 2))));

	delta_x = vector_delta_x / vector_delta_lenght;
	delta_y = vector_delta_y / vector_delta_lenght;

	move_sx = _sx;
	move_sy = _sy;
	move_ex = _ex;
	move_ey = _ey;
}

bool indll::SHOT::move(float gear)
{
	float my_speed = 5.0f + gear / 10.0f;

	start.x += delta_x * my_speed;
	start.y += delta_y * my_speed;

	set_edges();

	if (move_sx > move_ex)
	{
		if (move_sy > move_ey)
		{
			if (center.x <= move_ex && center.y <= move_ey)return false;
		}
		else if (move_sy < move_ey)
		{
			if (center.x <= move_ex && center.y >= move_ey)return false;
		}
		else
		{
			if (center.x <= move_ex)return false;
		}
	}
	else if (move_sx < move_ex)
	{
		if (move_sy > move_ey)
		{
			if (center.x >= move_ex && center.y <= move_ey)return false;
		}
		else if (move_sy < move_ey)
		{
			if (center.x >= move_ex && center.y >= move_ey)return false;
		}
		else
		{
			if (center.x >= move_ex)return false;
		}
	}
	else
	{
		if (move_sy > move_ey)
		{
			if (center.y <= move_ey)return false;
		}
		else if (move_sy < move_ey)
		{
			if (center.y >= move_ey)return false;
		}
		else return false;

	}

	return true;
}

void indll::SHOT::Release()
{
	delete this;
}

indll::SHOT* indll::SHOT::create(float sx, float sy, float ex, float ey)
{
	return new SHOT(sx, sy, ex, ey);
}

/////////////////////////////////////////////

// CLASS HERO *******************************

indll::HERO::HERO(float sx, float sy) :PROTON(sx, sy, 90.0f, 88.0f) {};

void indll::HERO::set_path(float _ex, float _ey)
{
	move_sx = start.x;
	move_ex = _ex;
	move_sy = start.y;
	move_ey = _ey;

	float vector_delta_x{ move_ex - move_sx };
	float vector_delta_y{ move_ey - move_sy };
	float vector_delta_lenght{ (float)(sqrt(pow(vector_delta_x,2) + pow(vector_delta_y,2))) };

	delta_x = vector_delta_x / vector_delta_lenght;
	delta_y = vector_delta_y / vector_delta_lenght;
}

int indll::HERO::get_frame()
{
	--frame_delay;

	if (frame_delay <= 0)
	{
		frame_delay = max_frame_delay;
		++frame;
		if (frame > max_frames)frame = 0;
	}
	
	return frame;
}

void indll::HERO::move(float gear)
{
	float my_speed{ linear * 3.0f + gear / 10.0f };
	
	switch (dir)
	{
	case dirs::right:
		start.x += my_speed;
		break;

	case dirs::left:
		start.x -= my_speed;
		break;
	}

	set_edges();
}

void indll::HERO::jump(float gear)
{
	float my_speed{ gravity + gear / 10.0f };

	if (state == states::fall)return;

	if (state != states::jump)
	{
		if (dir == dirs::left)set_path(center.x - _width, start.y - max_jump);
		else set_path(center.x + _width, start.y - max_jump);

		state = states::jump;
	}
	else
	{
		start.x += delta_x * my_speed;
		start.y += delta_y * my_speed;
		set_edges();

		if (center.y <= move_ey)state = states::fall;
	}
}
void indll::HERO::fall(float gear, BAG<D2D1_RECT_F>& fields_bag)
{
	float my_speed{ gravity + gear / 10.0f };
	
	if (state != states::fall)return;

	if (end.y < ground)
	{
		start.y += my_speed;
		set_edges();

		if (!fields_bag.empty())
		{
			for (int i = 0; i < fields_bag.size(); ++i)
			{
				if (Intersect(rect, fields_bag[i]))
				{
					end.y = fields_bag[i].top;
					start.y = end.y - _height;
					set_edges();
					state = states::stop;
					break;
				}
			}
		}
	}
	else
	{
		end.y = ground;
		start.y = end.y - _height;
		set_edges();
		state = states::stop;
	}
}

/////////////////////////////////////////////

// FUNCTIONS ********************************

bool indll::Intersect(D2D1_RECT_F first, D2D1_RECT_F second)
{
	return(!(first.left >= second.right || first.right <= second.left || first.top >= second.bottom || first.bottom <= second.top));
}