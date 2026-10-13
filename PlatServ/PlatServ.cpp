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

	case fields::cloud1:
		set_dims(200.0f, 79.0f);
		break;

	case fields::cloud2:
		set_dims(180.0f, 81.0f);
		break;

	case fields::cloud3:
		set_dims(120.0f, 63.0f);
		break;
	}

	max_frame_delay = frame_delay;
}

bool indll::FIELD::move(float gear, dirs to_where)
{
	float my_speed = linear + gear / 10.0f;

	if (type == fields::cloud1)my_speed -= 0.7f;
	if (type == fields::cloud2)my_speed -= 0.6f;
	if (type == fields::cloud3)my_speed -= 0.5f;

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

fields indll::FIELD::get_type() const
{
	return type;
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
	float my_speed{ gravity + 2.0f + gear / 10.0f };

	if (state == states::fall)return;

	if (state != states::jump)
	{
		if (dir == dirs::left)set_path(center.x - _width, start.y - max_jump);
		else set_path(end.x, start.y - max_jump);

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
	float my_speed{ gravity + 2.0f + gear / 10.0f };
	
	if (state != states::fall)return;

	if (end.y < ground - 42.0f)
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
		end.y = ground - 42.0f;
		start.y = end.y - _height;
		set_edges();
		state = states::stop;
	}
}

/////////////////////////////////////////////

// CLASS EVILS ******************************

indll::EVILS::EVILS(evils _what, float _sx, float _sy) :PROTON(_sx, _sy)
{
	type = _what;

	switch (type)
	{
	case evils::angry:
		set_dims(49.0f, 85.0f);
		_speed -= 0.4f;
		max_frames = 3;
		frame_delay = 20;
		attack_delay = 90;
		lifes = 80;
		damage = 10;
		break;

	case evils::caveman:
		set_dims(96.0f, 92.0f);
		_speed -= 0.3f;
		max_frames = 7;
		frame_delay = 10;
		attack_delay = 110;
		lifes = 100;
		damage = 15;
		break;

	case evils::zombie:
		set_dims(66.0f, 90.0f);
		_speed -= 0.2f;
		max_frames = 52;
		frame_delay = 1;
		attack_delay = 80;
		lifes = 70;
		damage = 8;
		break;
	}

	max_attack_delay = attack_delay;
	max_frame_delay = frame_delay;
}

evils indll::EVILS::get_type()const
{
	return type;
}

void indll::EVILS::set_path(float _ex, float _ey)
{
	move_sx = start.x;
	move_ex = _ex;
	move_sy = start.y;
	move_ey = _ey;

	float vec_delta_x{ move_ex - move_sx };
	float vec_delta_y{ move_ey - move_sy };
	float vec_delta_lenght{ (float)(sqrt(pow(vec_delta_x,2) + pow(vec_delta_y,2))) };

	delta_x = vec_delta_x / vec_delta_lenght;
	delta_y = vec_delta_y / vec_delta_lenght;
}

float indll::EVILS::get_target_x()const
{
	return move_ex;
}
float indll::EVILS::get_target_y()const
{
	return move_ey;
}

int indll::EVILS::get_frame()
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
int indll::EVILS::attack()
{
	--attack_delay;

	if (attack_delay <= 0)
	{
		attack_delay = max_attack_delay;

		return damage;
	}

	return 0;
}

void indll::EVILS::move(float gear)
{
	float my_speed{ _speed + gear / 10.0f };

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

	if (start.x < 0)dir = dirs::right;
	if (end.x > scr_width)dir = dirs::left;
}
void indll::EVILS::jump(float gear)
{
	float my_speed{ gravity + 2.0f + gear / 10.0f };

	if (state == states::fall)return;

	if (state != states::jump)
	{
		if (dir == dirs::left)set_path(center.x - _width, start.y - max_jump);
		else set_path(end.x, start.y - max_jump);

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
void indll::EVILS::fall(float gear, BAG<D2D1_RECT_F>& fields_bag)
{
	float my_speed{ gravity + 2.0f + gear / 10.0f };

	if (state != states::fall)return;

	if (end.y < ground - 42.0f)
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
		end.y = ground - 42.0f;
		start.y = end.y - _height;
		set_edges();
		state = states::stop;
	}
}

void indll::EVILS::Release()
{
	delete this;
}

indll::EVILS* indll::EVILS::create(evils what, float sx, float sy)
{
	return new EVILS(what, sx, sy);
}

/////////////////////////////////////////////

// FUNCTIONS ********************************

bool indll::Intersect(D2D1_RECT_F first, D2D1_RECT_F second)
{
	return(!(first.left >= second.right || first.right <= second.left || first.top >= second.bottom || first.bottom <= second.top));
}

float indll::Distance(D2D1_POINT_2F first, D2D1_POINT_2F second)
{
	float a{ (float)(pow(second.x - first.x, 2)) };
	float b{ (float)(pow(second.y - first.y, 2)) };

	return (float)(sqrt(a + b));
}

void indll::Sort(BAG<D2D1_POINT_2F>& bag, D2D1_POINT_2F ref)
{
	if (bag.size() < 2)return;

	bool ok = false;

	while (!ok)
	{
		ok = true;

		for (size_t i = 0; i < bag.size() - 1; ++i)
		{
			if (Distance(bag[i], ref) > Distance(bag[i + 1], ref))
			{
				D2D1_POINT_2F temp = bag[i];

				bag[i] = bag[i + 1];
				bag[i + 1] = temp;

				ok = false;
			}
		}
	}
}

void indll::EvilNextMove(EVILS& unit, BAG<D2D1_POINT_2F>& bAssetsCenters, BAG<D2D1_RECT_F>& bGrounds, D2D1_POINT_2F hero_center,
	float level_gear)
{
	if (unit.state == states::attack)
	{
		if (Distance(unit.center, hero_center) > unit.get_width() / 2.0f
			&& Distance(unit.center, hero_center) > unit.get_height() / 2.0f)
		{
			unit.state = states::walk;
			if (hero_center.x > unit.center.x)unit.dir = dirs::right;
			else unit.dir = dirs::left;
			return;
		}
	}
	else if (unit.state == states::walk)
	{
		if (Distance(unit.center, hero_center) <= unit.get_width() / 2.0f
			&& Distance(unit.center, hero_center) <= unit.get_height() / 2.0f)
		{
			unit.state = states::attack;
			return;
		}
		else if (!bGrounds.empty() && unit.end.y >= ground)
		{
			for (size_t i = 0; i < bGrounds.size(); ++i)
			{
				if (Intersect(bGrounds[i], unit.rect))
				{
					unit.state = states::jump;
					break;
				}
			}
		}
		else
		{
			Sort(bAssetsCenters, unit.center);

			if (Distance(unit.center, bAssetsCenters.front()) <= unit.get_width() / 2.0f
				&& Distance(unit.center, bAssetsCenters.front()) <= unit.get_height() / 2.0f)
			{
				unit.set_path(bAssetsCenters.front().x, bAssetsCenters.front().y);
				return;
			}
		}
	}
	else if (unit.state == states::jump)unit.jump(level_gear);
	else if (unit.state == states::fall)unit.fall(level_gear, bGrounds);
}