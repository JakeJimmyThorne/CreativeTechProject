#include "week.h"

void Week::AddEvent(std::string eventToAdd, int week)
{
	Event newEvent;

	if      (eventToAdd == "LEADER_NEW")		 newEvent.m_event = Event::LEADER_NEW;
	else if (eventToAdd == "LEADER_DEAD")        newEvent.m_event = Event::LEADER_DEAD;
	else if (eventToAdd == "LEADER_KILLED")      newEvent.m_event = Event::LEADER_KILLED;
	else if (eventToAdd == "LEADER_ABANDON")     newEvent.m_event = Event::LEADER_ABANDON;

	else if (eventToAdd == "CONFLICT_START")     newEvent.m_event = Event::CONFLICT_START;
	else if (eventToAdd == "CONFLICT_END")       newEvent.m_event = Event::CONFLICT_END;

	else if (eventToAdd == "DISASTER_FLOOD")     newEvent.m_event = Event::DISASTER_FLOOD;
	else if (eventToAdd == "DISASTER_EARTHQUAKE")newEvent.m_event = Event::DISASTER_EARTHQUAKE;
	else if (eventToAdd == "DISASTER_FAMINE")	 newEvent.m_event = Event::DISASTER_FAMINE;
	else if (eventToAdd == "DISASTER_DROUGHT")	 newEvent.m_event = Event::DISASTER_DROUGHT;
	else if (eventToAdd == "DISASTER_FIRE")		 newEvent.m_event = Event::DISASTER_FIRE;
	else if (eventToAdd == "DISASTER_BANDITS")	 newEvent.m_event = Event::DISASTER_BANDITS;
	else if (eventToAdd == "DISASTER_WEATHER")	 newEvent.m_event = Event::DISASTER_WEATHER;

	else if (eventToAdd == "FORTUNE_FOOD")       newEvent.m_event = Event::FORTUNE_FOOD;
	else if (eventToAdd == "FORTUNE_WATER")      newEvent.m_event = Event::FORTUNE_WATER;
	else if (eventToAdd == "FORTUNE_TRADE")      newEvent.m_event = Event::FORTUNE_TRADE;

	if (newEvent.m_event == NULL)
		return;

	newEvent.m_weekNumber = week;
	m_eventList.push_back(newEvent);
}