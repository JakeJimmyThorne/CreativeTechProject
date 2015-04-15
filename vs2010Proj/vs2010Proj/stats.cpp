#include "stats.h"

Stats::Stats()
{
	leaders = 0;

	floods = 0;
	earthquakes = 0;
	famines = 0;
	droughts = 0;
	fires = 0;
	banditAttacks = 0;
	weatherDisasters = 0;

	fortunes = 0;

	diedOfOldAge = 0;
	diedOfStarvation = 0;
	diedOfThirst = 0;

	diedFromFlood = 0;
	diedFromEarthquake = 0;
	diedFromFamine = 0;
	diedFromDrought = 0;
	diedFromFire = 0;

	wars = 0;
	highestPop = 0;
	lowestPop = 0;
}

Stats::~Stats()
{

}