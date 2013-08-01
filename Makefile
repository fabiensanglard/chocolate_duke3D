all:
	cd Engine/src && make
	cd Game/src && make
	gcc libGame.a libEngine.a `pkg-config --cflags --libs sdl SDL_mixer` -o chocolate-duke3d

clean:
	cd Game/src && make clean
	cd Engine/src && make clean
	rm chocolate-duke3d
