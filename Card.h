#include <iostream>
#pragma once
using namespace std;


class Card {
public:
	virtual int getCardsPerCoin(int cards)=0;
	virtual string getName()=0;
	virtual void print(ostream& out)=0;
};


class Blue : public Card {
public:
	string getName() {
		return "Blue";
	}
	void print(ostream& out) {
		out << "B" << '\n';
	}
	int getCardsPerCoin(int cards) {
		if (cards > 9) {
			return 4;
		}
		if (cards > 7) {
			return 3;
		}
		if (cards > 5) {
			return 2;
		}
		if (cards > 3) {
			return 1;
		}
		return 0;
	}
};

class Chili : public Card {
public:
	string getName() {
		return "Chili";
	}
	void print(ostream& out) {
		out << "C" << '\n';
	}
	int getCardsPerCoin(int cards) {
		if (cards > 8) {
			return 4;
		}
		if (cards > 7) {
			return 3;
		}
		if (cards > 5) {
			return 2;
		}
		if (cards > 2) {
			return 1;
		}
		return 0;
	}
};

class Stink : public Card {
public:
	string getName() {
		return "Stink";
	}
	void print(ostream& out) {
		out << "S" << '\n';
	}
	int getCardsPerCoin(int cards) {
		if (cards > 7) {
			return 4;
		}
		if (cards > 6) {
			return 3;
		}
		if (cards > 4) {
			return 2;
		}
		if (cards > 2) {
			return 1;
		}
		return 0;
	}
};

class Green : public Card {
public:
	string getName() {
		return "Green";
	}
	void print(ostream& out) {
		out << "G" << '\n';
	}
	int getCardsPerCoin(int cards) {
		if (cards > 6) {
			return 4;
		}
		if (cards > 5) {
			return 3;
		}
		if (cards > 4) {
			return 2;
		}
		if (cards > 2) {
			return 1;
		}
		return 0;
	}
};

class soy : public Card {
public:
	string getName() {
		return "soy";
	}
	void print(ostream& out) {
		out << "s" << '\n';
	}
	int getCardsPerCoin(int cards) {
		if (cards > 6) {
			return 4;
		}
		if (cards > 5) {
			return 3;
		}
		if (cards > 3) {
			return 2;
		}
		if (cards > 1) {
			return 1;
		}
		return 0;
	}
};

class black : public Card {
public:
	string getName() {
		return "black";
	}
	void print(ostream& out) {
		out << "b" << '\n';
	}
	int getCardsPerCoin(int cards) {
		if (cards > 5) {
			return 4;
		}
		if (cards > 4) {
			return 3;
		}
		if (cards > 3) {
			return 2;
		}
		if (cards > 1) {
			return 1;
		}
		return 0;
	}
};

class Red : public Card {
public:
	string getName() {
		return "Red";
	}
	void print(ostream& out) {
		out << "R" << '\n';
	}
	int getCardsPerCoin(int cards) {
		if (cards > 4) {
			return 4;
		}
		if (cards > 3) {
			return 3;
		}
		if (cards > 2) {
			return 2;
		}
		if (cards > 1) {
			return 1;
		}
		return 0;
	}
};

class garden : public Card {
public:
	string getName() {
		return "garden";
	}
	void print(ostream& out) {
		out << "g" << '\n';
	}
	int getCardsPerCoin(int cards) {
		if (cards > 2) {
			return 3;
		}
		if (cards > 1) {
			return 2;
		}
		return 0;
	}
};

ostream& operator<<(ostream& os, Card* x) {
	if (x->getName() == "Blue") {
		os << "B";
	}
	else if (x->getName() == "Chili") {
		os << "C";
	}
	else if (x->getName() == "Stink") {
		os << "S";
	}
	else if (x->getName() == "Green") {
		os << "G";
	}
	else if (x->getName() == "soy") {
		os << "s";
	}
	else if (x->getName() == "black") {
		os << "b";
	}
	else if (x->getName() == "Red") {
		os << "R";
	}
	else if (x->getName() == "garden") {
		os << "g";
	}
	return os;
}










