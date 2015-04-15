#include "historygenerator.h"
#include <time.h>

int main()
{
	srand(time(NULL));

	HistoryGenerator* hg;
	hg = new HistoryGenerator();

	return hg->Run();
}

