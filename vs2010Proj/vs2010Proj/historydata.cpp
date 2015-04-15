#include "HistoryData.h"

void HistoryData::Initialise(int years, int nations)
{
	m_weekTotal = 0;
	m_NationList.clear();

	for (int i = 0; i < nations; i++)
	{
		Nation nation;
		nation.Initialise(years);
		m_NationList.push_back(nation);
	}

	m_nationCount = nations;
}

void HistoryData::GenerateYear(int year)
{
	for(int week = 1; week <= 52; week++)
	{
		for(int nation = 0; nation < m_nationCount; nation++)
		{
			m_NationList[nation].Simulate();
			//Clamp values if they exceed their max values
			m_NationList[nation].Clamp();

			//Found the nation if in week one
			if (week == 1 && year == 1)
			{
				m_NationList[nation].FoundNation();
			}
			else
			{
				#pragma region Leader event chance logic
				if(Random() < m_NationList[nation].m_leaderEventMod)
				{
					bool eventSelected = false;

					//Test for different leader events
					if (Random() < LEADER_NEW_CHANCE + m_NationList[nation].m_leaderNewMod
						&& !eventSelected)
					{
						m_NationList[nation].GetWeekList()->AddEvent("LEADER_NEW", week);
						m_NationList[nation].LeaderNew();

						m_NationList[nation].IncrementEventCount();
						eventSelected = true;
					}

					if(Random() < LEADER_DEAD_CHANCE + m_NationList[nation].m_leaderDeadMod 
						&& !eventSelected)
					{
						m_NationList[nation].GetWeekList()->AddEvent("LEADER_DEAD", week);
						m_NationList[nation].LeaderDead();

						m_NationList[nation].IncrementEventCount();
						eventSelected = true;
					}

					if(Random() < LEADER_KILLED_CHANCE + m_NationList[nation].m_leaderKilledMod
						&& !eventSelected)
					{
						m_NationList[nation].GetWeekList()->AddEvent("LEADER_KILLED", week);
						m_NationList[nation].LeaderKilled();

						m_NationList[nation].IncrementEventCount();
						eventSelected = true;
					}

					if(Random() < LEADER_ABANDON_CHANCE + m_NationList[nation].m_leaderAbandonMod 
						&& !eventSelected)
					{
						m_NationList[nation].GetWeekList()->AddEvent("LEADER_ABANDON", week);
						m_NationList[nation].LeaderAbandon();

						m_NationList[nation].IncrementEventCount();
						eventSelected = true;
					}
				}
				#pragma endregion 

				#pragma region Disaster event chance logic
				if(Random() < m_NationList[nation].m_disasterEventMod + (m_NationList[nation].GetPopulation() / 5000))
				{
					bool eventSelected = false;

					if(Random() < DISASTER_FLOOD_CHANCE + m_NationList[nation].m_floodMod
						&& !eventSelected)
					{
						m_NationList[nation].GetWeekList()->AddEvent("DISASTER_FLOOD", week);
						m_NationList[nation].Flood();

						m_NationList[nation].IncrementEventCount();
						eventSelected = true;
					}

					if(Random() < DISASTER_EARTHQUAKE_CHANCE + m_NationList[nation].m_earthquakeMod
						&& !eventSelected)
					{
						m_NationList[nation].GetWeekList()->AddEvent("DISASTER_EARTHQUAKE", week);
						m_NationList[nation].Earthquake();

						m_NationList[nation].IncrementEventCount();
						eventSelected = true;
					}

					if (Random() < DISASTER_FAMINE_CHANCE + m_NationList[nation].m_famineMod + (m_NationList[nation].GetPopulation() / 5000)
						&& !eventSelected)
					{
						m_NationList[nation].GetWeekList()->AddEvent("DISASTER_FAMINE", week);
						m_NationList[nation].Famine();

						m_NationList[nation].IncrementEventCount();
						eventSelected = true;
					}

					if (Random() < DISASTER_DROUGHT_CHANCE + m_NationList[nation].m_droughtMod + (m_NationList[nation].GetPopulation() / 7000)
						&& !eventSelected)
					{
						m_NationList[nation].GetWeekList()->AddEvent("DISASTER_DROUGHT", week);
						m_NationList[nation].Drought();

						m_NationList[nation].IncrementEventCount();
						eventSelected = true;
					}

					if (Random() < DISASTER_FIRE_CHANCE + m_NationList[nation].m_fireMod + (m_NationList[nation].GetPopulation() / 3000)
						&& !eventSelected)
					{
						m_NationList[nation].GetWeekList()->AddEvent("DISASTER_FIRE", week);
						m_NationList[nation].Fire();

						m_NationList[nation].IncrementEventCount();
						eventSelected = true;
					}

					if(Random() < DISASTER_BANDITS_CHANCE + m_NationList[nation].m_banditsMod
						&& !eventSelected)
					{
						m_NationList[nation].GetWeekList()->AddEvent("DISASTER_BANDITS", week);
						m_NationList[nation].Bandits();

						m_NationList[nation].IncrementEventCount();
						eventSelected = true;
					}

					if(Random() < DISASTER_WEATHER_CHANCE + m_NationList[nation].m_weatherMod
						&& !eventSelected)
					{
						m_NationList[nation].GetWeekList()->AddEvent("DISASTER_WEATHER", week);
						m_NationList[nation].Weather();

						m_NationList[nation].IncrementEventCount();
						eventSelected = true;
					}
				}
				#pragma endregion 

				#pragma region Fortune event chance logic
				if(Random() < m_NationList[nation].m_fortuneEventMod)
				{
					bool eventSelected = false;

					if(Random() < FORTUNE_FOOD_CHANCE + m_NationList[nation].m_foodMod
						&& !eventSelected)
					{
						m_NationList[nation].GetWeekList()->AddEvent("FORTUNE_FOOD", week);
						m_NationList[nation].FortuneFood();

						m_NationList[nation].IncrementEventCount();
						eventSelected = true;
					}

					if(Random() < FORTUNE_WATER_CHANCE + m_NationList[nation].m_waterMod
						&& !eventSelected)
					{
						m_NationList[nation].GetWeekList()->AddEvent("FORTUNE_WATER", week);
						m_NationList[nation].FortuneWater();

						m_NationList[nation].IncrementEventCount();
						eventSelected = true;
					}

					if(Random() < FORTUNE_TRADE_CHANCE + m_NationList[nation].m_tradeMod
						&& !eventSelected)
					{
						m_NationList[nation].GetWeekList()->AddEvent("FORTUNE_TRADE", week);
						m_NationList[nation].FortuneTrade();

						m_NationList[nation].IncrementEventCount();
						eventSelected = true;
					}
				}
				#pragma endregion 
			}

			
		}

		m_weekTotal++;
	}

	for (int nation = 0; nation < m_nationCount; nation++)
	{
		m_NationList[nation].UpdateDataGraphs();
	}
}

Nation* HistoryData::GetNation(int index)
{
	return &m_NationList[index];
}

float HistoryData::Random()
{
	float toReturn = (rand() % 100) * (rand() % 100);
	toReturn /= 100;
	return toReturn;
}