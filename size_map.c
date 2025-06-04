#include "get_next_line.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int     fd;
    char    *line;

    fd = open("maps/map1.ber", O_RDONLY);
    line = get_next_line(fd);
    
    return (0);
}