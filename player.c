/** Copyright **/

#include "holdem.h"

Player player_new (const char * name, uint credit) {
	Player ret = (Player) malloc (sizeof (struct __player));

	ret->name = (char *) malloc (sizeof (char) * (strlen (name) + 1));
	strncpy (ret->name, name, strlen(name) + 1);

	ret->hand[0] = NULL;
	ret->hand[1] = NULL;
	ret->credit = credit;

	ret->last_bet = 0;
	ret->fold = 0;

	return ret;
}

void player_free (Player player) {
	free (player->name);

	if (player->hand[0] != NULL)
		free (player->hand[0]);

	if (player->hand[1] != NULL)
		free (player->hand[1]);
	free (player);
}

void player_deal_hand (Player p, Card hand[2]) {
	p->hand[0] = hand[0];
	p->hand[1] = hand[1];
}

uint player_place_bet (Player p, uint bet) {
	if (bet > p->credit || bet < 0) {
		p->fold = 1;
		return 0;
	}

	p->credit -= bet;
	p->last_bet = bet;

	return bet;
}

void player_reset_hand (Player p) {
	p->hand[0] = NULL;
	p->hand[1] = NULL;
}

const char * player_get_name (Player p) {
	return (const char *) p->name;
}

uint player_get_credit (Player p) {
	return p->credit;
}

Card * player_get_hand (Player p) {
	return (Card *) p->hand;
}

uint player_has_folded (Player p) {
	return p->fold;
}

uint player_get_last_bet (Player p) {
	return p->last_bet;
}
