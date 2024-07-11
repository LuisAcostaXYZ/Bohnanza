#include <iostream>
#pragma once
#include "Chain.h";
using namespace std;
#include "Card.h";
#include <vector>
#include "Hand.h";
#include <deque>
#include <stdlib.h>

class Player {
public:
	Hand playerHand;
	string name;
	int coins = 0;
	deque<Chain_Base*> chains;
	int maxChains = 2;
	Player(std::string& nom) {
		name = nom;
		chains.push_back(NULL);
		chains.push_back(NULL);
	}
	string getName() {
		return name;
	}
	int getNumCoins() {
		return coins;
	}
	Player& operator+=(const int toAdd) {
		cout << "Adding coins now" << '\n';
		coins += toAdd;
	}
	int getMaxNumChains() {
		if (maxChains == 2 || maxChains == 3) {
			return maxChains;
		}
		throw IllegalState("maxChains has illegal value");
	}
	int getNumChains() {
		return chains.size();
	}
	Chain_Base& operator[](int i) {
		return *chains[i];
	}
	void buyThirdChain() {
		if (maxChains != 2) {
			throw invalid_argument("maxChains is not 2");
		}
		if (getNumCoins() < 3) {
			throw NotEnoughCoins("Not enough Coins to buy the chain");
		}
		maxChains = 3;
		coins -= 3;
		chains.push_back(NULL);
	}
	void printHand(bool all) {
		if (!all) {
			cout << playerHand.top() << '\n';
		}
		else {
			cout << playerHand << '\n';
		}
	}
	friend ostream& operator<<(ostream& os, Player *dt) {
		os << dt->getName() << ";" << '\t' << " coins " << dt->getNumCoins() << '\n';
		for (int i = 0;i < dt->chains.size(); i++) {
			if (dt->chains.at(i) != NULL) {
				os << dt->chains.at(i);
			}
		}
		os << "." << '\n';
		return os;
	}
	Player(istream& text,CardFactory* factory) {
		char c;
		string ThisName;
		int ThisCoins;
		text >> c;
		while (c != ':') {
			text >> c;
		}
		text >> c;
		while (c != ';') {
			ThisName.push_back(c);
			text >> c;
		}
		name = ThisName;
		while (c != 's') {
			text >> c;
		}
		text >> ThisCoins;
		coins = ThisCoins;
		text >> c;
		int countingChains = 0;
		while (c != '.') {
			countingChains++;
			if (countingChains == 3) {
				maxChains = 3;
			}
			if (c == 'B') {
				for (int i = 0;i < 3;i++) {
					text >> c;
				}
				Chain<Blue*> *newChain= new Chain<Blue*>(text, factory);
				chains.push_back(newChain);
			}
			else if (c == 'C') {
				for (int i = 0;i < 4;i++) {
					text >> c;
				}
				Chain<Chili*>* newChain = new Chain<Chili*>(text, factory);
				chains.push_back(newChain);
			}
			else if (c == 'S') {
				for (int i = 0;i < 4;i++) {
					text >> c;
				}
				Chain<Stink*>* newChain = new Chain<Stink*>(text, factory);
				chains.push_back(newChain);
			}
			else if (c == 'G') {
				for (int i = 0;i < 4;i++) {
					text >> c;
				}
				Chain<Green*>* newChain = new Chain<Green*>(text, factory);
				chains.push_back(newChain);
			}
			else if (c == 's') {
				for (int i = 0;i < 2;i++) {
					text >> c;
				}
				Chain<soy*>* newChain = new Chain<soy*>(text, factory);
				chains.push_back(newChain);
			}
			else if (c == 'b') {
				for (int i = 0;i < 4;i++) {
					text >> c;
				}
				Chain < black* > * newChain = new Chain<black*>(text, factory);
				chains.push_back(newChain);
			}
			else if (c == 'R') {
				for (int i = 0;i < 2;i++) {
					text >> c;
				}
				Chain<Red*>* newChain = new Chain<Red*>(text, factory);
				chains.push_back(newChain);
			}
			else if (c == 'g') {
				for (int i = 0;i < 5;i++) {
					text >> c;
				}
				Chain<garden*>* newChain = new Chain<garden*>(text, factory);
				chains.push_back(newChain);
			}
			text >> c;
		}
		playerHand = Hand(text, factory);
		text >> c;
		int thisChains;
		
		while (c != ':') {
			text >> c;
		}
		text >> thisChains;
		maxChains = thisChains;
		while (chains.size() < maxChains) {
			chains.push_back(NULL);
		}
	}
	void addCard(Card* toAdd) {
		playerHand.push_back(toAdd);
	}

	bool checkBuy() {
		if (coins < 3 || maxChains != 2) {
			return false;
		}
		return true;
	}
};