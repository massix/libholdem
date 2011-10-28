/** Copyright **/

#include "holdem.h"


Card card_new () {
	Card ret = (Card) malloc (sizeof (struct __card));

	ret->value = 1;
	ret->seed = HEARTS;

	return ret;
}

Card card_new_random () {
	Card ret = card_new ();
	
	ret->value = (rand () % 13) + 1;

	switch (rand () % 4) {
		case 0:
			ret->seed = SPADES;
			break;
		case 1:
			ret->seed = DIAMONDS;
			break;
		case 2:
			ret->seed = CLUBS;
			break;
		case 3:
			ret->seed = HEARTS;
			break;
	}

	return ret;
}


/* Internal function used to check if the given seed is good */
static int __check_seed (char seed) {
	return (seed == HEARTS || seed == DIAMONDS || 
			seed == CLUBS || seed == SPADES);
}

Card card_new_with_values (uint value, char seed) {
	Card ret = card_new ();
	if (value < 1 || value > 13)
		value = 1;

	if (!__check_seed (seed))
		seed = SPADES;

	ret->value = value;
	ret->seed = seed;

	return ret;
}

void card_free (Card card) {
	free (card);
}

uint card_get_value (Card card) {
	return card->value;
}

char card_get_seed (Card card) {
	return card->seed;
}


void card_set_value (Card card, uint value) {
	if (value > 13 || value < 1)
		return;

	card->value = value;
}

void card_set_seed (Card card, char seed) {
	if (!__check_seed (seed))
		return;

	card->seed = seed;
}

void card_set_new (Card card, uint value, char seed) {
	card_set_value (card, value);
	card_set_seed (card, seed);
}

uint card_is_higher (Card first, Card second) {
	if (first->value > second->value)
		return 1;

	else if (first->value < second->value)
		return 0;

	/* values are tied, check the seed */
	if (first->seed == second->seed)
		return 1;

	return 0;
}

uint card_is_same (Card first, Card second) {
	return (first->value == second->value && 
			first->seed == second->seed);
}
