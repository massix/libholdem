#include "holdem.h"

void print_card (Card c) {
	printf ("Card: %d%c\n", 	card_get_value (c),
								card_get_seed (c));
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
	card_free (firstCard);
	card_free (secondCard);

	return 0;
}
