#ifndef _HISTORYDATA_H_
#define _HISTORYDATA_H_

#include "nation.h"
#include "configuration.h"

#include <vector>

class HistoryData
{
public:
	HistoryData() {}
	~HistoryData() {}

	void Initialise(int,int);
	void GenerateYear(int);

	int GetNationCount() { return m_nationCount; }
	Nation* GetNation(int);

	float GetSimulationLength() { return m_weekTotal / 52; }

private:

	//Returns value between 0 and 100
	float Random();

private:
	std::vector<Nation> m_NationList;
	int m_nationCount;
	int m_weekTotal;
};

#endif