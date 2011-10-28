#include "holdem.h"

void print_card (Card c) {
	printf ("Card: %d%c\n", 	card_get_value (c),
								card_get_seed (c));
	fflush (stdout);
}

int main () {
	holdem_init ();

	/* Test the new () function */
	Card firstCard = card_new ();
	print_card (firstCard);
	card_free (firstCard);

	/* Create a new random card */
	firstCard = card_new_random ();
	print_card (firstCard);
	card_free (firstCard);

	/* Create a card with given values */
	firstCard = card_new_with_values (12, CLUBS);
	print_card (firstCard);

	/* Set a new VALID value */
	card_set_new (firstCard, 4, HEARTS);
	print_card (firstCard);

	/* Set a new INVALID value */
	card_set_new (firstCard, 15, 'P');
	print_card (firstCard);
	card_free (firstCard);

	Card secondCard = card_new_random ();
	firstCard = card_new_random ();
	printf ("Confronting the next two cards:\n");
	print_card (firstCard);
	print_card (secondCard);
	printf ("firstCard is %s than secondCard\n", 
			card_is_higher(firstCard, secondCard)? "higher" : "lower");
	fflush (stdout);
	card_free (firstCard);
	card_free (secondCard);


	/* Test the Deck */
	Deck d = deck_new ();
	deck_free (d);

	d = deck_new ();

	firstCard = card_new_with_values (1, SPADES);
	if (deck_push_card(&d, firstCard))
		fprintf (stderr, "This is wrong\n");

	else
		printf ("Ok, pushing the same card twice gives an error\n");

	card_free (firstCard);
	printf ("There are %d cards in the deck\n", deck_count_cards(d));
	fflush (stdout);
	while (!deck_is_empty (d)) {
		firstCard = deck_pop_card (&d);
		print_card (firstCard);
		free (firstCard);
	}

	printf ("There are now %d cards in the deck\n", deck_count_cards(d));
	fflush (stdout);

	deck_push_card(&d, card_new_with_values(1, SPADES));
	deck_push_card(&d, card_new_with_values(2, SPADES));
	deck_push_card(&d, card_new_with_values(3, SPADES));
	deck_push_card(&d, card_new_with_values(4, SPADES));
	printf ("There are now %d cards in the deck\n", deck_count_cards(d));
	fflush (stdout);

	firstCard = deck_get_card (&d, 1);
	print_card (firstCard);
	printf ("There are now %d cards in the deck\n", deck_count_cards(d));
	fflush (stdout);

	deck_free (d);

	Deck shuffled = deck_new_shuffled ();
	printf ("There are now %d cards in the deck\n", deck_count_cards(shuffled));
	fflush (stdout);
	while (!deck_is_empty (shuffled)) {
			firstCard = deck_pop_card (&shuffled);
			print_card (firstCard);
			free (firstCard);
		}

	printf ("Ok\n");
	fflush (stdout);
	return 0;
}
