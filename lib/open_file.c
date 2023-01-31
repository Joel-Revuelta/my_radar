/*
** EPITECH PROJECT, 2022
** bs_myls
** File description:
** open_file
*/

#include "my.h"

char *open_file(char *path)
{
    struct stat st;
    int fd = open(path, O_RDONLY);
    char *buff = NULL;
    int rd = 0;

    if (fd == -1 || stat(path, &st) == -1) {
        close(fd);
        return (NULL);
    }
    buff = malloc(st.st_size + 1);
    if (read(fd, buff, st.st_size) < 0) {
        close(fd);
        free(buff);
        return (NULL);
    }
    buff[st.st_size] = '\0';
    close(fd);
    return (buff);
}
