/*
** EPITECH PROJECT, 2022
** CPool_13
** File description:
** csfml_objects
*/

#include "radar.h"

sfSprite *create_sprite(char *filepath, int x, int y)
{
    sfTexture *texture = sfTexture_createFromFile(filepath, NULL);
    sfSprite *sprite = sfSprite_create();
    sfVector2f pos = {x, y};

    sfSprite_setTexture(sprite, texture, 0);
    sfSprite_setPosition(sprite, pos);
    return (sprite);
}

sfSound *create_sound(char *filepath)
{
    sfSound *sound = sfSound_create();
    sfSoundBuffer *buffer = sfSoundBuffer_createFromFile(filepath);

    sfSound_setBuffer(sound, buffer);
    return (sound);
}

sfCircleShape *create_circle(sfVector2f pos, float radius)
{
    sfCircleShape *circle = sfCircleShape_create();

    sfCircleShape_setPosition(circle, pos);
    sfCircleShape_setRadius(circle, radius);
    sfCircleShape_setFillColor(circle, sfTransparent);
    sfCircleShape_setOutlineThickness(circle, 1);
    sfCircleShape_setOutlineColor(circle, sfBlue);
    return (circle);
}

sfRectangleShape *create_rect(char *fp, sfVector2f pos, sfVector2f sz)
{
    sfRectangleShape *r_shape = sfRectangleShape_create();
    sfTexture *texture = sfTexture_createFromFile(fp, NULL);

    sfRectangleShape_setTexture(r_shape, texture, sfTrue);
    sfRectangleShape_setSize(r_shape, sz);
    sfRectangleShape_setPosition(r_shape, pos);
    return (r_shape);
}

sfText *create_text(char *font_fp, char *str, sfVector2f pos, int size)
{
    sfFont *font = sfFont_createFromFile(font_fp);
    sfText *text = sfText_create();

    pos.x += 10;
    pos.y -= 30;
    sfText_setString(text, str);
    sfText_setFont(text, font);
    sfText_setPosition(text, pos);
    sfText_setCharacterSize(text, size);
    return (text);
}
