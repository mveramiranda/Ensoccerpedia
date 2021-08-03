#pragma once
#include <list>
#include <map>
#include <utility>
#include <string>
#include "Game.h"
using namespace std;

//hash table implementation
class Hash {
	private:
		//size of the hash table
		int SIZE;

		//hash table is an array of maps whose keys are the home and away teams and the value is a game object
		//this allows to handle the "collisions" which are expected and needed since every season has multiple games
		map< pair< string, string>, Game> *table;

		//hash code function
		int HashCode(int input);

	public: 
		//constructor that initilizes the hash table with a given size
		Hash(int size);

		//inserts games on the table
		void Insert(int season, Game game);

		//search functions
		void Search(int season, string team); //search feature for option 2
		Game Search(int season, string homeTeam, string awayTeam); //search feature for option 1
};