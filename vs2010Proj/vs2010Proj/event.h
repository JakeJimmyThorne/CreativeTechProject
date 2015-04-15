#ifndef _EVENT_H_
#define _EVENT_H_

class Event
{
public:

	enum EventType
	{
		NATION_FORMED,       //Start of a civilization
		NATION_DISBAND,		 //Civilization crumbles due to lack of supplies/populate/lost a war

		LEADER_NEW,          //New nation leader
		LEADER_DEAD,		 //Nation leader dies of natural causes/accident
		LEADER_KILLED,		 //Leader assassinated or killed in battle
		LEADER_ABANDON,		 //Leader has abdicated a nation

		CONFLICT_START,      //War starts
		CONFLICT_END,        //War ends

		DISASTER_FLOOD,
		DISASTER_EARTHQUAKE, 
		DISASTER_FAMINE,     //Shortage of food
		DISASTER_DROUGHT,    //Shortage of water
		DISASTER_FIRE,       //Fire outbreak in a town
		DISASTER_BANDITS,    //Town raided by bandits
		DISASTER_WEATHER,    //Bad weather leads to less crops

		FORTUNE_FOOD,        //Good harvest of food
		FORTUNE_WATER,		 //Good supply of water
		FORTUNE_TRADE,		 //Trade boom
		FORTUNE_CELEBRATION  //Celebration lowers food/water, happens when high morale/war is won, increases trade, increases morale
	};

public:
	Event() {}
	~Event() {}

	EventType m_event;

	//week the event(s) happened on
	int m_weekNumber;
};

#endif