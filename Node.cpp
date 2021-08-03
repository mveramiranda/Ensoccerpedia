#pragma once
#include <map>
#include <string>
#include "Game.h"
#include "Node.h"
using namespace std;

Node::Node(int season, Game game)
{
	this->season = season;
	data.emplace(make_pair(game.homeTeam, game.awayTeam), game);
}
void Node::changeColor(bool color)
{
	black = color;
}