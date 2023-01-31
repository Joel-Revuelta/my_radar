/*
** EPITECH PROJECT, 2022
** my_radar
** File description:
** radar
*/

#ifndef RADAR_H_
    #define RADAR_H_

    #include "my.h"

    #include <SFML/Audio.h>
    #include <SFML/Graphics.h>
    #include <SFML/System.h>
    #include <SFML/Window.h>
    #include <time.h>
    #include <math.h>
    #include <stdbool.h>

    #define WIDTH 1920
    #define HEIGHT 1080
    #define BPP 32

    #define FONT "assets/font.ttf"

    #define P_SIZE 20

    typedef struct plane_s {
        sfRectangleShape *rect;
        sfVector2f pos;
        sfVector2f end;
        sfVector2f step;
        int delay;
        sfClock *clock;
        sfFloatRect hitbox;
        sfBool del;
        int id;
        struct plane_s *next;
    } plane_t;

    typedef struct tower_s {
        sfRectangleShape *rect;
        sfCircleShape *circle;
        struct tower_s *next;
    } tower_t;

    typedef struct radar_s {
        sfRenderWindow *wd;
        sfEvent evt;
        plane_t *planes;
        tower_t *towers;
        sfSprite *bg;
        sfClock *timer;
        sfText *t_txt;
        sfMusic *music;
        sfBool l_option;
        sfBool s_option;
    } radar_t;

    sfRenderWindow *create_window(char *name, int x, int y, int fr);
    sfSprite *create_sprite(char *filepath, int x, int y);
    sfSound *create_sound(char *filepath);
    sfCircleShape *create_circle(sfVector2f pos, float radius);
    sfRectangleShape *create_rect(char *fp, sfVector2f pos, sfVector2f sz);
    sfText *create_text(char *font_fp, char *str, sfVector2f pos, int size);
    radar_t *init_radar(char **info);
    void events(radar_t *radar);
    void display(radar_t *radar);
    sfBool is_in_tower(plane_t *plane, radar_t *radar);
    sfFloatRect get_hitbox(plane_t *plane);
    plane_t *free_plane(plane_t **planes, plane_t *prev, plane_t *curr);
    void check_crash(plane_t **pl, plane_t *, plane_t **planes, radar_t *radar);
    sfFloatRect get_hitbox(plane_t *plane);
    sfVector2f *get_r_corners(sfFloatRect hitbox, float angle);
    sfVector2f rotate_point(sfVector2f point, sfVector2f center, float angle);
    sfVector2f get_step(sfVector2f a, sfVector2f b, int speed);
    float get_angle(sfVector2f a, sfVector2f b);

#endif /* !RADAR_H_ */
