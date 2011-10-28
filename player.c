/** Copyright **/

#include "holdem.h"

Player player_new (const char * name, uint credit) {
	Player ret = (Player) malloc (sizeof (struct __player));

	ret->name = (char *) malloc (sizeof (char) * (strlen (name) + 1));
	strncpy (ret->name, name, strlen(name) + 1);

	ret->hand[0] = NULL;
	ret->hand[1] = NULL;
	ret->credit = credit;

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

void player_give_hand (Player * p, Card hand[2]) {
	(*p)->hand[0] = hand[0];
	(*p)->hand[1] = hand[1];
}

uint player_place_bet (Player * p, uint bet) {
	if (bet > (*p)->credit)
		return 0;

	(*p)->credit -= bet;

	return bet;
}

void player_reset_hand (Player * p) {
	(*p)->hand[0] = NULL;
	(*p)->hand[1] = NULL;
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
