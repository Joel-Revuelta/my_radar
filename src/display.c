/*
** EPITECH PROJECT, 2023
** my_radar
** File description:
** display
*/

#include "radar.h"

void display(radar_t *radar)
{
    sfRenderWindow_clear(radar->wd, sfBlack);
    sfRenderWindow_drawSprite(radar->wd, radar->bg, NULL);
    for (plane_t *tmp = radar->planes; tmp; tmp = tmp->next)
        if (tmp->delay == 0)
            sfRenderWindow_drawRectangleShape(radar->wd, tmp->rect, NULL);
    for (tower_t *tmp = radar->towers; tmp; tmp = tmp->next) {
        sfRenderWindow_drawRectangleShape(radar->wd, tmp->rect, NULL);
        sfRenderWindow_drawCircleShape(radar->wd, tmp->circle, NULL);
    }
    sfRenderWindow_drawRectangleShape(radar->wd, radar->t_txt, NULL);
    sfRenderWindow_display(radar->wd);
}
