#ifndef _HISTORYGENERATOR_H_
#define _HISTORYGENERATOR_H_

#include "rlutil.h"
#include "../vs2010Proj/vs2010Proj/jspline.h"
#include "../vs2010Proj/vs2010Proj/nation.h"
#include "../vs2010Proj/vs2010Proj/event.h"
#include "../vs2010Proj/vs2010Proj/HistoryData.h"

const int SCREEN_X = 81;
const int SCREEN_Y = 26;

const std::string SELECTION_ICON = "~";

//Menu text
const std::string MENU_TITLE     = "Creative Tech Project - History Generation";
const std::string MENU_FOOTER    = " Created by Jake Thorne ";
const std::string MENU_CONTROLS  = "Navigate with W & S, select an option with SpaceBar";

const std::string MENU_OPTION1   = "Start Generation";
const std::string MENU_OPTION2   = "Encyclopaedia";
const std::string MENU_OPTION3   = "About this";
const std::string MENU_OPTION4   = "Exit";

const std::string ABOUT_TITLE    = "About this program";
const std::string ABOUT_LINE1    = "This system has been created for my Creative Technology Project module.";
const std::string ABOUT_LINE2    = "It will simulate history for you then to look through in the built";
const std::string ABOUT_LINE3    = "in encyclopaedia.";
const std::string ABOUT_LINE4    = "";
const std::string ABOUT_LINE5    = "Press Space to return to the menu";

const std::string SETUP_TITLE    = "History setup";
const std::string SETUP_OPTION1  = "Years to simulate: ";
const std::string SETUP_OPTION2  = "Start nation count: ";
const std::string SETUP_OPTION3  = "Simulate";
const std::string SETUP_OPTION4  = "Back to menu";
const std::string SETUP_CONTROLS = "Adjust values with A & D";

//for start generation only
const int         NATION_LIMIT   = 10;

//Encyclopaedia config
const float		  ENCYCLO_START_WIDTH = 0.05f;
const float		  ENCYCLO_START_HEIGHT = 0.25f;

class HistoryGenerator
{
public:

	enum State
	{
		MENU,
		ENCYCLOPAEDIA,
		ABOUT,
		GENERATION,
		GENERATION_SETUP
	};

public:
	HistoryGenerator();
	~HistoryGenerator();

	//entry point from main
	bool Run();

private:
	void Initialise();

	//main update function
	bool Update();
	void HandleInput();

	//used to start generation process
	void Generate();

	//used to initialise display screens
	void InitialiseBorder();
	void InitialiseEncyclopaedia();

	//used to display information screens
	void DrawMenu();
	void DrawEncyclopaedia();
	void DrawAbout();

	void DrawSetupGeneration();
	void DrawGeneration();

	void DrawOutline();

	//function to remove unnecessary zeroes
	void RemoveZeroes(std::string& text);

private:
	State m_State;

	std::string m_screen[SCREEN_X][SCREEN_Y];

	//false if an event has happened that needs the screen to update
	bool m_updated;

	//Used to see what the user is going to select
	int m_selection;
	bool m_selected;

	//encyclopaedia header selection
	int m_encycloSelect;

	//setup generation variables
	int m_yearsToSimulate;
	int m_startNations;

	//generation variables
	bool m_generating;
	int m_currentYear;

	float m_generationIncrement; //used for the progress bar

	//Data storage and generation
	HistoryData m_History;
};

#endif

/*
	History class to hold the generated data
	Encyclopaedia page

*/














