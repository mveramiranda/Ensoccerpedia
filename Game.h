#pragma once
#include <string>
using namespace std;

//game structure to store a specific game's information
struct Game {
		string date;
		int season;
		string homeTeam;
		string awayTeam;
		int hGoals;
		int aGoals;

		//constructors
		Game() : date(""), season(0), homeTeam(""), awayTeam(""), hGoals(0), aGoals(0) {};
		Game(string date, int season, string homeTeam, string awayTeam, int hGoals, int aGoals) :
			date(date), season(season), homeTeam(homeTeam), awayTeam(awayTeam), hGoals(hGoals), aGoals(aGoals) {};
};