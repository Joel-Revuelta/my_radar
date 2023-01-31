/*
** EPITECH PROJECT, 2023
** my_radar
** File description:
** in_tower
*/

#include "radar.h"

sfVector2f *get_corners(sfFloatRect const rect)
{
    sfVector2f *corners = malloc(sizeof(sfVector2f) * 4);

    corners[0] = (sfVector2f) {rect.left, rect.top};
    corners[1] = (sfVector2f) {rect.left + rect.width, rect.top};
    corners[2] = (sfVector2f) {rect.left, rect.top + rect.height};
    corners[3] = (sfVector2f) {rect.left + rect.width, rect.top + rect.height};
    return (corners);
}

sfBool point_in_circle(sfVector2f point, sfVector2f center, float radius)
{
    float x = point.x - center.x;
    float y = point.y - center.y;

    return (pow(x, 2) + pow(y, 2) <= pow(radius, 2));
}

sfBool is_in_circle(plane_t *plane, tower_t *tower)
{
    plane->hitbox = get_hitbox(plane);
    sfVector2f *corners = get_corners(plane->hitbox);
    sfVector2f center = sfCircleShape_getPosition(tower->circle);
    float radius = sfCircleShape_getRadius(tower->circle);
    sfBool res = sfFalse;

    for (int i = 0; i < 4 && !res; i++) {
        if (point_in_circle(corners[i], center, radius))
            res = sfTrue;
    }
    free(corners);
    return (res);
}

sfBool is_in_tower(plane_t *plane, radar_t *radar)
{
    for (tower_t *tow = radar->towers; tow; tow = tow->next) {
        if (radar->l_option)
            sfCircleShape_setOutlineColor(tow->circle, sfTransparent);
        else
            sfCircleShape_setOutlineColor(tow->circle, sfBlue);
        if (radar->s_option)
            sfRectangleShape_setTextureRect(tow->rect, (sfIntRect){0, 0, 0, 0});
        else
            sfRectangleShape_setTextureRect(tow->rect, (sfIntRect){0, 0, 200,
            200});
        if (is_in_circle(plane, tow)) {
            return (sfTrue);
        }
    }
    return (sfFalse);
}
