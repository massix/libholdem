#include "holdem.h"

// Check Unit Testing
#include <check.h>

START_TEST (cards_consistency)
{
	// Cards creation
	Card t_card = card_new_with_values (4, SPADES);
	fail_if (card_get_seed (t_card) != SPADES, "Seed not correct.");
	fail_if (card_get_value (t_card) != 4, "Value not correct.");
	card_free (t_card);

	// Creating with default values
	Card d_card = card_new ();
	fail_if (card_get_seed (t_card) != HEARTS, "Default seed not initialized.");
	fail_if (card_get_value (t_card) != 1, "Default value not initialized.");
	card_free (d_card);
}
END_TEST


START_TEST (cards_comparison)
{
	Card lower_card = card_new_with_values (2, SPADES);
	Card higher_card = card_new_with_values (8, HEARTS);
	fail_unless (card_is_higher (higher_card, lower_card), "Wrong comparison between higher-lower card.");
	card_free (lower_card);
	card_free (higher_card);

	Card card_one = card_new ();
	Card card_two = card_new ();

	fail_unless (card_is_same (card_one, card_two), "Wrong comparison between same cards.");
	card_free (card_one);
	card_free (card_two);
}
END_TEST


START_TEST (deck_consistency)
{
	// Ordered deck
	Deck ordered = deck_new ();
	fail_if (deck_count_cards (ordered) != 52, "Ordered deck hasn't 52 cards inside.");
	deck_free (ordered);

	// Shuffled deck
	Deck shuffled = deck_new_shuffled ();
	fail_if (deck_count_cards (shuffled) != 52, "Shuffled deck hasn't 52 cards inside.");
	deck_free (ordered);

	// Push and pop from an ordered deck
	Deck push_ordered = deck_new ();
	Card popped = deck_pop_card (&push_ordered);
	fail_if (card_get_seed (popped) != HEARTS, "Ordered deck doesn't begin with HEARTS as seed.");
	fail_if (deck_count_cards (push_ordered) != 51, "Card wasn't correctly popped from the deck.");

	deck_push_card (&push_ordered, popped);
	fail_if (deck_count_cards (push_ordered) != 52, "Card wasn't correctly pushed inside the deck.");
	fail_if (deck_push_card (&push_ordered, card_new_with_values (1, HEARTS)) != -1, "Deck has a duplicate card, now.");
}
END_TEST

const char * 	p_name = "Massimo";
int				initial_credit = 20000;
START_TEST (player_consistency)
{
	Player massi = player_new (p_name, initial_credit);
	fail_if (strcmp (p_name, player_get_name (massi)) != 0, "Player's name is incorrect.");
	fail_if (player_get_credit (massi) != initial_credit, "Player's credit is incorrect.");

	player_free (massi);
}
END_TEST

START_TEST (player_dealings)
{
	Player massi = player_new (p_name, initial_credit);
	Card deal[2];
	deal[0] = card_new_random ();
	deal[1]	= card_new_random ();

	player_deal_hand (massi, deal);
	Card * received;
	received = player_get_hand (massi);

	fail_unless (card_is_same (received[0], deal[0]), "Player's hand (first card) is not correct.");
	fail_unless (card_is_same (received[1], deal[1]), "Player's hand (second card) is not correct.");

	player_free (massi);
}
END_TEST

START_TEST (players_bet)
{
	Player massi = player_new (p_name, initial_credit);

	fail_if (player_place_bet (massi, 10000) != 10000, "Player's bet not correct.");
	fail_if (player_place_bet (massi, 10000) != 10000, "Player's bet (second one) not correct.");

	fail_if (player_place_bet (massi, 20) != 0, "Player's bet not correct (folding one).");
	fail_unless (player_has_folded (massi), "Player didn't fold after betting everything.");
	player_free (massi);
}
END_TEST


Suite * cards_suite ()
{
	Suite * s = suite_create ("Cards' suite");
	TCase * consistency = tcase_create ("Cards' consistency");
	tcase_add_test (consistency, cards_consistency);

	TCase * comparison = tcase_create ("Cards' comparison");
	tcase_add_test (comparison, cards_comparison);

	suite_add_tcase (s, consistency);
	suite_add_tcase (s, comparison);

	return s;
}

Suite * decks_suite ()
{
	Suite * s = suite_create ("Decks' suite");
	TCase * consistency = tcase_create ("Decks' consistency");
	tcase_add_test (consistency, deck_consistency);

	suite_add_tcase (s, consistency);

	return s;
}

Suite * players_suite ()
{
	Suite * s = suite_create ("Players' suite");

	TCase * consistency = tcase_create ("Players' consistency");
	tcase_add_test (consistency, player_consistency);

	TCase * dealings = tcase_create ("Players' dealings");
	tcase_add_test (dealings, player_dealings);

	TCase * bettings = tcase_create ("Players' bettings");
	tcase_add_test (bettings, players_bet);

	suite_add_tcase (s, consistency);
	suite_add_tcase (s, dealings);
	suite_add_tcase (s, bettings);

	return s;
}

int main (void)
{
	Suite * s = cards_suite ();
	SRunner * sr = srunner_create (s);
	srunner_add_suite (sr, decks_suite ());
	srunner_add_suite (sr, players_suite ());

	srunner_run_all (sr, CK_VERBOSE);
	srunner_free (sr);

	return 0;
}
