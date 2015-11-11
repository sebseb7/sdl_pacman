
#include <time.h>
#include <stdlib.h>



#include "sdl_util.h"
#include "pacman.h"



int main(int argc __attribute__((__unused__)), char *argv[] __attribute__((__unused__))) 
{
	srand(time(NULL));
	

	
	int zoom = 25;

	unsigned int* pixelbuffer = sdl_init(23*zoom, 24*zoom,"Pacman",60);

	pacman_init();


	int limiter=0;

	while(sdl_handle_events(pixelbuffer)) //limits loop to 60fps
	{
		while(sdl_limit_fps(&limiter,30))
		{
			pacman_tick(getkey);
			release_upped_keys();
		}
			
		pacman_render(pixelbuffer,zoom);

	}
	sdl_deinit();
	return 0;
}

