/** Copyright **/

#include "holdem.h"

/* Deck APIs */

Deck deck_new () {
	Deck ret = (Deck) malloc (sizeof (struct __deck));

	ret->current = NULL;
	ret->next = NULL;

	int i = 0, j = 0;
	for (i = 0; i < 13; i++) {
		for (j = 0; j < 4; j++) {
			char seed;

			switch (j) {
				case 0:
					seed = HEARTS;
					break;
				case 1:
					seed = DIAMONDS;
					break;
				case 2:
					seed = CLUBS;
					break;
				case 3:
					seed = SPADES;
					break;
			}

			deck_push_card (ret,
					card_new_with_values (i, seed));
		}
	}

	return ret;
}

void deck_free (Deck d) {
	Deck mover = d;
	Deck eraser = d;

	while (mover->next != NULL) {
		mover = mover->next;
		free (eraser);
		free (eraser->current);
		eraser = mover;
	}

	free (mover);
}

uint deck_count_cards (Deck d) {
	int cards = 0;
	Deck mover = d;

	while (mover->next != NULL) {
		cards++;
		mover = mover->next;
	}

	return ++cards;
}

int deck_is_empty (Deck d) {
	return (d->current == NULL);
}

int	deck_push_card (Deck d, Card c) {
	Card curr_card;
	Deck mover;

	/* There are no cards in the Deck */
	if (d->current == NULL)
		d->current = c;

	else {
		mover = d;

		while (mover->next != NULL) {
			curr_card = mover->current;

			if (card_is_same (curr_card, c))
				return -1;

			mover = mover->next;
		}

		// Last check
		curr_card = mover->current;
		if (card_is_same (curr_card, c))
			return -1;

		/** Allocates a new block and put the card in it **/
		mover->next = (Deck) malloc (sizeof (struct __deck));
		mover = mover->next;
		mover->current = c;
	}

	return 1; /* No errors occured */
}

Card deck_pop_card (Deck * d) {
	Deck head = (*d);

	/* Deck is empty :-( */
	if ((*d)->current == NULL)
		return NULL;

	Card ret = (*d)->current;
	(*d)->current = NULL;

	(*d) = (*d)->next;
	free (head);

	return ret;
}
