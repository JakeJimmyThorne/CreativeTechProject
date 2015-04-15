#include "nation.h"

Nation::Nation()
{
	m_inWar = false;
	m_bonusFood = 0;
}

Nation::~Nation()
{
}

void Nation::Initialise(int simLength)
{
	m_WeekList = new Week[simLength * 52];
}

void Nation::Simulate()
{
#pragma region fortune modifiers

	if(m_Biome.NEAR_RIVER)
		if (rand() % 100 < 25) m_floodMod += DISASTER_FLOOD_CHANCE;

	if(m_Biome.NEAR_MOUNTAINS)
		if (rand() % 100 < 25) m_earthquakeMod += DISASTER_EARTHQUAKE_CHANCE;

	if (rand() % 100 < 25) m_famineMod += DISASTER_FAMINE_CHANCE;
	if (rand() % 100 < 25) m_droughtMod += DISASTER_DROUGHT_CHANCE;

	if (m_Biome.DRY)
		if (rand() % 100 < 25) m_fireMod += DISASTER_FIRE_CHANCE;

	if(m_Biome.NEAR_ROAD && m_population < 500)
		if (rand() % 100 < 25) m_banditsMod += DISASTER_BANDITS_CHANCE;

	if (rand() % 100 < 25) m_weatherMod += DISASTER_WEATHER_CHANCE;

	if (m_Biome.SUNNY)
		m_foodMod += FORTUNE_FOOD_CHANCE;

	if (m_Biome.RAINY)
		m_waterMod += FORTUNE_WATER_CHANCE;

	m_tradeMod += FORTUNE_TRADE_CHANCE;

	m_leaderNewMod += LEADER_NEW_CHANCE;
	m_leaderDeadMod += LEADER_DEAD_CHANCE;
	m_leaderKilledMod += LEADER_KILLED_CHANCE;
	m_leaderAbandonMod += LEADER_ABANDON_CHANCE;
#pragma endregion 

	float fortuneIncrement = 0.4f / 52;
	float leaderIncrement = 0.01f / 52;
	float supplyDecrement = m_population;

	float foodDecrement = 0, waterDecrement = 0, medicineDecrement = 0;

	//slight variance to food and water consumed after each person has half a piece each
	//foodDecrement = m_population * 0.5f + m_morale / 100;
	//waterDecrement = m_population * 0.5f + m_morale / 100;

	if (m_inWar)
	{
		m_medicineSupply -= m_population * 0.05f;
		m_foodSupply -= m_population * 0.05f;
		m_waterSupply -= m_population * 0.05f;
	}

	//adds
	m_foodSupply += m_bonusFood;
	m_waterSupply += m_population * RandomRange(0.05f, 1.10f) +
		(m_population * RandomRange(0.05f, 0.10f));

	if (m_bonusFood > 0)
		m_bonusFood = 0;
	
	
	//should it require more food than it has
	//if (foodDecrement > m_foodSupply)
	//{
	//	int diff = foodDecrement - m_foodSupply;
	//	m_population -= diff / 40;
	//	m_foodSupply = m_population * RandomRange(0.0f, 0.15f);
	//}

	for (int i = 0; i < m_citizenList.size(); i++)
	{
		m_citizenList[i]->AgeOneWeek();

		if (rand() % 100 < 55)
		{
			m_foodSupply += rand() % 4;
			m_waterSupply += rand() % 2;
		}

		if (m_citizenList[i]->Alive())
		{
			//consume food
			if (m_foodSupply > 0)
			{
				//ration food if not enough
				if (m_foodSupply > m_citizenList.size())
				{
					m_foodSupply--;
				}
				else
				{
					m_foodSupply -= 0.5f;
				}
			}
			else
			{
				if (rand() % 100 < 40)
				{
					if (i > 0 && i < m_citizenList.size())
					{
						m_citizenList.erase(m_citizenList.begin() + i--);
						m_Stats.diedOfStarvation++;
						m_foodSupply += rand() % 2 + 1;
						continue;
					}
				}
			}
			
			//consume water
			if (m_waterSupply > 0)
			{
				//ration water if not enough
				if (m_waterSupply > m_citizenList.size())
				{
					m_waterSupply--;
				}
				else
				{
					m_waterSupply -= 0.5f;
				}
			}
			else
			{
				if (rand() % 100 < 40)
				{
					if (i > 0 && i < m_citizenList.size())
					{
						m_citizenList.erase(m_citizenList.begin() + i--);
						m_Stats.diedOfThirst++;
						m_waterSupply += rand() % 2 + 1;
						continue;
					}
				}
			}

			//birth chance
			if (m_citizenList[i]->IsFemale())
			{
				if (!m_citizenList[i]->IsPregnant())
				{
					//chance every year to give birth
					if (RandomRange(0.0f, 100.0f) < (3.0f/*2.8*/ / 52))
					{
						if (m_citizenList[i]->SetPregnant())
						{
							m_citizenList.push_back(new Citizen(0));

							//chance of birthdeath
							if (rand() % 100 < 20)
								m_citizenList[i]->birthDeath = true;
						}
					}
				}
			}
		}
		else
		{
			//erase
			if (i > 0 && i < m_citizenList.size())
			{
				m_citizenList.erase(m_citizenList.begin() + i--);
				m_Stats.diedOfOldAge++;
			}
		}
	}

	m_population = m_citizenList.size();
}

void Nation::Clamp()
{
	//supplies are capped at a base * technology value. more technology allows more storage
	if (m_waterSupply > BASE_SUPPLY_STORAGE * m_technology)
		m_waterSupply = BASE_SUPPLY_STORAGE * m_technology;

	if (m_foodSupply > BASE_SUPPLY_STORAGE * m_technology)
		m_foodSupply = BASE_SUPPLY_STORAGE * m_technology;

	if (m_medicineSupply > BASE_SUPPLY_STORAGE * m_technology)
		m_medicineSupply = BASE_SUPPLY_STORAGE * m_technology;

	if (m_weaponSupply > BASE_SUPPLY_STORAGE * m_technology)
		m_weaponSupply = BASE_SUPPLY_STORAGE * m_technology;

	//capped at 100
	m_technology = m_technology > TECHNOLOGY_CAP ? TECHNOLOGY_CAP : m_technology;

	m_morale	 = m_morale     > MORALE_CAP	 ? MORALE_CAP	  : m_morale;
	m_morale	 = m_morale     < 0				 ? 0			  : m_morale;

	m_waterSupply = m_waterSupply     < 0 ? 0 : m_waterSupply;
	m_foodSupply = m_foodSupply     < 0 ? 0 : m_foodSupply;
	m_medicineSupply = m_medicineSupply     < 0 ? 0 : m_medicineSupply;
	m_weaponSupply = m_weaponSupply     < 0 ? 0 : m_weaponSupply;

}

void Nation::FoundNation()
{
	m_name = RandomName();
	m_eventCount = 1;

	m_wealth = RandomRange(MIN_START_WEALTH, MAX_START_WEALTH);
	m_technology = RandomRange(MIN_START_TECHNOLOGY, MAX_START_TECHNOLOGY);
	m_population = rand() % MAX_START_POPULATION + MIN_START_POPULATION;
	m_morale = RandomRange(MIN_START_MORALE, MAX_START_MORALE);

	m_Stats.lowestPop = m_population * 2;

	m_waterSupply = m_population * 5;
	m_foodSupply = m_population * 5;
	m_medicineSupply = m_population;
	m_weaponSupply = m_population;

	//Chances for the events to even have a chance of happening
	m_leaderEventMod = 0.35f;
	m_fortuneEventMod = RandomRange(1, 7.5f);
	m_conflictEventMod = RandomRange(1, 7.5f);
	m_disasterEventMod = RandomRange(0.5f, 1.0f);

	m_leaderNewMod = 100;
	m_leaderDeadMod = RandomRange(0, LEADER_DEAD_CHANCE);
	m_leaderKilledMod = RandomRange(0, LEADER_KILLED_CHANCE);
	m_leaderAbandonMod = RandomRange(0, LEADER_ABANDON_CHANCE);

	for (int i = 0; i < m_population; i++)
	{
		m_citizenList.push_back(new Citizen(RandomRange(0,60)));
	}


	m_floodMod = RandomRange(0, DISASTER_FLOOD_CHANCE);
	m_earthquakeMod = RandomRange(0, DISASTER_EARTHQUAKE_CHANCE);
	m_famineMod = RandomRange(0, DISASTER_FAMINE_CHANCE);
	m_droughtMod = RandomRange(0, DISASTER_DROUGHT_CHANCE);
	m_fireMod = RandomRange(0, DISASTER_FIRE_CHANCE);
	m_banditsMod = RandomRange(0, DISASTER_BANDITS_CHANCE);
	m_weatherMod = RandomRange(0, DISASTER_WEATHER_CHANCE);

	m_foodMod = RandomRange(0, FORTUNE_FOOD_CHANCE);
	m_waterMod = RandomRange(0, FORTUNE_WATER_CHANCE);
	m_tradeMod = RandomRange(0, FORTUNE_TRADE_CHANCE);



	if (rand() % 100 < 25)
	{
		m_Biome.SUNNY = true;
	}

	if (rand() % 100 < 25)
	{
		m_Biome.RAINY = true;
	}

	if (rand() % 100 < 25)
	{
		m_Biome.DRY = true;
	}

	if (rand() % 100 < 25)
	{
		m_Biome.NEAR_RIVER = true;
	}

	if (rand() % 100 < 25)
	{
		m_Biome.NEAR_MOUNTAINS = true;
	}

	if (rand() % 100 < 40)
	{
		m_Biome.NEAR_ROAD = true;
	}
}

void Nation::DisbandNation()
{

}

std::string Nation::RandomName()
{
	long double randomName = rand() % 100;
	return "nation" + std::to_string(randomName);
}

float Nation::RandomRange(float min, float max)
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

void Nation::LeaderNew()
{
	m_leaderNewMod = -5;
	m_Stats.leaders++;
}

void Nation::LeaderDead()
{
	m_leaderNewMod = 100;
	m_morale -= m_morale * RandomRange(0.05f, 0.4f);
}

void Nation::LeaderKilled()
{
	m_leaderNewMod = 100;
	m_morale -= m_morale * RandomRange(0.2f, 0.5f);
}

void Nation::LeaderAbandon()
{
	m_leaderNewMod = 100;
	m_morale -= m_morale * RandomRange(0.5f, 0.8f);
}


void Nation::Flood()
{
	//loose half their food
	m_foodSupply /= 2;

	//some medicine & water
	m_medicineSupply -= m_medicineSupply * RandomRange(0.01f, 0.1f);
	m_waterSupply -= m_waterSupply * RandomRange(0.01f, 0.1f);

	m_morale -= m_morale * RandomRange(0.02f, 0.05f);

	int killOff = m_population * RandomRange(0, 0.075f);

	for(int i = 0; i < killOff; i++)
	{
		int randomCitizen = rand() % (int)m_citizenList.size();

		if (randomCitizen >= 0 && randomCitizen < m_citizenList.size())
		{
			m_citizenList.erase(m_citizenList.begin() + randomCitizen);
			m_Stats.diedFromFlood++;
		}
	}

	m_Stats.floods++;
}

void Nation::Earthquake()
{
	m_waterSupply -= m_waterSupply * RandomRange(0.01f, 0.1f);
	m_foodSupply -= m_foodSupply * RandomRange(0.01f, 0.1f);

	m_morale -= m_morale * RandomRange(0.15f, 0.3f);

	int killOff = m_population * RandomRange(0, 0.08f);

	for (int i = 0; i < killOff; i++)
	{
		int randomCitizen = rand() % (int)m_citizenList.size();

		if (randomCitizen >= 0 && randomCitizen < m_citizenList.size())
		{
			m_citizenList.erase(m_citizenList.begin() + randomCitizen);
			m_Stats.diedFromEarthquake++;
		}
	}

	m_earthquakeMod /= 10;

	m_Stats.earthquakes++;
}

void Nation::Famine()
{
	m_foodSupply /= 8;
	m_morale -= m_morale * RandomRange(0.01f, 0.08f);

	int killOff = m_population * RandomRange(0, 0.25f);

	for (int i = 0; i < killOff; i++)
	{
		int randomCitizen = rand() % (int)m_citizenList.size();

		if (randomCitizen >= 0 && randomCitizen < m_citizenList.size())
		{
			m_citizenList.erase(m_citizenList.begin() + randomCitizen);
			m_Stats.diedFromFamine++;
		}
	}

	m_famineMod /= 10;

	m_Stats.famines++;
}

void Nation::Drought()
{
	m_waterSupply /= 8;
	m_morale -= m_morale * RandomRange(0.01f, 0.03f);

	int killOff = m_population * RandomRange(0, 0.25f);

	for (int i = 0; i < killOff; i++)
	{
		int randomCitizen = rand() % (int)m_citizenList.size();

		if (randomCitizen >= 0 && randomCitizen < m_citizenList.size())
		{
			m_citizenList.erase(m_citizenList.begin() + randomCitizen);
			m_Stats.diedFromDrought++;
		}
	}

	m_droughtMod /= 10;

	m_Stats.droughts++;
}

void Nation::Fire()
{
	m_morale -= m_morale * RandomRange(0.01f, 0.025f);

	int killOff = m_population * RandomRange(0, 0.01f);

	for (int i = 0; i < killOff; i++)
	{
		int randomCitizen = rand() % (int)m_citizenList.size();

		if (randomCitizen >= 0 && randomCitizen < m_citizenList.size())
		{
			m_citizenList.erase(m_citizenList.begin() + randomCitizen);
			m_Stats.diedFromFire++;
		}
	}

	m_fireMod /= 8;

	m_Stats.fires++;
}

void Nation::Bandits()
{
	m_waterSupply -= m_waterSupply * RandomRange(0.01f, 0.1f);
	m_foodSupply -= m_foodSupply * RandomRange(0.01f, 0.1f);

	int killOff = m_population * RandomRange(0, 0.005f);

	for (int i = 0; i < killOff; i++)
	{
		int randomCitizen = rand() % (int)m_citizenList.size();

		if (randomCitizen >= 0 && randomCitizen < m_citizenList.size())
		{
			m_citizenList.erase(m_citizenList.begin() + randomCitizen);
		}
	}

	m_morale -= m_morale * RandomRange(0.01f, 0.3f);

	m_banditsMod /= 10;

	m_Stats.banditAttacks++;
}

void Nation::Weather()
{
	m_morale -= m_morale * RandomRange(0.01f, 0.1f);
	m_weatherMod /= 5;

	m_Stats.weatherDisasters++;
}


void Nation::FortuneFood()
{
	m_foodSupply += m_foodSupply * RandomRange(0.07f, 0.29f);
	m_morale += m_morale * RandomRange(0.01f, 0.6f);

	m_foodMod /= 10;

	m_banditsMod += m_banditsMod * 0.01f;

	int pregnancyBoom = rand() % (int)(m_population * 0.1f);

	for (int i = 0; i < pregnancyBoom; i++)
	{
		m_citizenList.push_back(new Citizen(0));
	}

	m_Stats.fortunes++;
}

void Nation::FortuneWater()
{
	m_waterSupply += m_waterSupply * RandomRange(0.07f, 0.29f);
	m_morale += m_morale * RandomRange(0.01f, 0.6f);

	m_waterMod /= 10;

	int pregnancyBoom = rand() % (int)( m_population * 0.1f );

	for (int i = 0; i < pregnancyBoom; i++)
	{
		m_citizenList.push_back(new Citizen(0));
	}

	m_banditsMod += m_banditsMod * 0.01f;
	m_bonusFood += 10;

	m_Stats.fortunes++;
}

void Nation::FortuneTrade()
{
	m_wealth += m_wealth * RandomRange(0.01f, 0.1f);
	m_morale += m_morale * RandomRange(0.01f, 0.2f);

	m_tradeMod /= 10;

	m_banditsMod += m_banditsMod * 0.01f;

	m_Stats.fortunes++;
}


void Nation::UpdateDataGraphs()
{
	m_Stats.yearlyFood.push_back(m_foodSupply);
	m_Stats.yearlyWater.push_back(m_waterSupply);
	m_Stats.yearlyMedicine.push_back(m_medicineSupply);
	m_Stats.yearlyWeapons.push_back(m_weaponSupply);

	m_Stats.yearlyWealth.push_back(m_wealth);
	m_Stats.yearlyTechnology.push_back(m_technology);
	m_Stats.yearlyPopulation.push_back(m_population);
	m_Stats.yearlyMorale.push_back(m_morale);

	if (m_population > m_Stats.highestPop)
		m_Stats.highestPop = m_population;

	if (m_population < m_Stats.lowestPop)
		m_Stats.lowestPop = m_population;
}
