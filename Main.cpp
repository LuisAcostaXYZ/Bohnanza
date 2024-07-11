#include <stdlib.h>
#include <cstdlib>
#include <iomanip>
#include "Chain.h"
#include <iostream>
#include "Card.h"
#include"Deck.h";
#include "Player.h"
#include "TradeArea.h";
#include "DiscardPile.h";
#include "CardFactory.h";
#include "Table.h";
#include <sstream>
#include <fstream>
#include <string>


int main() {
	int selection = 0;
	cout << "New Game: Enter [1]" << '\n' << "Load Game: Enter [2]"<<'\n';
	while (selection != 1 && selection!=2) {
		cout << "Selection: ";
		cin >> selection;
	}
	CardFactory* factory = CardFactory::factory;
	Table* table = new Table;

	//Open Game
	if (selection == 2) {
		bool loaded=0;
		string fileName;
		while(loaded==0){
			cout << "Enter File name." << '\n';
			cin >> setw(9) >> fileName; //Get file name from user, max 5 characters + ".txt".
			ifstream input(fileName, ios::in); //Ex. Game1.txt
			if (!input) {
				cout << "Impossible to open\n"; //Cant find file with such name.
			}
			else {
				loaded = 1;
				cout << "Loading..." << '\n'; //File opened correctly.
			}
			table= new Table(input, factory);
		}
		table->currentlyPlaying = table->Player1;
	}
	//Start new Game
	else {
		Player* Player1, * Player2;
		string name;
		cout << "Enter Player 1's name: " << '\n';
		cin >> setw(20) >> name;
		Player1 = new Player(name);
		cout << "Enter Player 2's name: " << '\n';
		cin >> setw(20) >> name;
		Player2 = new Player(name);
		table = new Table(factory);
		table->gameDeck = table->gameDeck;
		for (int i = 0; i < 5; i++) {
			Player1->addCard(table->gameDeck->draw());
			Player2->addCard(table->gameDeck->draw());
		}
		table->Player1 = Player1;
		table->Player2 = Player2;
		table->currentlyPlaying = table->Player1;
	}

	//Game starts here.
	bool pause = 0;
	while (!table->gameDeck->empty()) { 
		if (pause) { //If player wants to pause the game
			bool created = 0;
			while (!created) {
				char fileName[9];
				cout << "Enter the name of the file where the game will be saved (max 9 char.)" << '\n';
				cin >> setw(9) >> fileName;
				std::ofstream file(fileName, ios::out); //attempt to create new file
				if (!file) {
					cout << "Couldn't create file" << '\n';
				}
				else {//Saving data in file
					cout << "Saving data" << '\n';
					file << "Player 1: " << table->Player1 << '\n'<< table->Player1->playerHand << ";" << '\n';
					file << "Max Chains: " << table->Player1->getMaxNumChains()<<'\n';
					file << "Player 2: " << table->Player2  << '\n' << table->Player2->playerHand << ";" << '\n';
					file << "Max Chains: " << table->Player2->getMaxNumChains()<<'\n';
					file << "Discard Pile: ";
					for (int i = 0; i < table->pile->size(); i++) {
						file << table->pile->at(i);
					}
					while (!table->pile->empty()) {
						table->pile->pop_back();
					}
					file << ";" << '\n';
					file << "Trade Area: "<<table->area<< ";" << '\n';
					//No need to save deck, since all the cards that are not somewhere else will go to Deck.
					file.close();
					created = 1; //All data saved
					cout << "Data saved" << '\n';
					exit(0);
				}
			}
		}


		//Player's turn 
		cout << '\n' << '\n' << '\n';
		cout << table->currentlyPlaying->getName() << " its your turn!" << '\n';
		cout << table << '\n';
		table->currentlyPlaying->addCard(table->gameDeck->draw());
		char show = 'x';
		while (!(show == 'Y' || show == 'N')) {
			cout << "Show your hand? (Y/N)" << '\n';
			cin >> show;
		}
		if (show == 'Y') {
			table->printHand(1);
		}

		if (!table->area->area.empty()) {
			int size = table->area->numCards();
			for (int x = 0; x < size;x++) {
				Card* fromTrade = table->area->area.front();
				table->area->area.pop_front();
				char addCard = 0;
				cout << "Add card " << fromTrade << "? (Y/N)" << '\n'; //Player 1 can add Cards in the trade are to their chains.
				cin >> addCard;
				while (!(addCard == 'Y' || addCard == 'N')) {
					cout << "Not a valid answer" << '\n';
					cout << "Add card " << fromTrade << "? (Y/N)" << '\n';
					cin >> addCard;
				}
				if (addCard == 'N') {
					table->pile->push_back(fromTrade); //If they dont want to add the card, the card is discarted 
				}
				else {
					bool added = 0;                                         //If yes
					for (int i = 0; i < table->currentlyPlaying->maxChains; i++) {
						if (table->currentlyPlaying->chains[i] != NULL && table->currentlyPlaying->chains[i]->getType() == fromTrade->getName()) {
							table->currentlyPlaying->chains[i]->add(fromTrade);   //First we try to add it to an existing chain of that class
							added = 1;
							break;
						}
					}
					if (added == 0) {   //If no such chain exists, we try creating a new one in an empty space
						for (int i = 0; i < table->currentlyPlaying->maxChains; i++) {
							if (table->currentlyPlaying->chains[i] == NULL) {
								table->currentlyPlaying->chains[i] = new Chain<decltype(fromTrade)>(fromTrade);
								added = 1;
								break;
							}
						}
					}
					if (added == 0 && table->currentlyPlaying->checkBuy()) {
						char c = 'x';
						while (!(c == 'Y' || c == 'N')) {
							cout << "Do you want to buy a third chain? (Y/N)" << '\n';
							cin >> c;
						}
						if (c == 'Y') {
							table->currentlyPlaying->buyThirdChain();
							table->currentlyPlaying->chains[2] = new Chain<decltype(fromTrade)>(fromTrade);
							added = 1;
						}
					}
					if (added == 0) { //If there is no space to add the card, player can sell a current chain to make space
						cout << "You can't add this card to your current chains." << '\n';
						cout << "Do you want to sell a chain to make space for this card? (Y/N)" << '\n';
						char sellChain = 0;
						cin >> sellChain;
						while (!(sellChain == 'Y' || sellChain == 'N')) {
							cout << "Not a valid answer" << '\n';
							cout << "Sell chain? (Y/N)" << '\n';
							cin >> sellChain;
						}
						if (sellChain == 'N') { //If they don't want to sell a chain the card is discarted.
							table->pile->push_back(fromTrade);
						}
						else { //If yes, the game displays the current chains with an index so Player can choose what to sell.
							for (int i = 0; i < table->currentlyPlaying->maxChains;i++) {
								cout << i << ": " << table->currentlyPlaying->chains[i] << '\n';
							}
							cout << "What chain do you want to sell? (C to cancel)" << '\n';
							sellChain = 'X';
							cin >> sellChain;
							while (sellChain != ('C') && (int(sellChain) - int('0') < -1 && int(sellChain) - int('0') > table->currentlyPlaying->maxChains)) {
								cout << "Not a valid answer" << '\n';
								cout << "Select chain? (C to cancel)" << '\n';
								cin >> sellChain;
							}
							if (sellChain == 'C') { //If they change their mind the card is discarted.
								table->pile->push_back(fromTrade);
								cout << "Card has been discarted." << '\n';
							}
							else {
								table->currentlyPlaying->coins += table->currentlyPlaying->chains[int(sellChain) - int('0')]->sell();
								table->currentlyPlaying->chains[int(sellChain) - int('0')] = NULL;
								cout << "Chain sold!" << '\n';
								table->currentlyPlaying->chains[int(sellChain) - int('0')] = new Chain<decltype(fromTrade)>(fromTrade);
								cout << "The card has been added to a new chain" << '\n';
							}
						}
					}
				}
			}
		}

		//Now we play the first card of the Hand one or two times;
		int Played = 0;
		while (Played < 2) {
			Card* Playing = table->currentlyPlaying->playerHand.play();
			cout << "Now playing " << Playing << '\n';
			bool added = 0;
			for (int i = 0; i < table->currentlyPlaying->maxChains; i++) {
				if (table->currentlyPlaying->chains[i] != NULL && table->currentlyPlaying->chains[i]->getType() == Playing->getName()) {
					table->currentlyPlaying->chains[i]->add(Playing);   //First we try to add the card to an existing chain of that class
					added = 1;
					cout << "Card added to a chain" << '\n';
					break;
				}
			}
			if (added == 0) {   //If no such chain exists, we try creating a new one in an empty space
				for (int i = 0; i < table->currentlyPlaying->maxChains; i++) {
					if (table->currentlyPlaying->chains[i] == NULL) {
						table->currentlyPlaying->chains[i] = new Chain<decltype(Playing)>(Playing);
						added = 1;
						cout << "New Chain created" << '\n';
						break;
					}
				}
			}
			if (added == 0 && table->currentlyPlaying->checkBuy()) {
				char c = 'x';
				while (!(c == 'Y' || c == 'N')) {
					cout << "Do you want to buy a third chain? (Y/N)" << '\n';
					cin >> c;
				}
				if (c == 'Y') {
					table->currentlyPlaying->buyThirdChain();
					table->currentlyPlaying->chains[2] = new Chain<decltype(Playing)>(Playing);
					added = 1;
				}
			}
			if (added == 0) {
				cout << "You must sell a chain" << '\n';
				for (int i = 0; i < table->currentlyPlaying->maxChains;i++) {
					cout << i << ": " << table->currentlyPlaying->chains[i] << '\n';
				}
				cout << "What chain do you want to sell?" << '\n';
				int index;
				cin >> index;
				while (index < 0 || index >= table->currentlyPlaying->maxChains) {
					cout << "That is not a chain" << '\n';
					cout << "What chain do you want to sell?" << '\n';
					cin >> index;
				}
				table->currentlyPlaying->coins += table->currentlyPlaying->chains[index]->sell();
				table->currentlyPlaying->chains[index] = NULL;
				cout << "Chain sold!" << '\n';
				table->currentlyPlaying->chains[index] = new Chain<decltype(Playing)>(Playing);
				cout << "The card has been added to a new chain" << '\n';
			}
			char selection = 0;
			if (Played == 0) {				//If the player has played only one card this turn they may play a second one
				while (!(selection == 'Y' || selection == 'N')) {
					cout << "Play another card? (Y/N/S -to show next card without playing it-)" << '\n'; //They also have the option to see the card before playing it.
					cin >> selection;
					if (selection == 'S') {
						cout << "Card: " << table->currentlyPlaying->playerHand.front() << '\n';
					}
				}
				if (selection == 'Y') {
					Played = 1;
				}
				else {
					Played = 2;
				}
			}
			else {
				Played = 2;
			}
		}

		cout << table->currentlyPlaying << '\n'; //The current state of the player is displayed

		//Here the player has the option to sell a chain;

		char selection = 0;
		while (!(selection == 'Y' || selection == 'N')) {
			cout << "Do you want to sell a chain? (Y/N/S -To show hand-)" << '\n'; //They also have the option to see the card before playing it.
			cin >> selection;
			if (selection == 'S') {
				table->currentlyPlaying->printHand(1);
			}
		}
		if (selection == 'Y') {
			bool doneSelling = 0;
			while (!doneSelling) {
				for (int i = 0; i < table->currentlyPlaying->maxChains;i++) {
					cout << i << ": ";
					if (table->currentlyPlaying->chains[i] != NULL) {
						cout << table->currentlyPlaying->chains[i] << '\n';
					}
					else {
						cout << '\n';
					}
				}
				selection = 'X';
				cout << "What chain do you want to sell? (C to cancell)" << '\n';
				cin >> selection;
				while (selection != 'C' && ((int(selection) - int('0') < -1 &&int(selection) - int(0) > table->currentlyPlaying->maxChains))) {
					cout << "Not a valid answer" << '\n';
					cout << "Select chain? (C to cancel)" << '\n';
					cin >> selection;
					if (table->currentlyPlaying->chains[int(selection - int('0'))] == NULL) {
						cout << "That chain is empty" << '\n';
						selection = 'X';
					}
				}
				if (selection == 'C') {
					doneSelling = 1;
				}
				else {
					table->currentlyPlaying->coins += table->currentlyPlaying->chains[int(selection) - int('0')]->sell();
					table->currentlyPlaying->chains[int(selection) - int('0')] = NULL;
					cout << "Chain sold!" << '\n';
				}
				selection = 'X';
				if (!doneSelling) {
					while (!selection == 'Y' || !selection == 'N') {
						cout << "Sell another chain?" << '\n';
						cin >> selection;
					}
					if (selection == 'N') { doneSelling = 1; }
				}

			}
		}


		//Now the player may discard a card;
		if (table->currentlyPlaying->playerHand.size() > 0) {
			char selection = 'x';
			while (!(selection == 'Y' || selection == 'N')) {
				cout << "Do you want to discard a card? (Y/N/S -show hand before deciding-)" << '\n';
				cin >> selection;
				if (selection == 'S') {
					table->currentlyPlaying->printHand(1);
				}
			}
			if (selection == 'Y') {
				for (int i = 0; i < table->currentlyPlaying->playerHand.size(); i++) {
					cout << i << ": " << table->currentlyPlaying->playerHand.at(i) << "  ";
				}
				cout << '\n';
				int index = -1;
				while (index<0 || index>table->currentlyPlaying->playerHand.size()) {
					cout << "What card do you want to discard?" << '\n';
					cin >> index;
				}
				table->pile->push_back(table->currentlyPlaying->playerHand.at(index));
				table->currentlyPlaying->playerHand.erase(table->currentlyPlaying->playerHand.begin() + index);
			}
		}


		//Draw three cards from the deck and place cards in the trade area
		for (int i = 0; i < 3; i++) {
			table->area->area.push_back(table->gameDeck->draw());
		}
		cout << "New cards added to trade area" << '\n';

		//while top card of discard pile matches an existing card in the trade area draw the 
		//topmost card from the discard pile and place it in the trade area

		bool compatible = 1;
		bool addedFromPile = 0;
		while (compatible && !(table->pile->empty())) {
			Card* top = table->pile->top();
			if (table->area->legal(top)) {
				table->area->area.push_back(table->pile->pickUp());
				addedFromPile = 1;
			}
			else {
				compatible = 0;
			}
		}
		if (addedFromPile) {
			cout << "Cards added from discard pile" << '\n';

		}
		cout << "Trade area" << '\n';
		cout << table->area << '\n';

		int areaSize = table->area->area.size();
		for (int i = 0; i < areaSize; i++) { //for all cards in the trade area								
				Card* temp = table->area->area.front();		   //player can decide to chain the card
				table->area->area.pop_front();
				bool added = 0;
				for (int x = 0; x < table->currentlyPlaying->maxChains;x++) {
					if (table->currentlyPlaying->chains[x]!=NULL && temp->getName() == table->currentlyPlaying->chains[x]->getType()) {
						table->currentlyPlaying->chains[x]->add(temp);
						added = 1;
						cout << "Card " << temp->getName() << " added to chain" << '\n';
						break;
					}
				}
				if (added == 0) {
					for (int x = 0; x < table->currentlyPlaying->maxChains;x++) {
						if (table->currentlyPlaying->chains[x] == NULL) {
							cout << "Create a new chain with " << temp->getName() << " from trade area? (Y/N)" << '\n';
							char c = 'x';
							cin >> c;
							while (!(c == 'Y' || c == 'N')) {
								cout << "Y/N?" << '\n';
								cin >> c;
							}
							if (c == 'Y') {
								table->currentlyPlaying->chains[x] = new Chain<decltype(temp)>(temp);
								added = 1;
							}
							break;
						}
					}
				}
				if (added == 0) {
					table->area->area.push_back(temp);
				}
			}

			//Draw to cards form Deck
			table->currentlyPlaying->addCard(table->gameDeck->draw());
			table->currentlyPlaying->addCard(table->gameDeck->draw());
	
			//If both player have completed their turn, they can may puse the game
			if (table->currentlyPlaying == table->Player2) {
				char c = 'x';
				while (!(c == 'Y' || c == 'N')) {
					cout << "Do you want to keep playing? (Y/N)" << '\n';
					cin >> c;
				}
				if (c == 'N') {
					pause = 1;
				}
			}
			//Now we switch the active player...
			table->switchPlayer();
	}
	if (table->Player1->getNumCoins() > table->Player1->getNumCoins()) {
		cout << table->Player1->getName() << " wins!" << '\n';
	}
	else {
		cout << table->Player2->getName() << " wins!" << '\n';
	}
	char exit;
	cout << "Enter to exit.";
	cin >> exit;
}

