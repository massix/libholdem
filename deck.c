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


#include "holdem.h"

/* Deck APIs */

Deck deck_new () {
	Deck ret = (Deck) malloc (sizeof (struct __deck));

	ret->current = NULL;
	ret->next = NULL;

	int i = 0, j = 0;
	for (i = 1; i < 14; i++) {
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

			deck_push_card (&ret,
					card_new_with_values (i, seed));
		}
	}

	return ret;
}

Deck deck_new_shuffled () {
	Deck original = deck_new ();

	return deck_shuffle (original);
}

Deck deck_shuffle (Deck original) {
	Deck shuffled = (Deck) malloc (sizeof (struct __deck));

	shuffled->current = NULL;
	shuffled->next = NULL;

	while (!deck_is_empty (original)) {
		uint rand_card = rand () % deck_count_cards (original);
		Card c = deck_get_card (original, rand_card);
		if (c != NULL)
			deck_push_card (&shuffled, c);
	}

	deck_free (original);
	return shuffled;
}

void deck_free (Deck d) {
	while (!deck_is_empty(d)) {
		Card c = deck_pop_card(&d);
		if (c != NULL)
			free (c);
	}

	free (d);
}

uint deck_count_cards (Deck d) {
	int cards = 1;
	Deck mover = d;

	if (deck_is_empty(d))
		return 0;

	while (mover->next != NULL) {
		cards++;
		mover = mover->next;
	}

	return cards;
}

int deck_is_empty (Deck d) {
	return (d->current == NULL);
}

int	deck_push_card (Deck * d, Card c) {
	Card curr_card;
	Deck mover;

	/* There are no cards in the Deck */
	if ((*d)->current == NULL)
		(*d)->current = c;

	else {
		mover = (*d);

		while (mover->next != NULL) {
			curr_card = mover->current;

			if (card_is_same (curr_card, c))
				return 0;

			mover = mover->next;
		}

		// Last check
		curr_card = mover->current;
		if (card_is_same (curr_card, c))
			return -1;

		/** Allocates a new block and put the card in it **/
		mover->next = (Deck) malloc (sizeof (struct __deck));
		mover = mover->next;
		mover->next = NULL;
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

	if ((*d)->next != NULL) {
		(*d) = (*d)->next;
		free (head);
	}

	return ret;
}

Card deck_get_card (Deck d, uint index) {
	Card ret;
	Deck head = d;
	Deck curr = d;

	if (index > 0) {
		uint i = 0;
		while (i != index) {
			head = curr;
			curr = head->next;
			if (curr->next == NULL)
				break;
			i++;
		}

		head->next = curr->next;
		ret = curr->current;
		free (curr);

		return ret;
	}

	return deck_pop_card (&d);
}
