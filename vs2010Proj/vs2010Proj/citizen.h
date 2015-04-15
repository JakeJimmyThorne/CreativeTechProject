#ifndef _CITIZEN_H_
#define _CITIZEN_H_

#include <iostream>

class Citizen
{
public:
	enum Gender { MALE, FEMALE };

public:

	Citizen() 
	{
		happiness = 50;
		age = 0;

		m_gender = rand() % 100 > 50 ? FEMALE : MALE;

		deathMod = 0;
		m_pregnantCD = 0;
		birthDeath = false;
	}
	Citizen(int newAge)
	{
		happiness = 50;
		age = newAge;

		m_gender = rand() % 100 > 50 ? FEMALE : MALE;

		deathMod = 0;
		m_pregnantCD = 0;
		birthDeath = false;
	}

	~Citizen() {}

	void AgeOneWeek();
	bool Alive();

	bool IsFemale() { return m_gender == FEMALE ? true : false; }

	bool IsPregnant() { return m_pregnantCD == 0 ? false : true; }
	bool SetPregnant()
	{
		if (m_pregnantCD == 0 && age > 16 && age < 50)
		{
			m_pregnantCD = 36; //weeks
			return true;
		}
		else return false;
	}

	bool birthDeath;

private:

	Gender m_gender;
	float RandomRange(float min, float max);

	float happiness;
	float age;

	float deathMod;
	int m_pregnantCD;

	
};

#endif