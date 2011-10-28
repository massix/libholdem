#include "holdem.h"

void print_card (Card c) {
	wprintf (L"\tCard \u9665: %d%c\n", 	card_get_value (c),
										card_get_seed (c));
	fflush (stdout);
}

int main () {
	holdem_init ();
	Deck shuffled = deck_new_shuffled ();

	/** Testing players **/
	Player massi = player_new ("Massimo", 25000);
	Player flavio = player_new ("Flavio", 30000);
	Player monica = player_new ("Monica", 10000);

	printf ("Players: %s, %s and %s\n", player_get_name (massi),
			player_get_name (flavio), player_get_name (monica));

	Card array[2];
	array[0] = deck_pop_card (&shuffled);
	array[1] = deck_pop_card (&shuffled);
	player_give_hand (&massi, array);

	array[0] = deck_pop_card (&shuffled);
	array[1] = deck_pop_card (&shuffled);
	player_give_hand (&flavio, array);

	array[0] = deck_pop_card (&shuffled);
	array[1] = deck_pop_card (&shuffled);
	player_give_hand (&monica, array);

	printf ("Deck has %d cards\n", deck_count_cards (shuffled));

	Card * pl_cards = player_get_hand (massi);
	printf ("%s has:\n", player_get_name (massi));
	print_card (pl_cards[0]);
	print_card (pl_cards[1]);

	deck_push_card (&shuffled, pl_cards[0]);
	deck_push_card (&shuffled, pl_cards[1]);

	pl_cards = player_get_hand (flavio);
	printf ("%s has:\n", player_get_name (flavio));
	print_card (pl_cards[0]);
	print_card (pl_cards[1]);

	deck_push_card (&shuffled, pl_cards[0]);
	deck_push_card (&shuffled, pl_cards[1]);

	pl_cards = player_get_hand (monica);
	printf ("%s has:\n", player_get_name (monica));
	print_card (pl_cards[0]);
	print_card (pl_cards[1]);

	deck_push_card (&shuffled, pl_cards[0]);
	deck_push_card (&shuffled, pl_cards[1]);

	printf ("Deck has %d cards\n", deck_count_cards (shuffled));

	shuffled = deck_shuffle (shuffled);
	/** Check that the Deck has all the cards **/



	player_free (massi);
	player_free (flavio);

	return 0;
}
