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

	return distr(*twister);
}

//////////////////////////////////////////////