#pragma once
#include <random>       
#include <chrono> 
#include <set>;
#include "Deck.h";
#include <iostream>     // std::cout
#include <algorithm>    // std::shuffle
#include <array>

class CardFactory {
public:
	static CardFactory* const factory;
	std::vector<Card*> allCards;

	CardFactory() {
		if (factory != NULL) {
			throw IllegalState("A factory has already been created");
		}
		int i;
		for (i = 0; i < 20; i++) {
			allCards.push_back(new Blue);
		}
		for (i = 0; i < 18; i++) {
			allCards.push_back(new Chili);
		}
		for (i = 0; i < 16; i++) {
			allCards.push_back(new Stink);
		}
		for (i = 0; i < 14; i++) {
			allCards.push_back(new Green);
		}
		for (i = 0; i < 12; i++) {
			allCards.push_back(new soy);
		}
		for (i = 0; i < 10; i++) {
			allCards.push_back(new black);
		}
		for (i = 0; i < 8; i++) {
			allCards.push_back(new Red);
		}
		for (i = 0; i < 6; i++) {
			allCards.push_back(new garden);
		}
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		shuffle(allCards.begin(), allCards.end(), std::default_random_engine(seed));
	}

	static CardFactory* getFactory() {
		return factory;
	}

	Card* getCard(string type) {
		//cout <<'\n' << "geting Card" << '\n';
		Card* toReturn;
		for (int i = 0; i < allCards.size(); i++) {
			//cout << i << " ";
			if (allCards[i] != NULL && type == allCards[i]->getName()) {
				toReturn = allCards[i];
				allCards[i] = NULL;
				//cout << "Card Found"<<'\n';
				return toReturn;
			}
		}
		throw IllegalState("No such card available");
	}

	Deck* getDeck() {
		Deck* toReturn =new Deck;
		Card* current;
		for (int i = 0; i < allCards.size(); i++) {
			current = allCards[i];
			if (current != NULL) {
				toReturn->push_back(current);
				allCards[i] = NULL;
			}
		}
		return toReturn;
	}
};

CardFactory* const CardFactory::factory = new CardFactory();
