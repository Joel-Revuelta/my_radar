/*
** EPITECH PROJECT, 2022
** my_radar
** File description:
** my_radar
*/

#include "radar.h"

void update_timer(radar_t *radar)
{
    static int seconds = 0;
    static int minutes = 0;
    char *str = NULL;

    if (seconds < 59)
        seconds += 1;
    else {
        seconds = 0;
        minutes += 1;
    }
    if (my_int_len(minutes) == 1)
        str = my_strmcat(str, "0");
    str = my_strmcat(str, my_int_to_str(minutes));
    str = my_strmcat(str, ":");
    if (my_int_len(seconds) == 1)
        str = my_strmcat(str, "0");
    str = my_strmcat(str, my_int_to_str(seconds));
    sfText_setString(radar->t_txt, str);
    sfClock_restart(radar->timer);
}

void game_loop(radar_t *radar)
{
    if (sfTime_asSeconds(sfClock_getElapsedTime(radar->timer)) >= 1)
        update_timer(radar);
    move_planes(&radar->planes, radar);
    while (sfRenderWindow_pollEvent(radar->wd, &radar->evt))
        events(radar);
    display(radar);
    if (!radar->planes)
        sfRenderWindow_close(radar->wd);
}

void destroyer(radar_t *radar)
{
    sfMusic_destroy(radar->music);
    sfSprite_destroy(radar->bg);
    sfClock_destroy(radar->timer);
    sfText_destroy(radar->t_txt);
    sfRenderWindow_destroy(radar->wd);
    for (plane_t *tmp = radar->planes, *next; tmp; tmp = next) {
        next = tmp->next;
        sfRectangleShape_destroy(tmp->rect);
        sfClock_destroy(tmp->clock);
        free(tmp);
    }
    for (tower_t *tmp = radar->towers, *next; tmp; tmp = next) {
        next = tmp->next;
        sfRectangleShape_destroy(tmp->rect);
        sfCircleShape_destroy(tmp->circle);
        free(tmp);
    }
    free(radar);
}

void my_radar(char *str)
{
    radar_t *radar = init_radar(my_str_to_array(str, '\n'));

    sfMusic_setLoop(radar->music, sfTrue);
    sfMusic_play(radar->music);
    while (sfRenderWindow_isOpen(radar->wd))
        game_loop(radar);
    sfMusic_stop(radar->music);
    destroyer(radar);
}
