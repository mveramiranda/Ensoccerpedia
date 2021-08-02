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
		list < map< pair< string, string>, Game> > *table;

	public: 
		void Insert(Game game);
		void Search(int season, string homeTeam, string awayTeam);
};