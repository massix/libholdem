/* libholdem - just a way to waste some time creating a library for Texas Hold'em games
 * Copyright (C) 2011 Massimo Gengarelli <massimo.gengarelli@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef _HOLDEM_H_
#define _HOLDEM_H_

/* holdem.h library description */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/** Typedefs and structures **/
typedef unsigned int uint;

struct __card {
	uint 	value;
	char	seed;
};

/** looks like a linked list, behaves like a stack **/
struct __deck {
	struct __card * current;
	struct __deck * next;
};



enum {
	HEARTS = 'H',
	DIAMONDS = 'D',
	CLUBS = 'C',
	SPADES = 'S'
};

typedef struct __card * Card;
typedef struct __deck * Deck;

/** a standard player **/
struct __player {
	char * 	name;
	uint	credit;
	Card	hand[2];

	uint	fold;
	uint	last_bet;
};

typedef struct __player * Player;

/** a play **/
struct __play {
	Player	players[5];
	uint	playing;

	Deck	deck;

	Card	flop[3];
	Card	river;
	Card	turn;

	uint	pot;

	uint	ante;
	uint	small_blind;
	uint	big_blind;

	uint	dealer;
};

typedef struct __play * Play;

/** Card APIs **/

/* Initialize the library */
void	holdem_init ();

/* Creates a new Card (Ace of Hearts by defaults) */
Card 	card_new ();

/* Creates a new Card with the given values */
Card	card_new_with_values (uint, char);

/* Creates a new Random card */
Card	card_new_random ();

/* Frees a card */
void	card_free (Card);

/* Getters */
uint	card_get_value (Card);
char	card_get_seed (Card);

/* Setters */
void	card_set_value (Card, uint);
void	card_set_seed (Card, char);
void	card_set_new (Card, uint, char);

/* Compare cards:
 * returns 1 if the first card provided is higher than the second
 * 0 otherwise */
uint	card_is_higher (Card, Card);

/* Returns true if the cards are exactly the same */
uint	card_is_same (Card, Card);




/** Deck APIs **/

/* Creates a new ordered deck */
Deck	deck_new ();

/* Creates a new shuffled deck */
Deck	deck_new_shuffled ();

/* Shuffles an existing deck
 *
 * This actually returns a new (m)alloc'd deck, the deck passed as
 * argument will be automatically freed.
 */
Deck	deck_shuffle (Deck);

/* Returns 1 if deck is empty, 0 otherwise */
int		deck_is_empty (Deck);
void	deck_free (Deck);

/* Returns the number of the cards in the deck */
uint	deck_count_cards (Deck);

/**
  * Pushes a card at the end of the deck.
  * Returns -1 if the card is already in the deck
  */
int		deck_push_card (Deck *, Card);

/**
  * Gets the first card from the deck
  */
Card	deck_pop_card (Deck *);


/**
 * Gets the card at the given index
 */
Card 	deck_get_card (Deck, uint index);


/** Player APIs **/

/** Creates a new player
 *	First parameter is the name of the player
 *	Second parameter is the initial credit of the player
 */
Player			player_new (const char *, uint);
void			player_free (Player);

/*
 * Deals the hand to the player
 *
 * This may overwrite the cards that the player is already holding
 */
void			player_deal_hand (Player, Card[2]);

/*
 * Lets the player place the bet given as arguments
 * returns the bet if everything goes right
 * returns 0 if bet > credit and sets the "folded" bit to 1
 */
uint			player_place_bet (Player, uint);

/*
 * Sets to NULL the cards' pointer
 */
void			player_reset_hand (Player);

/*
 * Getters
 */
const char * 	player_get_name (Player);
uint			player_get_credit (Player);
Card *			player_get_hand (Player);
uint			player_has_folded (Player);
uint			player_get_last_bet (Player);



/** Play APIs **/

/*
 * Create a new Play with the given Deck.
 * Second parameter is the ante of the play
 * Third parameter is the small blind
 * Fourth parameter is the big blind
 */
Play			play_new (Deck, uint, uint, uint);
void			play_free (Play);

/*
 * Inserts a player into the play. Returns -1 if there are already 4 players registered
 */
uint			play_register_player (Play, Player);

/*
 * Getters
 */
uint			play_get_players_count (Play);
Player			play_get_player (Play, uint);
Player			play_get_dealer (Play);
Player			play_get_small_blind (Play);
Player			play_get_big_blind (Play);
uint			play_get_pot (Play);

/*
 * Setters
 */
void			play_set_dealer (Play *, uint);

/*
 * Deal hands (first two cards) to every player registered
 */
void			play_deal_hands (Play);

/*
 * Deals flop, turn and river.
 */
void			play_deal_flop (Play);
void			play_deal_turn (Play);
void			play_deal_river (Play);

/*
 * Makes every player registered to place the ante
 */
void			play_place_ante (Play);

/*
 * Lets the player at index place the bet
 */
void			play_place_bet (Play, uint index, uint bet);

#endif
