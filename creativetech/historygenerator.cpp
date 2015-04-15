#include "historygenerator.h"

//preprocessor directives

#include <cstdio>
#include <regex>
#include <fstream>


#define atCoord(x,y) rlutil::locate(x,y);
#define print std::cout <<

HistoryGenerator::HistoryGenerator()
{
	
}

HistoryGenerator::~HistoryGenerator()
{

}

bool HistoryGenerator::Run()
{
	bool running = true;

	Initialise();	

	while (running)
	{
		running = Update();
	}

	return running;
}

void HistoryGenerator::Initialise()
{
	//initialise the screen to nothing
	for (int y = 1; y < SCREEN_Y; y++)
	{
		for (int x = 1; x < SCREEN_X; x++)
		{
			m_screen[x][y] = " ";
		}
	}

	m_updated = false;
	m_selection = 0;
	m_selected = false;
	m_generating = false;

	m_yearsToSimulate = 100;
	m_startNations = 1;
	m_generationIncrement = 0;
	m_currentYear = 1;

	//Initial state will be the menu
	m_State = MENU;

	InitialiseBorder();
	InitialiseEncyclopaedia();
}

bool HistoryGenerator::Update()
{
	bool result = true;

	//if not up to date, update the visuals
	if (!m_updated)
	{
		if(m_State == MENU)
			DrawMenu();

		if (m_State == ABOUT)
			DrawAbout();

		if (m_State == GENERATION_SETUP)
			DrawSetupGeneration();

		if (m_State == GENERATION)
			DrawGeneration();

		if (m_State == ENCYCLOPAEDIA)
			DrawEncyclopaedia();

		m_updated = true;
	}

	//updating
	switch (m_State)
	{
	case MENU:
		if (m_selected)
		{
			m_updated = false;
			m_selected = false;
			
			//going to generation setup
			if (m_selection == 0)
			{
				//reset the selection
				m_selection = 0;

				m_State = GENERATION_SETUP;
				return true;
			}

			if (m_selection == 1)
			{
				m_selection = 0;
				m_encycloSelect = 0;
				m_State = ENCYCLOPAEDIA;
				return true;
			}

			//going to the about screen
			if (m_selection == 2)
			{
				m_State = ABOUT;
				return true;
			}

			//exiting the program
			if (m_selection == 3)
				return false;
		}
		break;
	case ENCYCLOPAEDIA:
		if (m_selected)
		{
			m_updated = false;
			m_selected = false;

			//going to generation setup
			if (m_selection == 0)
			{
				//reset the selection
				m_selection = 0;

				m_State = MENU;
				return true;
			}
		}
		break;
	case ABOUT:
		if (m_selected)
		{
			m_updated = false;
			m_selected = false;
			m_State = MENU;
			
			//reset the selection
			m_selection = 0;

			return true;
		}
		break;
	case GENERATION:

		Generate();

		m_State = MENU;
		m_generating = false;
		m_updated = false;

		m_currentYear = 0;

		//reset the selection
		m_selection = 0;

		return true;
		break;
	case GENERATION_SETUP:
		if (m_selected)
		{
			m_updated = false;
			m_selected = false;

			if (m_selection == 2)
			{
				m_State = GENERATION;
				m_generating = true;
				m_generationIncrement = m_yearsToSimulate / 50;

				m_History.Initialise(m_yearsToSimulate, 1);

				rlutil::cls();

				return true;
			}

			if (m_selection == 3)
			{
				//reset the selection
				m_selection = 0;

				m_State = MENU;
				return true;
			}
		}
		break;
	}

	if(!m_generating)
		HandleInput();

	return result;
}

void HistoryGenerator::HandleInput()
{
	//get user input
	char input = getch();

	bool up = false, down = false;

    #pragma region test the input

	switch(input)
	{
	case 'w':
		up = true;
		break;
	case 's':
		down = true;
		break;
	case ' ':
		m_selected = true;
		break;
	case 'd':
		//in generation setup we use the D key to increase the variables
		if (m_State == GENERATION_SETUP)
		{
			/*if (m_selection == 0)
			{
				m_updated = false;
				m_yearsToSimulate++;
			}
			else if (m_selection == 1)
			{
				if (m_startNations < NATION_LIMIT)
				{
					m_updated = false;
					m_startNations++;
				}
			}*/
		}

		//use D to cycle through different info
		if (m_State == ENCYCLOPAEDIA)
		{
			if (m_encycloSelect < 4)
			{
				m_encycloSelect++;
				m_updated = false;
			}
		}
		break;
	case 'a':
		//in generation setup we use the A key to decrease variables
		if (m_State == GENERATION_SETUP)
		{
			/*if (m_selection == 0)
			{
				if (m_yearsToSimulate > 0)
				{
					m_yearsToSimulate--;
					m_updated = false;
				}
			}
			else if (m_selection == 1)
			{
				if (m_startNations > 0)
				{
					m_startNations--;
					m_updated = false;
				}
			}*/
		}

		//use A to cycle through different info
		if (m_State == ENCYCLOPAEDIA)
		{
			if (m_encycloSelect > 0)
			{
				m_encycloSelect--;
				m_updated = false;
			}
		}
		break;
	#pragma region Generator shortcuts
	case '1':
		if (m_State == GENERATION_SETUP)
		{
			if (m_selection == 0)
			{
				m_updated = false;
				m_yearsToSimulate += 10;
			}
		}
		break;
	case '2':
		if (m_State == GENERATION_SETUP)
		{
			if (m_selection == 0)
			{
				m_updated = false;
				m_yearsToSimulate += 20;
			}
		}
		break;
	case '3':
		if (m_State == GENERATION_SETUP)
		{
			if (m_selection == 0)
			{
				m_updated = false;
				m_yearsToSimulate += 30;
			}
		}
		break;
	case '4':
		if (m_State == GENERATION_SETUP)
		{
			if (m_selection == 0)
			{
				m_updated = false;
				m_yearsToSimulate += 40;
			}
		}
		break;
	case '5':
		if (m_State == GENERATION_SETUP)
		{
			if (m_selection == 0)
			{
				m_updated = false;
				m_yearsToSimulate += 50;
			}
		}
		break;
	case '6':
		if (m_State == GENERATION_SETUP)
		{
			if (m_selection == 0)
			{
				m_updated = false;
				m_yearsToSimulate += 60;
			}
		}
		break;
	case '7':
		if (m_State == GENERATION_SETUP)
		{
			if (m_selection == 0)
			{
				m_updated = false;
				m_yearsToSimulate += 70;
			}
		}
		break;
	case '8':
		if (m_State == GENERATION_SETUP)
		{
			if (m_selection == 0)
			{
				m_updated = false;
				m_yearsToSimulate += 80;
			}
		}
		break;
	case '9':
		if (m_State == GENERATION_SETUP)
		{
			if (m_selection == 0)
			{
				m_updated = false;
				m_yearsToSimulate += 90;
			}
		}
		break;
		#pragma endregion 
	}

	#pragma endregion 

	//don't need to move on the ABOUT screen
	if (m_State == ABOUT)
		return;

	//if nothing has been pressed, don't even check; just return
	if (!up && !down)
		return;

	//up or down movement
	if (up)
	{
		if (m_selection > 0)
		{
			m_selection--;
			m_updated = false;
		}
	}
	else if(down)
	{
		int max = 0;

		switch (m_State)
		{
		case MENU:
			max = 3; //four options
			break;
		case ENCYCLOPAEDIA:
			max = m_History.GetNationCount();
			break;
		case GENERATION_SETUP:
			max = 3; //four options
			break;
		}

		if (m_selection < max)
		{
			m_selection++;
			m_updated = false;
		}
	}
}

void HistoryGenerator::Generate()
{
	while (m_generating)
	{
		//update the screen if it needs updating
		if(!m_updated)
		{
			DrawGeneration();
			m_updated = true;
		}

		m_History.GenerateYear(m_currentYear);

		m_currentYear++;
		m_updated = false;

		//End the generation if completed
		if (m_currentYear > m_yearsToSimulate)
		{
			m_generating = false;
			/*std::ofstream myfile;
			myfile.open("population.txt");

			for (int i = 0; i < m_yearsToSimulate; i++)
			{
				myfile << m_History.GetNation(0)->GetStats()->yearlyPopulation[i] << std::endl;
			}
			
			myfile.close();*/
		}
	}

	return;
}

void HistoryGenerator::InitialiseBorder()
{
	//Set the top and bottom borders of the screen
	for (int x = 1; x < SCREEN_X; x++)
	{
		m_screen[x][1] = char(176);
		m_screen[x][SCREEN_Y - 1] = char(176);
	}

	//Set the left and right borders of the screen
	for (int y = 1; y < SCREEN_Y; y++)
	{
		m_screen[1][y] = char(176);
		m_screen[SCREEN_X - 1][y] = char(176);
	}
}

void HistoryGenerator::InitialiseEncyclopaedia()
{

}

void HistoryGenerator::DrawMenu()
{
	//clear the screen
	rlutil::cls();
	DrawOutline();

	rlutil::setColor(15); //set colour to white

	//Title
	atCoord(SCREEN_X/2 - MENU_TITLE.length()/2 , 3) print MENU_TITLE;

	//title decoration
	for (int i = 0; i < MENU_TITLE.length(); i++)
	{
		atCoord(SCREEN_X / 2 - MENU_TITLE.length() / 2 + i, 4) print char(194);
	}

	#pragma region MenuOptions
	atCoord(SCREEN_X / 2 - MENU_FOOTER.length() / 2, 25) print MENU_FOOTER;

	//menu options
	int option1Line = 8, option2Line = 10, option3Line = 12, option4Line = 14;

	//option 1
	if (m_selection == 0) rlutil::setColor(12);
	else rlutil::setColor(15);

	if (m_selection == 0)
	{
		atCoord(SCREEN_X / 2 - MENU_OPTION1.length() / 2 - 2, option1Line) print SELECTION_ICON;
		atCoord(SCREEN_X / 2 + MENU_OPTION1.length() / 2 + 2, option1Line) print SELECTION_ICON;
	}

	atCoord(SCREEN_X / 2 - MENU_OPTION1.length() / 2, option1Line) print MENU_OPTION1;

	//option 2
	if (m_selection == 1) rlutil::setColor(12);
	else rlutil::setColor(15);

	if (m_selection == 1)
	{
		atCoord(SCREEN_X / 2 - MENU_OPTION2.length() / 2 - 2, option2Line) print SELECTION_ICON;
		atCoord(SCREEN_X / 2 + MENU_OPTION2.length() / 2 + 2, option2Line) print SELECTION_ICON;
	}

	atCoord(SCREEN_X / 2 - MENU_OPTION2.length() / 2, option2Line) print MENU_OPTION2;

	//option 3
	if (m_selection == 2) rlutil::setColor(12);
	else rlutil::setColor(15);

	if (m_selection == 2)
	{
		atCoord(SCREEN_X / 2 - MENU_OPTION3.length() / 2 - 2, option3Line) print SELECTION_ICON;
		atCoord(SCREEN_X / 2 + MENU_OPTION3.length() / 2 + 2, option3Line) print SELECTION_ICON;
	}

	atCoord(SCREEN_X / 2 - MENU_OPTION3.length() / 2, option3Line) print MENU_OPTION3;

	//option 4
	if (m_selection == 3) rlutil::setColor(12);
	else rlutil::setColor(15);

	if (m_selection == 3)
	{
		atCoord(SCREEN_X / 2 - MENU_OPTION4.length() / 2 - 2, option4Line) print SELECTION_ICON;
		atCoord(SCREEN_X / 2 + MENU_OPTION4.length() / 2 + 2, option4Line) print SELECTION_ICON;
	}

	atCoord(SCREEN_X / 2 - MENU_OPTION4.length() / 2, option4Line) print MENU_OPTION4;

	#pragma endregion 

	rlutil::setColor(15);
	atCoord(SCREEN_X / 2 - MENU_CONTROLS.length() / 2, 22) print MENU_CONTROLS;

	//set cursor to top left to show normal screen
	//then hide the cursor
	atCoord(1, 1) rlutil::hidecursor();
}

void HistoryGenerator::DrawEncyclopaedia()
{
	//clear the screen
	rlutil::cls();
	DrawOutline();

	rlutil::setColor(15); //set colour to white

	if (m_selection == 0) 
		rlutil::setColor(12);
	else 
		rlutil::setColor(15);

	atCoord(SCREEN_X * ENCYCLO_START_WIDTH, SCREEN_Y * ENCYCLO_START_HEIGHT - 2)
		print "Back";

	//if no data
	if (m_History.GetNationCount() <= 0)
	{
		rlutil::setColor(15);

		atCoord(SCREEN_X * ENCYCLO_START_WIDTH, SCREEN_Y * ENCYCLO_START_HEIGHT)
			print "No data available. Please generate history first.";

		return;
	}

	//header drawing
	if (m_selection != 0)
	{
		std::string header = "";

		header = "Gen";

		if (m_encycloSelect == 0) rlutil::setColor(12); else rlutil::setColor(15);
		atCoord(SCREEN_X * ENCYCLO_START_WIDTH + 15, SCREEN_Y * ENCYCLO_START_HEIGHT) print header;

		header = "Pop";

		if (m_encycloSelect == 1) rlutil::setColor(12); else rlutil::setColor(15);
		atCoord(SCREEN_X * ENCYCLO_START_WIDTH + 20, SCREEN_Y * ENCYCLO_START_HEIGHT) print header;

		header = "Evt";

		if (m_encycloSelect == 2) rlutil::setColor(12); else rlutil::setColor(15);
		atCoord(SCREEN_X * ENCYCLO_START_WIDTH + 25, SCREEN_Y * ENCYCLO_START_HEIGHT) print header;

		header = "Eco";

		if (m_encycloSelect == 3) rlutil::setColor(12); else rlutil::setColor(15);
		atCoord(SCREEN_X * ENCYCLO_START_WIDTH + 25, SCREEN_Y * ENCYCLO_START_HEIGHT) print header;
	}


	//drawing
	switch (m_encycloSelect)
	{
	case 0:
	{
			  //First info screen
#pragma region Nation Drawing

			  for (int i = 0; i < m_History.GetNationCount(); i++)
			  {
				  if (m_selection == i + 1)
				  {
					  rlutil::setColor(15);

					  std::string text = "";

					  //total events
					  text = "Total events over " +
						  std::to_string((long double)m_History.GetSimulationLength()) +
						  " years: " +
						  std::to_string((long double)m_History.GetNation(i)->EventCount());
					  RemoveZeroes(text);
					  atCoord(SCREEN_X * ENCYCLO_START_WIDTH + 15, SCREEN_Y * ENCYCLO_START_HEIGHT - 3) print text;

					  //average events per week
					  text = "Avg events p/w: " +
						  std::to_string((long double)m_History.GetSimulationLength() * 52 / (long double)m_History.GetNation(i)->EventCount());

					  atCoord(SCREEN_X * ENCYCLO_START_WIDTH + 15, SCREEN_Y * ENCYCLO_START_HEIGHT - 2) print text;

					  //leaders
					  text = "Leader count:     " + std::to_string((long double)m_History.GetNation(i)->GetStats()->leaders);
					  RemoveZeroes(text);
					  atCoord(SCREEN_X * ENCYCLO_START_WIDTH + 15, SCREEN_Y * ENCYCLO_START_HEIGHT + 2) print text;

					  //floods
					  text = "flood count:      " + std::to_string((long double)m_History.GetNation(i)->GetStats()->floods) +
						  "    Avg per year: " + std::to_string((long double)m_History.GetNation(i)->GetStats()->floods /
																(long double)m_History.GetSimulationLength());
					  RemoveZeroes(text);
					  atCoord(SCREEN_X * ENCYCLO_START_WIDTH + 15, SCREEN_Y * ENCYCLO_START_HEIGHT + 3) print text;

					  //earthquakes
					  text = "earthquake count: " + std::to_string((long double)m_History.GetNation(i)->GetStats()->earthquakes) +
						  "    Avg per year: " + std::to_string((long double)m_History.GetNation(i)->GetStats()->earthquakes /
																(long double)m_History.GetSimulationLength());
					  RemoveZeroes(text);
					  atCoord(SCREEN_X * ENCYCLO_START_WIDTH + 15, SCREEN_Y * ENCYCLO_START_HEIGHT + 4) print text;

					  //famines
					  text = "famine count:     " + std::to_string((long double)m_History.GetNation(i)->GetStats()->famines) +
						  "    Avg per year: " + std::to_string((long double)m_History.GetNation(i)->GetStats()->famines /
																(long double)m_History.GetSimulationLength());
					  RemoveZeroes(text);
					  atCoord(SCREEN_X * ENCYCLO_START_WIDTH + 15, SCREEN_Y * ENCYCLO_START_HEIGHT + 5) print text;

					  //droughts
					  text = "drought count:    " + std::to_string((long double)m_History.GetNation(i)->GetStats()->droughts) +
						  "    Avg per year: " + std::to_string((long double)m_History.GetNation(i)->GetStats()->droughts /
																(long double)m_History.GetSimulationLength());
					  RemoveZeroes(text);
					  atCoord(SCREEN_X * ENCYCLO_START_WIDTH + 15, SCREEN_Y * ENCYCLO_START_HEIGHT + 6) print text;

					  //fires
					  text = "fire count:       " + std::to_string((long double)m_History.GetNation(i)->GetStats()->fires) +
						  "    Avg per year: " + std::to_string((long double)m_History.GetNation(i)->GetStats()->fires /
																(long double)m_History.GetSimulationLength());
					  RemoveZeroes(text);
					  atCoord(SCREEN_X * ENCYCLO_START_WIDTH + 15, SCREEN_Y * ENCYCLO_START_HEIGHT + 7) print text;

					  //bandit attacks   
					  text = "bandit attacks:   " + std::to_string((long double)m_History.GetNation(i)->GetStats()->banditAttacks) +
						  "    Avg per year: " + std::to_string((long double)m_History.GetNation(i)->GetStats()->banditAttacks /
																(long double)m_History.GetSimulationLength()
						  );
					  RemoveZeroes(text);
					  atCoord(SCREEN_X * ENCYCLO_START_WIDTH + 15, SCREEN_Y * ENCYCLO_START_HEIGHT + 8) print text;

					  //weatherDisasters
					  text = "bad weather:      " + std::to_string((long double)m_History.GetNation(i)->GetStats()->weatherDisasters) +
						  "    Avg per year: " + std::to_string(m_History.GetNation(i)->GetStats()->weatherDisasters /
																m_History.GetSimulationLength());
					  RemoveZeroes(text);
					  atCoord(SCREEN_X * ENCYCLO_START_WIDTH + 15, SCREEN_Y * ENCYCLO_START_HEIGHT + 9) print text;

					  //fortunes
					  text = "Fortunes count:   " + std::to_string((long double)m_History.GetNation(i)->GetStats()->fortunes) +
						  "   Avg per year: " + std::to_string((long double)m_History.GetNation(i)->GetStats()->fortunes /
															   (long double)m_History.GetSimulationLength()
						  );
					  RemoveZeroes(text);
					  atCoord(SCREEN_X * ENCYCLO_START_WIDTH + 15, SCREEN_Y * ENCYCLO_START_HEIGHT + 10) print text;

					  //floods

					  rlutil::setColor(12);
				  }
				  else
					  rlutil::setColor(15);

				  atCoord(SCREEN_X * ENCYCLO_START_WIDTH, SCREEN_Y * ENCYCLO_START_HEIGHT + i)

					  std::string name = m_History.GetNation(i)->GetName();
				  RemoveZeroes(name);

				  print name;


			  }

#pragma endregion 
break;
	}
	case 1:
	{
		//Population graph screen
		for (int i = 0; i < m_History.GetNationCount(); i++)
		{
			if (m_selection == i + 1)
			{
				rlutil::setColor(15);

   				std::string text = "";

				//total events
				text = "Population rise over " +
					std::to_string((long double)m_History.GetSimulationLength()) +
					" years: " +
					std::to_string(m_History.GetNation(0)->GetStats()->highestPop - m_History.GetNation(0)->GetStats()->lowestPop);
				RemoveZeroes(text);
				atCoord(SCREEN_X * ENCYCLO_START_WIDTH + 15, SCREEN_Y * ENCYCLO_START_HEIGHT - 3) print text;

				//table width is 60 and height is 15
				
				//draw the left bar (with population numbers)
				for (int t = 0; t < 15; t++)
				{
					if (t == 0)
					{
						atCoord(SCREEN_X * ENCYCLO_START_WIDTH + 10, SCREEN_Y * ENCYCLO_START_HEIGHT + 2 + t)
							print std::to_string(m_History.GetNation(0)->GetStats()->highestPop);
					}

					if (t == 7)
					{
						atCoord(SCREEN_X * ENCYCLO_START_WIDTH + 10, SCREEN_Y * ENCYCLO_START_HEIGHT + 2 + t)
							print std::to_string(m_History.GetNation(0)->GetStats()->highestPop / 2);
					}

					text = "]";
					atCoord(SCREEN_X * ENCYCLO_START_WIDTH + 15, SCREEN_Y * ENCYCLO_START_HEIGHT + 2 + t) print char(186);
				}

				//bottom border
				for (int t = 0; t < 60; t++)
				{
					if (t == 0)
					{
						atCoord(SCREEN_X * ENCYCLO_START_WIDTH + 15, SCREEN_Y * ENCYCLO_START_HEIGHT + 17)
							print char(200);

						atCoord(SCREEN_X * ENCYCLO_START_WIDTH + 12, SCREEN_Y * ENCYCLO_START_HEIGHT + 17)
							print "0";
					}
					else
					{
						atCoord(SCREEN_X * ENCYCLO_START_WIDTH + 15 + t, SCREEN_Y * ENCYCLO_START_HEIGHT + 17) 
							print char(205);
					}

				}

				//range of 14 to work with
				int highestPoint = SCREEN_Y * ENCYCLO_START_HEIGHT + 2; //8
				int lowestPoint = SCREEN_Y * ENCYCLO_START_HEIGHT + 16; //22

				std::vector<int> dataPoints = m_History.GetNation(0)->GetStats()->yearlyPopulation;

				//Squeeze the bigger data into the 69 slots of the table
				std::vector<int> tableData = JSpline::Calculate(59, dataPoints);

				//increments of how far each place jumps up on the table
				std::vector<int> populationScale;

				for (int s = 0; s < 14; s++)
				{
					populationScale.push_back((m_History.GetNation(0)->GetStats()->highestPop / 14) * i + 1);
				}
				
				//data drawing
				for (int p = 0; p < 59; p++)
				{
					//converting the population amount of the tableData to where it can be resembled on the table
					float point = ((float)tableData[p]) / ((float)m_History.GetNation(0)->GetStats()->highestPop);
					point *= 1.4f;

					//get the vector point and then the remainder to see if it's a high/med/low point in that
					//particular region
					int actualPoint = std::floorf(point * 10);
					float remainder = (point * 10) - actualPoint;
					
					if (remainder > 0 && remainder <= 0.33f)
					{
						atCoord(SCREEN_X * ENCYCLO_START_WIDTH + 16 + p, lowestPoint - actualPoint)
							print char(220); //low
					}
					else if (remainder > 0.33f && remainder <= 0.66f)
					{
						atCoord(SCREEN_X * ENCYCLO_START_WIDTH + 16 + p, lowestPoint - actualPoint)
							print char(254); //mid
					}
					else if (remainder > 0.66f)
					{
						atCoord(SCREEN_X * ENCYCLO_START_WIDTH + 16 + p, lowestPoint - actualPoint)
							print char(223); //high
					}
				}

				rlutil::setColor(12);
			}
			else
				rlutil::setColor(15);

			atCoord(SCREEN_X * ENCYCLO_START_WIDTH, SCREEN_Y * ENCYCLO_START_HEIGHT + i)

				std::string name = m_History.GetNation(i)->GetName();
			RemoveZeroes(name);

			print name;
		}

		break;
	}

	}

	

		
		
	

	//set cursor to top left to show normal screen
	//then hide the cursor
	atCoord(1, 1) rlutil::hidecursor();
}

void HistoryGenerator::DrawAbout()
{
	//clear the screen
	rlutil::cls();
	DrawOutline();

	rlutil::setColor(15); //set colour to white

	//about title
	atCoord(SCREEN_X / 2 - ABOUT_TITLE.length() / 2, 3) print ABOUT_TITLE;

	//title decoration
	for (int i = 0; i < ABOUT_TITLE.length(); i++)
	{
		atCoord(SCREEN_X / 2 - ABOUT_TITLE.length() / 2 + i, 4) print char(194);
	}

	int startLine = 9;

	atCoord(SCREEN_X / 2 - ABOUT_LINE1.length() / 2, startLine) print ABOUT_LINE1;
	atCoord(SCREEN_X / 2 - ABOUT_LINE2.length() / 2, startLine+1) print ABOUT_LINE2;
	atCoord(SCREEN_X / 2 - ABOUT_LINE3.length() / 2, startLine+2) print ABOUT_LINE3;
	atCoord(SCREEN_X / 2 - ABOUT_LINE4.length() / 2, startLine+3) print ABOUT_LINE4;
	atCoord(SCREEN_X / 2 - ABOUT_LINE5.length() / 2, startLine+4) print ABOUT_LINE5;

	atCoord(1, 1)
}

void HistoryGenerator::DrawSetupGeneration()
{
	//clear the screen
	rlutil::cls();
	DrawOutline();

	rlutil::setColor(15); //set colour to white

	//Title
	atCoord(SCREEN_X / 2 - MENU_TITLE.length() / 2, 3) print MENU_TITLE;

	//title decoration
	for (int i = 0; i < MENU_TITLE.length(); i++)
	{
		atCoord(SCREEN_X / 2 - MENU_TITLE.length() / 2 + i, 4) print char(194);
	}

#pragma region Options
	//options
	int option1Line = 8, option2Line = 9, option3Line = 11, option4Line = 12;

	//option 1
	if (m_selection == 0) rlutil::setColor(12);
	else rlutil::setColor(15);

	if (m_selection == 0)
	{
		atCoord(SCREEN_X / 2 - SETUP_OPTION1.length() / 2 - 2, option1Line) print SELECTION_ICON;
		atCoord(SCREEN_X / 2 + SETUP_OPTION1.length() / 2 + 2, option1Line) print SELECTION_ICON;
	}

	atCoord(SCREEN_X / 2 - SETUP_OPTION1.length() / 2, option1Line) print SETUP_OPTION1 << m_yearsToSimulate;

	//option 2
	if (m_selection == 1) rlutil::setColor(12);
	else rlutil::setColor(15);

	if (m_selection == 1)
	{
		atCoord(SCREEN_X / 2 - SETUP_OPTION2.length() / 2 - 2, option2Line) print SELECTION_ICON;
		atCoord(SCREEN_X / 2 + SETUP_OPTION2.length() / 2 + 2, option2Line) print SELECTION_ICON;
	}

	atCoord(SCREEN_X / 2 - SETUP_OPTION2.length() / 2, option2Line) print SETUP_OPTION2 << m_startNations;

	//option 3
	if (m_selection == 2) rlutil::setColor(12);
	else rlutil::setColor(15);

	if (m_selection == 2)
	{
		atCoord(SCREEN_X / 2 - SETUP_OPTION3.length() / 2 - 2, option3Line) print SELECTION_ICON;
		atCoord(SCREEN_X / 2 + SETUP_OPTION3.length() / 2 + 2, option3Line) print SELECTION_ICON;
	}

	atCoord(SCREEN_X / 2 - SETUP_OPTION3.length() / 2, option3Line) print SETUP_OPTION3;

	//option 4
	if (m_selection == 3) rlutil::setColor(12);
	else rlutil::setColor(15);

	if (m_selection == 3)
	{
		atCoord(SCREEN_X / 2 - SETUP_OPTION4.length() / 2 - 2, option4Line) print SELECTION_ICON;
		atCoord(SCREEN_X / 2 + SETUP_OPTION4.length() / 2 + 2, option4Line) print SELECTION_ICON;
	}

	atCoord(SCREEN_X / 2 - SETUP_OPTION4.length() / 2, option4Line) print SETUP_OPTION4;

#pragma endregion 

	rlutil::setColor(15);
	atCoord(SCREEN_X / 2 - SETUP_CONTROLS.length() / 2, 22) print SETUP_CONTROLS;

	//set cursor to top left to show normal screen
	//then hide the cursor
	atCoord(1, 1) 
}

void HistoryGenerator::DrawGeneration()
{
	//clear the screen
	//rlutil::cls();
	//DrawOutline();

	atCoord(5, 4) print "[";

	//drawing the progress bar 
	const int drawAmount = 70;
	for (int i = 0; i < m_currentYear * drawAmount / m_yearsToSimulate; i++)
	{
		atCoord(6 + i, 4) print "#";
	}

	atCoord(SCREEN_X - 5, 4) print "]";

	atCoord(1,1)
}

void HistoryGenerator::DrawOutline()
{
	rlutil::setColor(12); //set colour to red 
	
	for (int y = 1; y < SCREEN_Y; y++)
	{
		for (int x = 1; x < SCREEN_X; x++)
		{
			if (m_screen[x][y] != " ")
			{
				atCoord(x, y) print m_screen[x][y];
			}
		}
	}	
}

void HistoryGenerator::RemoveZeroes(std::string& text)
{
	bool foundPoint = false;
	bool checked = false;

	for (int i = 0; i < text.length(); i++)
	{
		if (text.at(i) == '.')
		{
			foundPoint = true;
		}

		if (foundPoint)
		{
			if (!checked)
			{
				for (int x = i + 1; x < text.length(); x++)
				{
					if (text.at(x) == ' ') break;

					if (text.at(x) == '1' || text.at(x) == '2' || text.at(x) == '3' || text.at(x) == '4' ||
						text.at(x) == '5' || text.at(x) == '6' || text.at(x) == '7' || text.at(x) == '8' ||
						text.at(x) == '9')
						return;
				}

				checked = true;
			}

			if (text.at(i) == '.' || text.at(i) == '0')
			{
				text.erase(text.begin() + i--);
			}
			else
			{
				foundPoint = false;
				checked = false;
				return;
			}
		}
	}
}