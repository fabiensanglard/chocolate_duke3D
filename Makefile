GCC  ?= gcc
MAKE ?= make


all:
	cd Engine/src && $(MAKE)
	cd Game/src && $(MAKE)
	$(GCC) $(LDFLAGS) libGame.a libEngine.a `pkg-config --cflags --libs sdl SDL_mixer` -o chocolate-duke3d

clean:
	cd Game/src && $(MAKE) clean
	cd Engine/src && $(MAKE) clean
	rm -f chocolate-duke3d

distclean: clean

