#pragma once
#include <map>
#include <iomanip>
#include <string>
#include <queue>
#include <vector>
#include "Game.h"
#include "Node.h"
using namespace std;

//red-black tree implementation
class redBlackTree
{
public:
	Node* root = nullptr;

	void insert(int season, Game game);
	Node* insertInside(Node* currNode, Node* node, Game game); //Inspiration from project 1 made by Eitan Kogutek
	void balance(Node* node);
	Game search(int season, string home, string visitor);
	Game searchIterator(int season, string home, string visitor, Node* node);

	void search(int season, string team);

	void searchIterator(int season, string team, Node* node);


	void levelOrder();

	//Rotations
	void rotationLL(Node* node);
	void rotationRR(Node* node);

};