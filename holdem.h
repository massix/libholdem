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

struct __deck {
	struct __card	cards[40];
	int				decksize;
};

enum {
	HEARTS = 'H',
	DIAMONDS = 'D',
	CLUBS = 'C',
	SPADES = 'S'
};

typedef struct __card * Card;
typedef struct __deck * Deck;

/* Initialize the library */
void	holdem_init ();

/* Creates a new Card (Ace of Hearts by defaults) */
Card 	card_new ();

/* Creates a new Card with the given values */
Card	card_new_with_values (uint value, char seed);

/* Creates a new Random card */
Card	card_new_random ();

/* Frees a card */
void	card_free (Card card);

/* Getters */
uint	card_get_value (Card card);
char	card_get_seed (Card card);

/* Setters */
void	card_set_value (Card card, uint value);
void	card_set_seed (Card card, char seed);
void	card_set_new (Card card, uint value, char seed);

/* Compare cards:
 * returns 1 if the first card provided is higher than the second
 * 0 otherwise */
uint	card_is_higher (Card first, Card second);
