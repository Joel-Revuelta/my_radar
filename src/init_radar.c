/*
** EPITECH PROJECT, 2022
** my_radar
** File description:
** init_radar
*/

#include "radar.h"



void init_plane(plane_t **planes, char **info)
{
    static int id = 0;
    plane_t *new = malloc(sizeof(plane_t));
    char **st = my_str_to_array(info[1], ' ');
    char **end = my_str_to_array(info[2], ' ');

    new->pos = (sfVector2f){my_getnbr(st[0]), my_getnbr(st[1])};
    new->end = (sfVector2f){my_getnbr(end[0]), my_getnbr(end[1])};
    new->step = get_step(new->pos, new->end, my_getnbr(info[3]));
    new->delay = my_getnbr(info[4]);
    new->rect = create_rect("assets/plane.png", new->pos, (sfVector2f){20, 20});
    sfRectangleShape_setOutlineThickness(new->rect, 1);
    sfRectangleShape_setOutlineColor(new->rect, sfYellow);
    sfRectangleShape_setOrigin(new->rect, (sfVector2f){10, 10});
    sfRectangleShape_setRotation(new->rect, get_angle(new->pos, new->end));
    new->hitbox = get_hitbox(new);
    new->clock = sfClock_create();
    new->del = sfFalse;
    new->id = id;
    id += 1;
    new->next = *planes;
    *planes = new;
}

void init_tower(tower_t **towers, char **info)
{
    tower_t *new = malloc(sizeof(tower_t));
    char **pos_str = my_str_to_array(info[1], ' ');
    sfVector2f pos = (sfVector2f){my_getnbr(pos_str[0]), my_getnbr(pos_str[1])};
    int rad = my_getnbr(info[2]);

    new->rect = create_rect("assets/tower.png", pos, (sfVector2f){50, 50});
    new->circle = create_circle(pos, rad);
    sfRectangleShape_setOrigin(new->rect, (sfVector2f){25, 25});
    sfCircleShape_setOrigin(new->circle, (sfVector2f){rad, rad});
    new->next = *towers;
    *towers = new;
}

void check_line(char **line)
{
    bool error = false;
    int len = my_arr_len(line);

    if (len != 5 && len != 3 && len != 1)
        error = true;
    if (line[0][0] != 'A' && line[0][0] != 'T' && len != 1)
        error = true;
    for (int i = 1; line[i]; i++)
        if (my_getnbr(line[i]) < 0)
            error = true;
    if (error) {
        write(2, "Invalid file", 12);
        exit(84);
    }
}

radar_t *init_radar(char **info)
{
    radar_t *radar = malloc(sizeof(radar_t));
    radar->planes = NULL;
    radar->towers = NULL;
    radar->wd = create_window("Radar", 30);
    radar->bg = create_sprite("assets/background.png", 0, 0);
    radar->timer = sfClock_create();
    radar->t_txt = create_text(FONT, "00:00", (sfVector2f){1775, -10}, 100);
    radar->music = sfMusic_createFromFile("assets/keyboard_cat.ogg");
    radar->l_option = sfFalse;
    radar->s_option = sfFalse;

    for (int i = 0; info[i]; i++) {
        check_line(my_str_to_array(info[i], '\t'));
        if (info[i][0] == 'A')
            init_plane(&radar->planes, my_str_to_array(info[i], '\t'));
        if (info[i][0] == 'T')
            init_tower(&radar->towers, my_str_to_array(info[i], '\t'));
    }
    return (radar);
}
