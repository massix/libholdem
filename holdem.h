/** Copyright **/

/* holdem.h library description */

#include <stdio.h>
#include <stdlib.h>
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

int		deck_is_empty (Deck);
void	deck_free (Deck);
uint	deck_count_cards (Deck);

/**
  * Pushes a card at the end of the deck.
  * It may return -1 if the card is already in the deck
  */
int		deck_push_card (Deck *, Card);

/**
  * Gets the first card from the deck
  */
Card	deck_pop_card (Deck *);


/**
 * Gets the card at index
 */
Card 	deck_get_card (Deck *, uint index);

