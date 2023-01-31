/*
** EPITECH PROJECT, 2023
** my_radar
** File description:
** events
*/

#include "radar.h"

void events(radar_t *radar)
{
    if (radar->evt.type == sfEvtClosed || (radar->evt.type == sfEvtKeyPressed &&
    radar->evt.key.code == sfKeyEscape))
        sfRenderWindow_close(radar->wd);
    if ((radar->evt.type == sfEvtKeyPressed && radar->evt.key.code == sfKeyL))
        radar->l_option = radar->l_option ? sfFalse : sfTrue;
    if ((radar->evt.type == sfEvtKeyPressed && radar->evt.key.code == sfKeyS))
        radar->s_option = radar->s_option ? sfFalse : sfTrue;
}
