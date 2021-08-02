#include "Hash.h"
#include <iostream>
#include <iomanip>

Hash::Hash(int size) {
	this->SIZE = size;
	table = new map< pair< string, string>, Game>[SIZE];
}

int Hash::HashCode(int input) {
	return input % SIZE;
}

void Hash::Insert(int season, Game game) {
	int index = HashCode(season);
	table[index][make_pair(game.homeTeam, game.awayTeam)] =  game;
}

Game Hash::Search(int season, string homeTeam, string awayTeam) {
	int index = HashCode(season);
	return table[index][make_pair(homeTeam, awayTeam)];
}

void Hash::Search(int season, string team) {
	int index = HashCode(season);
	auto teamRecord = table[index];
	team = "\"" + team + "\"";

	int goalsFor = 0;
	int goalsAgainst = 0;
	int totalGames = 0;

	for (auto& it : teamRecord) {
		if (it.first.first == team || it.first.second == team) {
			totalGames++;
			if (it.first.first == team) {
				goalsFor += it.second.hGoals;
				goalsAgainst += it.second.aGoals;
			}
			if (it.first.second == team) {
				goalsFor += it.second.aGoals;
				goalsAgainst += it.second.hGoals;
			}
		}
	}

	//set precision to display only 2 decimals. snippet from 
	//https://stackoverflow.com/questions/22515592/how-to-use-setprecision-in-c
	cout << fixed << showpoint;
	cout << setprecision(2);

	cout << endl;

	cout << team.substr(1, team.size() - 2) << " record for the " << season << "-" << season + 1 << "season : " << endl;
	cout << "Goals for: " << goalsFor << endl;
	cout << "Goals against: " << goalsAgainst << endl;
	cout << "Goal difference: " << goalsFor - goalsAgainst << endl;
	cout << "Average goals scored: " << (float)goalsFor / (float)totalGames << endl;
	cout << "Average goals received: " << (float)goalsAgainst / (float)totalGames << endl;

}