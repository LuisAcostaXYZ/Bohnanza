#include <iostream>
using namespace std;
#include <vector>;
#pragma once
#include "card.h";


class Deck : public std::vector<Card*>{
public:
	Card* draw() {
		Card* toReturn = at(size() - 1);
		this->pop_back();
		return toReturn;
	}
	friend ostream& operator<<(ostream& os, Deck x) {
		int mySize = x.size();
		for (int i=0; i < mySize; i++) {
			os << x.at(i);
		}
		os << ";" << '\n';
		return os;
	}
};


