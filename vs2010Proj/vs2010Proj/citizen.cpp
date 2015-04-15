#include "citizen.h"

void Citizen::AgeOneWeek()
{
	age += 1.0f / 52;

	if (m_pregnantCD > 0)
	{
		m_pregnantCD--;
	}
}

float Citizen::RandomRange(float min, float max)
{
	if (max == 0)
		return 0;

	min *= 1000;
	max *= 1000;

	if (max < 1)
		max = 1;

	float toReturn = (rand() % ((int)max - (int)min)) + min;
	toReturn /= 1000;

	return toReturn;
}

bool Citizen::Alive()
{
	if (birthDeath)
		return false;

	if (age > 30)
	{
		//Increasing 0.5% of dying each consecutive year
		//1 / 52 would give a 1% chance every year
		deathMod += (1.0f / 52) / 2;
	}

	//kill off at 75
	if (age > 75) 
		return false;

	if (RandomRange(0.0f, 100.0f < deathMod))
	{
		return false;
	}

	if (happiness < 0)
	{
		//happiness = 0;
		//deathMod += 100 / 1.0f / 52;
	}

	if (happiness > 100)
	{
		//happiness = 100;
	}

	return true;
}