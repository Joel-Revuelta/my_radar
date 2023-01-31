/*
** EPITECH PROJECT, 2022
** my_radar
** File description:
** main
*/

#include "radar.h"

void print_help(void)
{
    my_putstr("Air traffic simulation panel\n\nUSAGE\n\t./my_radar [OPTIONS] \
path_to_script\n\tpath_to_script\tThe path to the script file.\n\nOPTIONS\n\
\t-h\t\tprint the usage and quit.\n\nUSAGE INTERACTIONS\n\t'L' key\t\t\
enable/disable hitboxes and areas.\n\t'S' key\t\tenable/disable sprites.\n");
}

int error_handling(int ac, char **av)
{
    char *str = NULL;

    if (ac != 2)
        return (1);
    if ((str = open_file(av[1])) == NULL || my_strlen(str) < 2) {
        free(str);
        return (1);
    }
    free(str);
    return (0);
}

int main(int ac, char **av)
{
    if (ac == 2 && my_strcmp(av[1], "-h") == 0) {
        print_help();
        return (0);
    }
    if (error_handling(ac, av))
        return (84);
    my_radar(open_file(av[1]));
    return (0);
}
