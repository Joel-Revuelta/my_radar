/*
** EPITECH PROJECT, 2023
** my_radar
** File description:
** collisions
*/

#include "radar.h"

sfBool check_coll(sfRectangleShape* r1, sfRectangleShape* r2, sfVector2f *x,
sfVector2f pos1)
{
    sfVector2f size1 = sfRectangleShape_getSize(r1);
    sfVector2f pos2 = sfRectangleShape_getPosition(r2);
    sfVector2f size2 = sfRectangleShape_getSize(r2);
    for (int i = 0; i < 4; i++) {
        float mi1 = INFINITY, ma1 = -INFINITY, mi2 = INFINITY, ma2 = -INFINITY;
        for (int j = 0; j < 4; j++) {
            sfVector2f point = {
            pos1.x + (j % 2 == 0 ? 0 : size1.x) - (j / 2 == 0 ? 0 : size1.y),
            pos1.y + (j % 2 == 0 ? 0 : size1.x) + (j / 2 == 0 ? 0 : size1.y)};
            float projection = point.x * x[i].x + point.y * x[i].y;
            mi1 = fmin(mi1, projection), ma1 = fmax(ma1, projection);
            point = (sfVector2f){
            pos2.x + (j % 2 == 0 ? 0 : size2.x) - (j / 2 == 0 ? 0 : size2.y),
            pos2.y + (j % 2 == 0 ? 0 : size2.x) + (j / 2 == 0 ? 0 : size2.y)};
            projection = point.x * x[i].x + point.y * x[i].y;
            mi2 = fmin(mi2, projection), ma2 = fmax(ma2, projection);}
        if (ma1 < mi2 || ma2 < mi1)
            return sfFalse;
    }
    return sfTrue;
}

void check_crash(plane_t **pl, plane_t **planes)
{
    for (plane_t *tmp = *planes; *pl && tmp; tmp = tmp->next) {
        if (((tmp->delay && !end_delay(tmp, tmp->clock)) || tmp->delay ||
        *pl == tmp) || !tmp || !*pl)
            continue;
        float rot1 = sfRectangleShape_getRotation((*pl)->rect) * M_PI / 180.0f;
        float rot2 = sfRectangleShape_getRotation(tmp->rect) * M_PI / 180.0f;
        sfVector2f axis[4] = {{cos(rot1), sin(rot1)}, {cos(rot1 + M_PI / 2.0f),
        sin(rot1 + M_PI / 2.0f)}, {cos(rot2), sin(rot2)},
        {cos(rot2 + M_PI / 2.0f), sin(rot2 + M_PI / 2.0f)}};
        sfVector2f pos1 = sfRectangleShape_getPosition((*pl)->rect);
        if (check_coll((*pl)->rect, tmp->rect, axis, pos1)) {
            tmp->del = sfTrue;
            (*pl)->del = sfTrue;
            break;
        }
    }
}
