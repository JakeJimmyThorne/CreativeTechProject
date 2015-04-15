#ifndef _NATION_H_
#define _NATION_H_

#include <vector>
#include <string>

#include "event.h"
#include "week.h"
#include "configuration.h"
#include "stats.h"
#include "citizen.h"



class Nation
{
public:

	struct BiomeAttributes
	{
		bool SUNNY = false;			  //Increased food intake
		bool RAINY = false;			  //Increased water intake

		bool DRY = false;			  //Higher chance of fire

		bool NEAR_RIVER = false;      //Higher chance of floods
		bool NEAR_MOUNTAINS = false;  //Higher chance of earthquakes
		bool NEAR_ROAD = false;       //Higher chance of bandit attacks
	};

public:
	Nation();
	~Nation();

	void Initialise(int);
	void Simulate();
	void Clamp();

	float m_leaderEventMod; //General leader event

	//Changed dependant on the leader's stats
	float m_leaderNewMod, m_leaderDeadMod, m_leaderKilledMod, m_leaderAbandonMod;

	float m_conflictEventMod; //Executes event depending on current state of war
	
	float m_disasterEventMod; //General disaster mod

	//Individual mods depend on nation location
	float m_floodMod, m_earthquakeMod, m_famineMod, m_droughtMod,
		  m_fireMod,  m_banditsMod,    m_weatherMod;

	float m_fortuneEventMod; //Base fortune mod

	//Changes based on population and stats
	float m_foodMod, m_waterMod, m_tradeMod; 

	//event functions
	void FoundNation();   //Called in year one
	void DisbandNation(); //Called when the nation falls

	Week* GetWeekList() { return m_WeekList; }
	std::string GetName() { return m_name; }

	int EventCount() { return m_eventCount; }
	void IncrementEventCount() { m_eventCount++; }

	Stats* GetStats() { return &m_Stats; }
	std::vector<int> &GetPopulationGraph() { return m_Stats.yearlyPopulation; }


	void UpdateDataGraphs();

	float GetPopulation() { return m_population; }

	//Event functions (change modifiers/stats here)
	void LeaderNew();
	void LeaderDead();
	void LeaderKilled();
	void LeaderAbandon();

	void Flood();
	void Earthquake();
	void Famine();
	void Drought();
	void Fire();
	void Bandits();
	void Weather();

	void FortuneFood();
	void FortuneWater();
	void FortuneTrade();

private:
	Nation* FindByName(std::string);

	std::string RandomName();
	float RandomRange(float, float);

private:
	Stats m_Stats;
	BiomeAttributes m_Biome;

	std::string m_name;
	Week* m_WeekList;
	int m_eventCount;

	//0 - 100%
	float m_waterSupply;
	float m_foodSupply;
	float m_medicineSupply;
	float m_weaponSupply;

	float m_wealth;
	float m_technology;
	float m_population;
	float m_morale;

	std::vector<Citizen*> m_citizenList;

	//List of nation names that this nation hates/likes or is neutral with
	std::vector<std::string> m_hatedNations;
	std::vector<std::string> m_neutralNations;
	std::vector<std::string> m_likedNations;

	//list of nations that this is at war with
	std::vector<std::string> m_atWarWith;
	bool m_inWar;

	//list of all the nations
	static std::vector<const Nation> s_NationList;
	static int s_nationCount;

	int m_nationNumber;
	int m_currentWeek;


	int m_bonusFood;
	int m_bonusWater;
};

#endif