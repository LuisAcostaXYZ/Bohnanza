#include <iostream>
#pragma once
using namespace std;
#include "Card.h";
#include <deque>

class Hand : public std::deque<Card*> {
public:
	Hand(){}

	int getSize() { return size(); };

	Hand& operator+=(Card* toAdd) {
		push_back(toAdd);
		return *this;
	}

	Card* play() {
		Card *ToReturn = front();
		pop_front();
		return ToReturn;
	}

	Card* top() {
		return front();
	}

	Card* operator[](int index) {
		Card* ToReturn;
		std::vector<Card*> temp;
		for (int i = 0; i++; i < (size() - index) - 1) {
			temp.push_back(back());
			pop_back();
		}

		ToReturn = back();
		pop_back();
		while (!temp.empty()) {
			push_back(temp.back());
			temp.pop_back();
		}
		return ToReturn;
	}

	Hand(istream& text, CardFactory* factory) {
		char c;
		text >> c;
		while (c != ';') {
			if (c == 'B') {
				push_back(factory->getCard("Blue"));
			}
			else if (c == 'S') {
				push_back(factory->getCard("Stink"));
			}
			else if (c == 'C') {
				push_back(factory->getCard("Chili"));
			}
			else if (c == 'G') {
				push_back(factory->getCard("Green"));
			}
			else if (c == 's') {
				push_back(factory->getCard("soy"));
			}
			else if (c == 'b') {
				push_back(factory->getCard("black"));
			}
			else if (c == 'R') {
				push_back(factory->getCard("Red"));
			}
			else if (c == 'g') {
				push_back(factory->getCard("garden"));
			}
			text >> c;
		}
	}
	friend ostream& operator<<(ostream& os, Hand *dt) {
		int size = dt->getSize();
		for (int i = size-1; i >= 0; i--) {
			os << dt->at(i) << " ";
		}
		os << ";";
		return os;
	}
};
ostream& operator<<(ostream& os, Hand dt){
	int size = dt.getSize();
	for (int i = size - 1; i >= 0; i--) {
		os << dt.front() << " ";
		dt.pop_front();
	}
	return os;
}
