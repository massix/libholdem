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
#include "holdem_version.h"

// Check Unit Testing
#include <check.h>

START_TEST (cards_consistency)
{
	// Cards creation
	Card t_card = card_new_with_values (4, SPADES);
	fail_if (card_get_seed (t_card) != SPADES, "Seed not correct.");
	fail_if (card_get_value (t_card) != 4, "Value not correct.");
	card_free (t_card);
}
END_TEST

START_TEST (default_card_consistency)
{
	// Creating with default values
	Card d_card = card_new ();
	fail_if (card_get_seed (d_card) != HEARTS, "Default seed not initialized.");
	fail_if (card_get_value (d_card) != 1, "Default value not initialized.");
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
}
END_TEST

START_TEST (same_cards_comparison)
{
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
	fail_if (ordered == NULL, "Deck wasn't created correctly.");
	fail_if (deck_count_cards (ordered) != 52, "Ordered deck hasn't 52 cards inside.");
	deck_free (ordered);
}
END_TEST

START_TEST (shuffled_deck_consistency)
{
	// Shuffled deck
	Deck shuffled = deck_new_shuffled ();
	fail_if (shuffled == NULL, "Shuffled deck wasn't created correctly.");
	fail_if (deck_count_cards (shuffled) != 52, "Shuffled deck hasn't 52 cards inside.");
	deck_free (shuffled);
}
END_TEST

START_TEST (deck_push_pop)
{
	// Push and pop from an ordered deck
	Deck push_ordered = deck_new ();
	Card popped = deck_pop_card (&push_ordered);
	fail_if (card_get_seed (popped) != HEARTS, "Ordered deck doesn't begin with HEARTS as seed.");
	fail_if (deck_count_cards (push_ordered) != 51, "Card wasn't correctly popped from the deck.");

	mark_point ();

	deck_push_card (&push_ordered, popped);
	fail_if (deck_count_cards (push_ordered) != 52, "Card wasn't correctly pushed inside the deck.");
	fail_if (deck_push_card (&push_ordered, card_new_with_values (1, HEARTS)) != -1, "Deck has a duplicate card, now.");
	deck_free (push_ordered);
}
END_TEST

const char * 	p_name = "Massimo";
const int		initial_credit = 20000;
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
	tcase_add_test (consistency, default_card_consistency);

	TCase * comparison = tcase_create ("Cards' comparison");
	tcase_add_test (comparison, cards_comparison);
	tcase_add_test (comparison, same_cards_comparison);

	suite_add_tcase (s, consistency);
	suite_add_tcase (s, comparison);

	return s;
}

Suite * decks_suite ()
{
	Suite * s = suite_create ("Decks' suite");
	TCase * consistency = tcase_create ("Decks' consistency");
	tcase_add_test (consistency, deck_consistency);
	tcase_add_test (consistency, shuffled_deck_consistency);

	TCase * ppop = tcase_create ("Decks' push and pop");
	tcase_add_test (ppop, deck_push_pop);

	suite_add_tcase (s, consistency);
	suite_add_tcase (s, ppop);

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
	printf ("TESTING LIBHOLDEM %d.%d.%d\n", HOLDEM_MAJOR, HOLDEM_REVIEW,
			HOLDEM_MINOR);

	SRunner * sr = srunner_create (cards_suite ());
	srunner_set_log(sr, "tests.log");
	srunner_set_xml(sr, "tests.xml");

	srunner_add_suite (sr, decks_suite ());
	srunner_add_suite (sr, players_suite ());

	srunner_run_all (sr, CK_NORMAL);
	srunner_free (sr);

	return 0;
}
