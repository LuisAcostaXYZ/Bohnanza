#include <iostream>
using namespace std;
#include <vector>
#include "Card.h";
#pragma once;
#include "Deck.h";




class DiscardPile : public std::vector<Card*> {
public:
	DiscardPile() {};

	DiscardPile& operator+=(Card* toDiscard) {
		push_back(toDiscard);
		return *this;
	}

	Card* pickUp() {
		Card* toReturn = back();
		this->pop_back();
		return toReturn;
	}

	Card* top() {
		return back();
	}

	friend ostream& operator<<(ostream& os, DiscardPile *x) {
		if (x->empty()) {
			return os;
		}
		os << x->top()<<'\n';
		return os;
	}

	DiscardPile(istream& text, CardFactory *factory) {
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
};