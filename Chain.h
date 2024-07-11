#include <typeinfo>
#include <iostream>
using namespace std;
#include "Card.h";
#include <vector>
#include <stdexcept>
#include "Exceptions.h";
#include "CardFactory.h";
#include "DiscardPile.h";
#pragma once

class Chain_Base {
public:
	virtual int sell() = 0;
	virtual Chain_Base& operator +=(Card* x) = 0;
	virtual void print() = 0;
	virtual void print(ostream&) = 0;
	virtual string getType() = 0;
	virtual void add(Card*)=0;
};



template <class T> class Chain:public Chain_Base {
	vector<T> thisChain;
public:
	Chain<T>(Card* toAdd) {
		thisChain.push_back(toAdd);
	}
	string getType(){
		return thisChain.front()->getName();
	}
	int sell() {
		if (thisChain.empty()) {
			throw IllegalState("Chain is empty");
		}
		int toReturn = thisChain.front()->getCardsPerCoin(thisChain.size());
		cout << "Selling for " << toReturn << " coins" << '\n';
		return toReturn;
	};
	Chain<T>& operator+=(Card* x) {
		if (thisChain.size() && x->getName() != thisChain.front()->getName()) {
			throw IllegalTypeException("Card type does not match chain");
		}
		T newX = dynamic_cast<const T>(x);
		thisChain.push_back(newX);
		//cout << thisChain.size() << '\n'; 
	}
	void add(Card* toAdd) {
		if (thisChain.size() && toAdd->getName() != thisChain.front()->getName()) {
			throw IllegalTypeException("Card type does not match chain");
		}
		T newAdd = dynamic_cast<const T>(toAdd);
		thisChain.push_back(newAdd);
	}
	void print() {
		if (!thisChain.empty()) {
			cout << thisChain.front()->getName()<<'\t';
			for (int i = 0; i < thisChain.size(); i++) {
				cout << thisChain.at(i)<<" ";
			}
			cout << ";" << '\n';
		}
	}
	void print(ostream& out) {
		if (!thisChain.empty()) {
			out << thisChain.front()->getName() << '\t';
			for (int i = 0; i < thisChain.size(); i++) {
				out << thisChain.at(i) << " ";
			}
			out << ";" << '\n';
		}
	}
	Chain<T>(istream& text, CardFactory* factory) {
		char c;
		text >> c;
		while (c != ';') {
			if (c == 'B') {
				T newX = dynamic_cast<const T>((factory->getCard("Blue")));
				thisChain.push_back(newX);
			}
			else if (c == 'C') {
				T newX = dynamic_cast<const T>((factory->getCard("Chili")));
				thisChain.push_back(newX);
			}
			else if (c == 'S') {
				T newX = dynamic_cast<const T>((factory->getCard("Stink")));
				thisChain.push_back(newX);
			}
			else if (c == 'G') {
				T newX = dynamic_cast<const T>((factory->getCard("Green")));
				thisChain.push_back(newX);
			}
			else if (c == 's') {
				T newX = dynamic_cast<const T>((factory->getCard("soy")));
				thisChain.push_back(newX);
			}
			else if (c == 'b') {
				T newX = dynamic_cast<const T>((factory->getCard("black")));
				thisChain.push_back(newX);
			}
			else if (c == 'R') {
				T newX = dynamic_cast<const T>((factory->getCard("Red")));
				thisChain.push_back(newX);
			}
			else if (c == 'g') {
				T newX = dynamic_cast<const T>((factory->getCard("garden")));
				thisChain.push_back(newX);
			}
			text >> c;
		}
	}
};

std::ostream& operator<<(std::ostream& os, Chain_Base* a )
{
     a->print(os);
     return os;
}






