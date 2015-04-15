//Apparently this method is similar to
//BSpline to I thought it only right to call it JSpline
#ifndef _JSPLINE_H_
#define _JSPLINE_H_

#include <vector>
#include <cmath>

/*
This is a class to push a bigger vector into a smaller vector that I come up with. As I only have 69 horizontal spaces
to play with (visually), I needed to average out any number of years (100+) into a smaller array. What this class does
is takes the generated history and steps through that, averaging points together into a smaller array. 

Data returned will obviously get less precise the more amount of years that are simulated but for rise and declines in
history, it does it's job well.
*/

class JSpline
{
public:

	static std::vector<int> Calculate(int _constraintWidth, std::vector<int> _data)
	{
		std::vector<int> toReturn;

		float stepIncrement = ((float)_data.size()) / ((float)_constraintWidth);
		float runningIncrement = 0;

		for (int i = 0; i < (int)_constraintWidth; i++)
		{
			//what we'll add to the toReturn vector
			int toPushBack = 0;

			runningIncrement += stepIncrement;

			//Get the absolute number and the remainder
			int base = std::floorf(runningIncrement);
			float remainder = runningIncrement - base;

			//the two values the current step(runningIncrement) resides between
			int element1 = 0, element2 = 0;

			if (base < _data.size() - 1)
			{
				element1 = _data[base];
				element2 = _data[base + 1];
			}
			else
			{
				element1 = _data[_data.size() - 2];
				element2 = _data[_data.size() - 1];
			}

			//"take" weighted data from each value 
			float percentage1 = element1 * (1.0f - remainder);
			float percentage2 = element2 * remainder;

			toPushBack = (int)( percentage1 + percentage2 );

			toReturn.push_back(toPushBack);
		}

		return toReturn;
	}
};

#endif