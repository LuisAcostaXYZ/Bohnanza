#include <iostream>
#pragma once
using namespace std;
#include "Player.h";
#include "Deck.h";
#include "TradeArea.h";
#include "DiscardPile.h";
#include <stdlib.h>

class Table {
public:
	Player *Player1, *Player2;
	Deck *gameDeck;
	DiscardPile *pile;
	TradeArea *area;
	Player *currentlyPlaying;
	void printHand(bool all) {
		currentlyPlaying->printHand(all);

	}
	friend ostream& operator<<(ostream& os, Table *dt) {
		os << "Player 1:" << '\n' << dt->Player1 << '\n' <<"Player 2:" << '\n'<< dt->Player2 << '\n';
		os << "Discard Pile:" << '\n' << dt->pile << '\n' << "Trading Area:" << '\n' << dt->area << '\n';
		return os;
	}
	Table(istream& text, CardFactory* factory) {
		cout << "Reading" << '\n';
		Player1 = new Player(text, factory);
		cout << "Player 1 data found" << '\n';
		Player2 = new Player(text, factory);
		cout << "Player 2 data found" << '\n';
		char c = 0;
		while (c != ':') {
			text >> c;
		}
		pile = new DiscardPile(text, factory);
		cout << "Discard pile data found" << '\n';
		while (c != ':') {
			text >> c;
		}
		area = new TradeArea(text, factory);
		cout << "Trade area data found" << '\n';
		gameDeck = factory->getDeck();
		cout << "Starting game" << '\n';
	}
	Table(CardFactory* factory) {
		gameDeck = factory->getDeck();
		pile = new DiscardPile;
		area = new TradeArea;
	}
	Table(){}

	void switchPlayer() {
		if (currentlyPlaying == Player1) {
			currentlyPlaying = Player2;
		}
		else {
			currentlyPlaying = Player1;
		}
	}
};
