#ifndef _WEEK_H_
#define _WEEK_H_

#include "event.h"
#include <vector>
#include <string>

class Week
{
public:
	Week() {}
	~Week() {}

	void AddEvent(std::string, int);

private:
	//List of events that happened in this week
	std::vector<Event> m_eventList;
};

#endif