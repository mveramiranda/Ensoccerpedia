#pragma once
#include <list>
#include <map>
#include <utility>
#include <string>
#include "Game.h"
using namespace std;

class Hash {
	private:
		int SIZE;
		map< pair< string, string>, Game> *table;

	public: 
		Hash(int size);
		int HashCode(int input);
		void Insert(int season, Game game);
		void Search(int season, string team); //search feature for option 2
		Game Search(int season, string homeTeam, string awayTeam); //search feature for option 1
};