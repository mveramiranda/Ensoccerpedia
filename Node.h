#pragma once
#include <map>
#include <string>
#include "Game.h"
using namespace std;

//red-black tree node
class Node
{
public:
	int season;
	map<pair<string, string>, Game> data;

	bool black = false;

	Node* parent = nullptr;
	Node* left = nullptr;
	Node* right = nullptr;

	Node(int season, Game game);
	void changeColor(bool color);
};