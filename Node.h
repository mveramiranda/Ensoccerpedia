#pragma once
#include <map>
#include <string>
#include "Game.h"
using namespace std;

class Node
{
public:
	int season;
	map<pair<string, string>, Game> data;

	bool black = false;

	Node* parent = nullptr;
	Node* left = nullptr;
	Node* right = nullptr;

	Node(int season, Game game)
	{
		this->season = season;
		data.emplace(make_pair(game.homeTeam, game.awayTeam), game);
	}

	void changeColor(bool color)
	{
		black = color;
	}
};