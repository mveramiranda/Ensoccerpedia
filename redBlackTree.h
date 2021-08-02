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
			insertInside(root, newNode); // recursive function
			if (newNode->parent != nullptr)
			{
				balance(newNode);
			}
		}
	}
	Node* insertInside(Node* currNode, Node* node) //Inspiration from project 1 made by Eitan Kogutek
	{
		if (currNode == nullptr)
		{
			return node;
		}
		else if (node->season < currNode->season) // CORREGIR, no se que tipo de data usaremos para comparar
		{
			if (currNode->left == nullptr) // sets the parent if the new node is going to be set in the next iteration
			{
				node->parent = currNode;
			}
			currNode->left = insertInside(currNode->left, node);
		}
		else if (node->season > currNode->season) // CORREGIR, no se que tipo de data usaremos para comparar
		{
			if (currNode->right == nullptr) // sets the parent if the new node is going to be set in the next iteration
			{
				node->parent = currNode;
			}
			currNode->right = insertInside(currNode->right, node);
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