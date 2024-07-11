<h1>Bohnanza</h1>
<img src="https://upload.wikimedia.org/wikipedia/en/9/92/Bohnanza_game_box_art.jpeg" height="20%" width="20%" alt="Cover picture"/>

<h2>Description</h2>
This game is a digital adaptation of the card game <a href="https://en.wikipedia.org/wiki/Bohnanza">"Bohnanza"</a>. However, the original game is for 3-5 players; this version is adapted for a set number of two players. For this purpose, some of the rules were changed.
<br />


<h2>Languages and Utilities Used</h2>

- <b>C++</b> 

<h2>Rules</h2>

The game is played with a deck of cards of eight different types of beans (some more scarce than others), which two players place cards in chains, trade the cards and sell the chains in order to raise money. <br/>

The player obtains cards of all different types randomly from the deck, and so must engage in trade with the other player to be successful.<br/>

The cards have 8 different faces corresponding to different types of Beans (see Table below). The goal of the game is to chain-up the cards of same bean to gain coins. The player with the most coins at the end wins. The chains for the cards are formed by each player for all to see and there are a maximum of either two or three chains at any point per player. Each chain can only be formed with a single type of Bean. <br/>
Each player is dealt a hand of five cards to start and the remaining cards form a draw deck. The rule is that cards in a player’s hand need to be kept sorted. Cards will be placed on a discard pile during the game. Cards in the hand are kept hidden. <br/>

Cards in trading areas and chains are visible to all players. The discard pile is face up, but only the top card is visible. The game proceeds with the players taking turns. During their turn, each player does the following:
<br/>
1. If the other player has left cards in the trade area from the previous turn (in Step 5), the player may add these cards to his/her chains or discard them.
2. The player then plays the topmost card from his/her hand. The card must be added to a chain with the same beans. If the player has currently no such chain on the table, an old chain on the table will have to be tied and sold, and a new chain must be started. If the chain has not reached a sufficient length, a player may receive 0 coins.
3. The player has the option to repeat Step 2.
4. Then, the player has the option of discarding one arbitrary card (in any order) from his/her hand on the discard pile face up.
5. The player draws three cards from the draw deck and places them in the trade area. Next, the player draws cards from the discard pile as long as the card matches one of the beans in the trade area. Once the top card does not match or the pile is empty, the player can either chain the cards or leave them in the trade area for the next player. As in Step 2, if the player has currently no such chain matching the bean of the card, an old chain on the table will have to be tied and sold, and then a new chain is started.
6. The turn ends with the player drawing always two cards from the deck and placing them at the back of his/her hand. </br>

Whenever a player ties a chain and sells it (Steps 2,3 or 5), the player receives coins in trade for the chain.</br>
A player can purchase the right to form a third chain for three coins. No more than three chains can be formed simultaneously by a player during the game.</br>
The game ends when the deck becomes empty.</br>
Chains of different length and different beans have different value as shown below:</br>
<p align="center">
<img src="https://i.imgur.com/i7gXYnf.png" height="80%" width="80%" alt="Table of bean values"/>
<br />


<h2>Program walk-through:</h2>

The game starts with two options, start a new game or load an existing one from a .txt file that uses the game's save format.
<p align="center">
<img src="https://i.imgur.com/Diu78aP.png" height="50%" width="50%" alt="Start options"/>
</p>
If you decide to start a new game, you start by selecting the name of the two players. A screen with the initial conditions (or current conditions if loading an existing game) would then be displayed.
<br />
<p align="center">
<img src="https://i.imgur.com/kn8hQ7K.png" height="50%" width="50%" alt="Start screen"/>
</p>
At the begining of your turn you will have the option to look at your hand if you desire to do so. Then the first card on your hand will be played. You will then have the option to play a second card if you want to do so. At this point you can sell a chain if you want to. The next step is to discard a card if you wish to do so. Then, three cards are drawn into the trade area. The player can start a new chain with this cards if they want to do so.
<p align="center">
<img src="https://i.imgur.com/UcjOnNQ.png" height="50%" width="50%" alt="Player 1's turn"/>
</p>
Then it is the turn of player 2, they follow the same steps as player 1.
<p align="center">
<img src="https://i.imgur.com/GHAWLwZ.png" height="50%" width="50%" alt="Status screen at the start of player 2's turn"/>
<img src="https://i.imgur.com/92RimXP.png" height="50%" width="50%" alt="Player 2's turn"/>
</p>
The game keeps going in the same way until the deck is empty.

