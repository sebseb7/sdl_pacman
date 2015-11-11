COMPILER = gcc
FLAGS= -O3 --std=gnu99 -Wall  -funsigned-char -Wundef -Wsign-compare  -Wstrict-prototypes 
LDFLAGS=

FLAGS+= `sdl2-config --cflags`
LDFLAGS+= `sdl2-config --libs`

all: pacman 

clean:
	rm -f pacman
	rm -f pacman.exe
	rm -f pacman_win.zip
	rm -f pacman.rc
	rm -f pacman.ico
	rm -f Pacman.app/Contents/MacOS/pacman_osx
	rm -f Pacman.app/Contents/Resources/iconfile.icns
	rm -f pacmanrc.o

pacman: main.c sdl_util.c sdl_util.h pacman.h pacman.c Makefile 
	@$(COMPILER) $(FLAGS) main.c pacman.c sdl_util.c $(LDFLAGS) -o pacman 

Pacman.app/Contents/MacOS/pacman_osx: main.c sdl_util.c sdl_util.h pacman.h pacman.c Makefile 
	$(COMPILER) $(FLAGS) main.c pacman.c sdl_util.c $(LDFLAGS) -o pacman_osx
	@install_name_tool -change /usr/local/opt/sdl2/lib/libSDL2-2.0.0.dylib @executable_path/../Frameworks/SDL2.framework/libSDL2-2.0.0.dylib pacman_osx
	@makeicns -32 pacman_36x36x4.png -out Pacman.app/Contents/Resources/iconfile.icns 
	@mv pacman_osx Pacman.app/Contents/MacOS
	cp -f /usr/local/lib/libSDL2-2.0.0.dylib Pacman.app/Contents/Frameworks/SDL2.framework/libSDL2-2.0.0.dylib
	@touch Pacman.app

pacman.ico: pacman_36x36x4.png Makefile
	icotool -c -o pacman.ico pacman_36x36x4.png

pacman.exe: pacman_36x36x4.png pacman.ico main.c sdl_util.c sdl_util.h pacman.h pacman.c Makefile SDL2-2.0.4
	echo "0 ICON pacman.ico" > pacman.rc
	i686-w64-mingw32-windres pacman.rc pacmanrc.o
	i686-w64-mingw32-gcc -static -std=gnu99 -ISDL2-2.0.4/i686-w64-mingw32/include/SDL2 -D_GNU_SOURCE=1 -Dmain=SDL_main -LSDL2-2.0.4/i686-w64-mingw32/lib  main.c pacman.c sdl_util.c -lmingw32 -lSDL2main -lSDL2 -mwindows -Wl,--no-undefined -lm -ldinput8 -ldxguid -ldxerr8 -luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 -lversion -luuid -static-libgcc  pacmanrc.o -o pacman.exe

pacman_win.zip: pacman.exe
	zip -j pacman_win.zip pacman.exe 

pacman_osx.zip: Pacman.app/Contents/MacOS/pacman_osx
	@zip -r pacman_osx.zip Pacman.app
	

SDL2-2.0.4:
	wget https://www.libsdl.org/tmp/release/SDL2-devel-2.0.4-mingw.tar.gz
	tar -xzf SDL2-devel-2.0.4-mingw.tar.gz
	rm -f SDL2-devel-2.0.4-mingw.tar.gz


.PHONY : clean all

