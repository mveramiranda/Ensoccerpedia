#pragma once
#include <string>
using namespace std;

class Game {
	private:
		string date;
		int season;
		string homeTeam;
		string awayTeam;
		int hGoals;
		int aGoals;
	public: 
		Game(string date, int season, string homeTeam, string awayTeam, int hGoals, int aGoals) :
			date(date), season(season), homeTeam(homeTeam), awayTeam(awayTeam), hGoals(hGoals), aGoals(aGoals) {};
};