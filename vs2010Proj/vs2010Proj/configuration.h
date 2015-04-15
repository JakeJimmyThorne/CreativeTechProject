#ifndef _CONFIGURATION_H_
#define _CONFIGURATION_H_

//BASE CHANCE VALUES - 0% to 100%
// divide by 52 for that chance to be the overall chance it could happen by each year
static const float LEADER_NEW_CHANCE          = 0.001f   / 52;
static const float LEADER_DEAD_CHANCE		  =	0.0005f	/ 52;
static const float LEADER_KILLED_CHANCE       = 0.005f    / 52;
static const float LEADER_ABANDON_CHANCE      = 0.00001f    / 52;

static const float CONFLICT_START_CHANCE      = 1.0f    / 52;
static const float CONFLICT_END_CHANCE        = 1.0f    / 52;

static const float DISASTER_FLOOD_CHANCE      = 0.00005f    / 52; //modified by proximity to rivers
static const float DISASTER_EARTHQUAKE_CHANCE = 0.000025f	/ 52;  //modified by proximity to mountains
static const float DISASTER_FAMINE_CHANCE     = 0.001f    / 52; //lush land
static const float DISASTER_DROUGHT_CHANCE    = 0.001f    / 52;  //rivers
static const float DISASTER_FIRE_CHANCE       = 0.008f    / 52;  //rivers
static const float DISASTER_BANDITS_CHANCE    = 0.0004f    / 52;  
static const float DISASTER_WEATHER_CHANCE    = 0.002f    / 52;

static const float FORTUNE_FOOD_CHANCE        = 0.8f    / 52;
static const float FORTUNE_WATER_CHANCE       = 0.64f    / 52;
static const float FORTUNE_TRADE_CHANCE       = 0.5f    / 52;

static const float BASE_SUPPLY_STORAGE        = 100;

// MIN/MAX starting values
static const int MIN_START_POPULATION		  = 60;
static const int MAX_START_POPULATION       = 100;

static const float MIN_START_WEALTH			  = 50;
static const float MAX_START_WEALTH			  = 100;

static const float MIN_START_TECHNOLOGY		  = 100;
static const float MAX_START_TECHNOLOGY		  = 1000;

static const float MIN_START_MORALE			  = 100;
static const float MAX_START_MORALE			  = 1000;

// stat caps
static const float TECHNOLOGY_CAP			  = 100;
static const float MORALE_CAP				  = 100;

#endif