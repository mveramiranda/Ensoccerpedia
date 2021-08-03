#include "Hash.h"
#include <iostream>
#include <iomanip>

Hash::Hash(int size) {
	this->SIZE = size;
	//initializes a new table with the given size
	table = new map< pair< string, string>, Game>[SIZE];
}

int Hash::HashCode(int input) {
	//the hash function is the modulo of the input and the table size
	return input % SIZE;
}

void Hash::Insert(int season, Game game) {
	//hashes the season year to a table index
	int index = HashCode(season);

	//inserts into the map of the given index the game
	table[index][make_pair(game.homeTeam, game.awayTeam)] =  game;
}

Game Hash::Search(int season, string homeTeam, string awayTeam) {
	//hashes the season year to a table index
	int index = HashCode(season);

	//returns the game found at the table with a given index
	return table[index][make_pair(homeTeam, awayTeam)];
}

void Hash::Search(int season, string team) {
	//hashes the season year to a table index
	int index = HashCode(season);
	auto teamRecord = table[index];
	team = "\"" + team + "\"";

	int goalsFor = 0;
	int goalsAgainst = 0;
	int totalGames = 0;

	//updates the team record by iterating through all their games in the specified season
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

	//prints out the team stats in the given season

	cout << team.substr(1, team.size() - 2) << " record for the " << season << "-" << season + 1 << "season : " << endl;
	cout << "Goals for: " << goalsFor << endl;
	cout << "Goals against: " << goalsAgainst << endl;
	cout << "Goal difference: " << goalsFor - goalsAgainst << endl;
	cout << "Average goals scored: " << (float)goalsFor / (float)totalGames << endl;
	cout << "Average goals received: " << (float)goalsAgainst / (float)totalGames << endl;

}