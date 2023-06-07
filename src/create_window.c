/*
** EPITECH PROJECT, 2023
** my_radar
** File description:
** create_window
*/

#include "radar.h"

sfRenderWindow *create_window(char *name, int fr)
{
    sfRenderWindow *wd;
    sfVideoMode mode = {WIDTH, HEIGHT, BPP};

    wd = sfRenderWindow_create(mode, name, sfDefaultStyle | sfFullscreen, NULL);
    sfRenderWindow_setFramerateLimit(wd, fr);
    return (wd);
}
