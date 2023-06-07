/*
** EPITECH PROJECT, 2023
** my_radar
** File description:
** planes
*/

#include "radar.h"

sfBool is_landing(plane_t *planes)
{
    sfVector2f pos = sfRectangleShape_getPosition(planes->rect);
    float diff_x = fabs(planes->end.x - pos.x);
    float diff_y = fabs(planes->end.y - pos.y);

    if (diff_x < 10 && diff_y < 10)
        return (sfTrue);
    return (sfFalse);
}

plane_t *free_plane(plane_t **planes, plane_t *prev, plane_t *curr)
{
    if (prev == NULL) {
        *planes = curr->next;
    } else {
        prev->next = curr->next;
    }
    sfRectangleShape_destroy(curr->rect);
    sfClock_destroy(curr->clock);
    free(curr);
    return (prev == NULL) ? *planes : prev->next;
}

sfBool end_delay(plane_t *planes, sfClock *clock)
{
    if (planes->delay <= sfTime_asSeconds(sfClock_getElapsedTime(clock))) {
        planes->delay = 0;
        sfClock_restart(clock);
        return (sfTrue);
    }
    return (sfFalse);
}

void do_collisions(plane_t **planes, radar_t *radar, plane_t *tmp)
{
    if (is_in_tower(tmp, radar))
        sfRectangleShape_setOutlineColor(tmp->rect, sfGreen);
    else {
        sfRectangleShape_setOutlineColor(tmp->rect, sfYellow);
        check_crash(&tmp, planes);
    }
    if (radar->l_option)
        sfRectangleShape_setOutlineColor(tmp->rect, sfTransparent);
    if (radar->s_option)
        sfRectangleShape_setTextureRect(tmp->rect, (sfIntRect){0, 0, 0, 0});
    else
        sfRectangleShape_setTextureRect(tmp->rect, (sfIntRect){0, 0, 128, 128});
}

void move_planes(plane_t **planes, radar_t *radar)
{
    plane_t *prev = NULL;

    for (plane_t *tmp = *planes; tmp; prev = tmp, tmp = tmp->next) {
        if ((tmp->delay && !end_delay(tmp, tmp->clock)) || tmp->delay)
            continue;
        if (sfTime_asMilliseconds(sfClock_getElapsedTime(tmp->clock)) > 25) {
            sfRectangleShape_move(tmp->rect, tmp->step);
            sfClock_restart(tmp->clock);
        }
        if (is_landing(tmp) || tmp->del)
            tmp = free_plane(planes, prev, tmp);
        if (!tmp)
            break;
        if (is_landing(tmp))
            continue;
        do_collisions(planes, radar, tmp);
        if (!tmp)
            return;
    }
}
