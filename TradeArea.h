#include <iostream>
#include <deque>
using namespace std;
#include <list>
#include "Card.h";
#pragma once

class TradeArea {
public:
	TradeArea(){}
	list<Card*> area;

	TradeArea& operator+=(Card* toAdd) {
		area.push_back(toAdd);
		return *this;
	}

	bool legal(Card* toCheck) {
		list<Card*> temp;
		bool present = 0;
		while (!area.empty()) {
			if (area.back()->getName() == toCheck->getName()) {
				present = 1;
				break;
			}
			temp.push_back(area.back());
			area.pop_back();
		}
		while (!temp.empty()) {
			area.push_back(temp.back());
			temp.pop_back();
		}
		return present;
	}
	Card* trade(string toTake) {
		list<Card*> temp;
		bool present = 0;
		Card* toReturn;
		while (!area.empty()) {
			if (area.back()->getName() == toTake) {
				toReturn = area.back();
				area.pop_back();
				return toReturn;
			}
			temp.push_back(area.back());
			area.pop_back();
		}
		while (!temp.empty()) {
			area.push_back(area.back());
			temp.pop_back();
		}
		throw std::invalid_argument("Type of card not in the trade area.");
	}
	int numCards() {
		return area.size();
	};

	friend ostream& operator<<(ostream& os, TradeArea* x) {
		for (int i = 0; i < x->area.size(); i++) {
			Card* temp = x->area.front();
			x->area.pop_front();
			os << temp<<" ";
			x->area.push_back(temp);
		}
		return os;
	}
	TradeArea(istream& text, CardFactory* factory) {
		char c;
		text >> c;
		while (c != ';') {
			if (c == 'B') {
				area.push_back(factory->getCard("Blue"));
			}
			else if (c == 'S') {
				area.push_back(factory->getCard("Stink"));
			}
			else if (c == 'C') {
				area.push_back(factory->getCard("Chili"));
			}
			else if (c == 'G') {
				area.push_back(factory->getCard("Green"));
			}
			else if (c == 's') {
				area.push_back(factory->getCard("soy"));
			}
			else if (c == 'b') {
				area. push_back(factory->getCard("black"));
			}
			else if (c == 'R') {
				area.push_back(factory->getCard("Red"));
			}
			else if (c == 'g') {
				area.push_back(factory->getCard("garden"));
			}
			text >> c;
		}
	}
};
