/** Copyright **/

#include "holdem.h"

Play play_new (Deck deck, uint ante, uint small_blind, uint big_blind) {
	Play ret = (Play) malloc (sizeof (struct __play));
	int i = 0;
	for (i = 0; i < 5; i++)
		ret->players[i] = NULL;

	ret->playing = 0;
	ret->deck = deck;

	for (i = 0; i < 3; i++)
		ret->flop[i] = NULL;

	ret->river = NULL;
	ret->turn = NULL;

	ret->pot = 0;

	ret->ante = ante;
	ret->small_blind = small_blind;
	ret->big_blind = big_blind;
	ret->dealer = 0;

	return ret;
}

void play_free (Play p) {
	for (int i = 0; i < p->playing; i++)
		player_free (p->players[i]);

	deck_free (p->deck);

	for (int i = 0; i < 3; i++)
		if (p->flop[i] != NULL)
			card_free (p->flop[i]);

	if (p->river != NULL)
		card_free (p->river);

	if (p->turn != NULL)
		card_free (p->turn);

	free (p);
}

uint play_register_player (Play * p, Player player) {
	if ((*p)->playing > 4)
		return 0;

	(*p)->players[(*p)->playing++] = player;
	return 1;
}

uint play_get_players_count (Play p) {
	return p->playing;
}

Player play_get_player (Play p, uint index) {
	if (index >= 0 && index < p->playing)
		return p->players[index];

	return NULL;
}

void play_set_dealer (Play * p, uint index) {
	if (index < 0 || index >= (*p)->playing)
		return;

	(*p)->dealer = index;
}

Player play_get_dealer (Play p) {
	return p->players[p->dealer];
}

Player play_get_small_blind (Play p) {
	uint index = (p->dealer + 1) % (p->playing);

	return p->players[index];
}

Player play_get_big_blind (Play p) {
	uint index = (p->dealer + 2) % (p->playing);

	return p->players[index];
}

uint play_get_pot (Play p) {
	return p->pot;
}

void play_deal_hands (Play * p) {
	int i = 0;

	(*p)->deck = deck_shuffle ((*p)->deck);

	for (i = 0; i < (*p)->playing; i++) {
		Card hand[2];
		hand[0] = deck_pop_card (&((*p)->deck));
		hand[1] = deck_pop_card (&((*p)->deck));

		player_deal_hand (&((*p)->players[i]), hand);
	}
}

void play_deal_flop (Play * p) {
	free (deck_pop_card (&((*p)->deck)));
	(*p)->flop[0] = deck_pop_card ((&((*p)->deck)));

	free (deck_pop_card (&((*p)->deck)));
	(*p)->flop[1] = deck_pop_card (&((*p)->deck));

	free (deck_pop_card (&((*p)->deck)));
	(*p)->flop[1] = deck_pop_card ((&((*p)->deck)));
}

void play_deal_turn (Play * p) {
	free (deck_pop_card ((&((*p)->deck))));
	(*p)->turn = deck_pop_card ((&((*p)->deck)));
}

void play_deal_river (Play * p) {
	free (deck_pop_card ((&((*p)->deck))));
	(*p)->turn = deck_pop_card ((&((*p)->deck)));
}

void play_place_ante (Play * p) {
	int i = 0;

	for (i = 0; i < (*p)->playing; i++) {
		if ((*p)->players[i] == play_get_small_blind (*p))
			(*p)->pot += player_place_bet (&((*p)->players[i]), (*p)->small_blind);

		else if ((*p)->players[i] == play_get_big_blind (*p))
			(*p)->pot += player_place_bet (&((*p)->players[i]), (*p)->big_blind);

		else
			(*p)->pot += player_place_bet (&((*p)->players[i]), (*p)->ante);
	}

}

void play_place_bet (Play * p, uint index, uint bet) {
	if (index >= 0 && index < (*p)->playing) {
		if (!player_has_folded ((*p)->players[index]))
			(*p)->pot += player_place_bet (&((*p)->players[index]), bet);
	}
}
