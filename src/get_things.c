/*
** EPITECH PROJECT, 2023
** my_radar
** File description:
** get_things
*/

#include "radar.h"

float get_angle(sfVector2f a, sfVector2f b)
{
    float dx = a.x - b.x;
    float dy = a.y - b.y;
    float radians = atan2f(dx, dy);

    if (radians < 0)
        radians = fabs(radians);
    else
        radians = 2 * M_PI - radians;
    radians = 180 / M_PI * radians;
    return (radians);
}

sfVector2f get_step(sfVector2f a, sfVector2f b, int speed)
{
    int dx = b.x - a.x;
    int dy = b.y - a.y;
    unsigned int steps = (abs(dx) > abs(dy)) ? abs(dx) : abs(dy);
    sfVector2f offset;

    offset.x = (dx / (float)steps) * speed;
    offset.y = (dy / (float)steps) * speed;
    return (offset);
}

sfVector2f rotate_point(sfVector2f point, sfVector2f center, float angle)
{
    sfVector2f r_point;

    angle = angle * (M_PI / 180);
    r_point.x = cos(angle) * (point.x - center.x) - sin(angle) *
    (point.y - center.y) + center.x;
    r_point.y = sin(angle) * (point.x - center.x) + cos(angle) *
    (point.y - center.y) + center.y;
    return (r_point);
}

sfVector2f *get_r_corners(sfFloatRect hitbox, float angle)
{
    sfVector2f center = {hitbox.left + hitbox.width / 2.0,
    hitbox.top + hitbox.height / 2.0};
    sfVector2f *corners = malloc(sizeof(sfVector2f) * 4);

    corners[0] = (sfVector2f){hitbox.left, hitbox.top};
    corners[1] = (sfVector2f){hitbox.left + hitbox.width, hitbox.top};
    corners[2] = (sfVector2f){hitbox.left, hitbox.top + hitbox.height};
    corners[3] = (sfVector2f){hitbox.left + hitbox.width,
    hitbox.top + hitbox.height};

    for (int i = 0 ; i < 4 ; i++)
        corners[i] = rotate_point(corners[i], center, angle);
    return (corners);
}

sfFloatRect get_hitbox(plane_t *plane)
{
    sfVector2f pos = sfRectangleShape_getPosition(plane->rect);
    sfFloatRect hitbox = {pos.x, pos.y, P_SIZE, P_SIZE};
    sfVector2f *corners = get_r_corners(hitbox,
    sfRectangleShape_getRotation(plane->rect));
    float min_x = corners[0].x, max_x = corners[0].x;
    float min_y = corners[0].y, max_y = corners[0].y;

    for (unsigned int i = 1 ; i < 4 ; i++) {
        if (corners[i].x < min_x)
            min_x = corners[i].x;
        if (corners[i].x > max_x)
            max_x = corners[i].x;
        if (corners[i].y < min_y)
            min_y = corners[i].y;
        if (corners[i].y > max_y)
            max_y = corners[i].y;
    }
    free(corners);
    hitbox = (sfFloatRect){min_x, min_y, max_x - min_x, max_y - min_y};
    return (hitbox);
}
