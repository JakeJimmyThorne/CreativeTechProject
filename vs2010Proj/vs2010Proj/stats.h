#ifndef _STATS_H_
#define _STATS_H_

#include <vector>

class Stats
{
public:
	Stats();
	~Stats();
	
	int leaders;

	int floods;
	int earthquakes;
	int famines;
	int droughts;
	int fires;
	int banditAttacks;
	int weatherDisasters;

	int fortunes;

	int wars;

	int diedOfOldAge;
	int diedOfStarvation;
	int diedOfThirst;

	int diedFromFlood;
	int diedFromEarthquake;
	int diedFromFamine;
	int diedFromDrought;
	int diedFromFire;

	std::vector<int> yearlyFood;
	std::vector<int> yearlyWater;
	std::vector<int> yearlyMedicine;
	std::vector<int> yearlyWeapons;

	std::vector<int> yearlyWealth;
	std::vector<int> yearlyTechnology;
	std::vector<int> yearlyPopulation;
	std::vector<int> yearlyMorale;

	int highestPop, lowestPop;
	int highestFood, lowestFood;
};

#endif
