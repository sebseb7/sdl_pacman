#ifndef _PACMAN_H
#define _PACMAN_H

void pacman_tick(int getkey(int));
void pacman_init(void);
void pacman_render(unsigned int* pixelbuffer,int zoom);

#endif

