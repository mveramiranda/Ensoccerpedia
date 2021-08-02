#pragma once
#include <map>
#include <string>
#include <queue>
#include <vector>
#include "Game.h"
#include "Node.h"
using namespace std;

class redBlackTree
{
public:
	Node* root = nullptr;

	void insert(int season, Game game)
	{
		if (root == nullptr) //empty tree
		{
			Node* newNode = new Node(season, game);
			newNode->changeColor(true);
			root = newNode;
		}
		else
		{
			Node* newNode = new Node(season, game);
			insertInside(root, newNode, game); // recursive function
			if (newNode->parent != nullptr)
			{
				balance(newNode);
			}
		}
	}
	Node* insertInside(Node* currNode, Node* node, Game game) //Inspiration from project 1 made by Eitan Kogutek
	{
		if (currNode == nullptr)
		{
			return node;
		}
		else if (currNode->season == node->season)
		{
			currNode->data.emplace(make_pair(game.homeTeam, game.awayTeam), game);
		}
		else if (node->season < currNode->season) // CORREGIR, no se que tipo de data usaremos para comparar
		{
			if (currNode->left == nullptr) // sets the parent if the new node is going to be set in the next iteration
			{
				node->parent = currNode;
			}
			currNode->left = insertInside(currNode->left, node, game);
		}
		else if (node->season > currNode->season) // CORREGIR, no se que tipo de data usaremos para comparar
		{
			if (currNode->right == nullptr) // sets the parent if the new node is going to be set in the next iteration
			{
				node->parent = currNode;
			}
			currNode->right = insertInside(currNode->right, node, game);
		}
		return currNode;
	}
	void balance(Node* node) // inspired by algorithmtutor https://algorithmtutor.com/Data-Structures/Tree/Red-Black-Trees/
	{
		Node* uncle;
		while (node->parent->black == false)
		{
			if (node->parent == node->parent->parent->right)
			{
				uncle = node->parent->parent->left;
				if (uncle != nullptr)
				{
					if (uncle->black == false) // 3.1
					{
						uncle->changeColor(true);
						node->parent->changeColor(true);
						node->parent->parent->changeColor(false);
						node = node->parent->parent;
					}
					else
					{
						if (node == node->parent->left)
						{
							node = node->parent;
							rotationLL(node);
						}
						node->parent->changeColor(true);
						node->parent->parent->changeColor(false);
						rotationRR(node->parent->parent);
					}
				}
				else
				{
					if (node == node->parent->left)
					{
						node = node->parent;
						rotationLL(node);
					}
					node->parent->changeColor(true);
					node->parent->parent->changeColor(false);
					rotationRR(node->parent->parent);
				}
			}
			else
			{
				uncle = node->parent->parent->right;
				if (uncle != nullptr)
				{
					if (uncle->black == false)
					{
						uncle->changeColor(true);
						node->parent->changeColor(true);
						node->parent->parent->changeColor(false);
						node = node->parent->parent;
					}
					else
					{
						if (node == node->parent->right)
						{
							node = node->parent;
							rotationRR(node);
						}
						node->parent->changeColor(true);
						node->parent->parent->changeColor(false);
						rotationLL(node->parent->parent);
					}
				}
				else
				{
					if (node == node->parent->right)
					{
						node = node->parent;
						rotationRR(node);
					}
					node->parent->changeColor(true);
					node->parent->parent->changeColor(false);
					rotationLL(node->parent->parent);
				}
			}
			if (node == root)
			{
				break;
			}
		}
		root->changeColor(true);
	}
	Game search(int season, string home, string visitor)
	{
		Game temp = searchIterator(season, home, visitor, root);
		return temp;
	}
	Game searchIterator(int season, string home, string visitor, Node* node)
	{
		if (node->season == season)
		{
			auto iter = node->data.begin();
			pair<string, string> searchGame = make_pair(home, visitor);
			for (; iter != node->data.end(); ++iter)
			{
				if (iter->first == searchGame)
				{
					return iter->second;
				}
			}
		}
		if (node->season > season)
		{
			return searchIterator(season, home, visitor, node->left);
		}
		else if (node->season < season)
		{
			return searchIterator(season, home, visitor, node->right);
		}
	}

	void search(int season, string team) {
		searchIterator(season, team, root);
	}

	void searchIterator(int season, string team, Node* node) {
		if (node->season == season)
		{
			team = "\"" + team + "\"";
			int goalsFor = 0;
			int goalsAgainst = 0;
			int totalGames = 0;
			for (auto& it : node->data) {
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

			cout << team.substr(1, team.size() - 2) << " record for the " << season << "-" << season + 1 << " season : " << endl;
			cout << "Goals for: " << goalsFor << endl;
			cout << "Goals against: " << goalsAgainst << endl;
			cout << "Goal difference: " << goalsFor - goalsAgainst << endl;
			cout << "Average goals scored: " << (float)goalsFor / (float)totalGames << endl;
			cout << "Average goals received: " << (float)goalsAgainst / (float)totalGames << endl;
		}
		if (node->season > season)
		{
			 searchIterator(season, team, node->left);
		}
		else if (node->season < season)
		{
			 searchIterator(season, team, node->right);
		}
	}


	void levelOrder() // inspired by module4 stepik solution
	{
		queue<Node*> queue;
		int levelNum = 1;
		if (root == nullptr) { return; }

		queue.push(root);
		while (!queue.empty())
		{
			int size = queue.size();
			vector<int> level;
			for (int i = 0; i < size; i++)
			{
				Node* node = queue.front();
				level.push_back(node->season);
				queue.pop();
				if (node->left != nullptr)
				{
					queue.push(node->left);
				}
				if (node->right != nullptr)
				{
					queue.push(node->right);
				}
			}
			cout << "Level: " << levelNum << endl;
			for (int item : level)
			{
				cout << item << " ";
			}
			cout << endl;
			levelNum++;
		}
	}

	//Rotations
	void rotationLL(Node* node)
	{
		Node* temp = node->left;
		node->left = temp->right;
		if (node->left != nullptr)
		{
			node->left->parent = node;
		}
		temp->parent = node->parent;
		if (node->parent == nullptr)
		{
			root = temp;
		}
		else if (node == node->parent->left)
		{
			node->parent->left = temp;
		}
		else
		{
			node->parent->right = temp;
		}
		temp->right = node;
		node->parent = temp;
	}
	void rotationRR(Node* node)
	{
		Node* temp = node->right;
		node->right = temp->left;
		if (node->right != nullptr)
		{
			node->right->parent = node;
		}
		temp->parent = node->parent;
		if (node->parent == nullptr)
		{
			root = temp;
		}
		else if (node == node->parent->left)
		{
			node->parent->left = temp;
		}
		else
		{
			node->parent->right = temp;
		}
		temp->left = node;
		node->parent = temp;
	}

};