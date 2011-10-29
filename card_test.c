#include "holdem.h"

void print_card (Card c) {
    printf ("\tCard: %02d (%c) ", card_get_value (c), card_get_seed (c));

#ifdef UNICODE_ENABLED
	switch (card_get_seed (c)) {
		case HEARTS:
			printf ("\u2665");
			break;
		case SPADES:
			printf ("\u2660");
			break;
		case DIAMONDS:
			printf ("\u2666");
			break;
		case CLUBS:
			printf ("\u2663");
			break;
	}
#endif

	printf ("\n");
    fflush (stdout);
}

int main () {
	holdem_init ();

	Play p = play_new (deck_new (), 0, 500, 1000);

	play_register_player (&p, player_new ("Flavio", 80000));
	play_register_player (&p, player_new ("Monica", 80000));
	play_register_player (&p, player_new ("Massi", 80000));
	play_register_player (&p, player_new ("Alice", 80000));

	play_set_dealer (&p, 3);

	printf ("There are %d players at the table\n", play_get_players_count (p));
	printf ("Dealer is %s, small blind is %s, big blind is %s\n",
			player_get_name (play_get_dealer (p)),
			player_get_name (play_get_small_blind (p)),
			player_get_name (play_get_big_blind (p)));

	play_place_ante (&p);
	play_deal_hands (&p);
	for (int i = 0; i < play_get_players_count (p); i++) {
		Player get = play_get_player (p, i);
		Card * hand = player_get_hand (get);
		play_place_bet (&p, i, 2500);

		printf ("Player %s has %d credits left and hand:\n", player_get_name (get), player_get_credit (get));
		print_card (hand[0]);
		print_card (hand[1]);
	}

	printf ("Pot is: %d\n", play_get_pot (p));

	play_free (p);

	return 0;
}
