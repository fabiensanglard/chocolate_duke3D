GCC  ?= gcc
MAKE ?= make
AR   ?= ar
RANLIB ?= ranlib


SOURCES=actors.c animlib.c config.c console.c control.c cvar_defs.c cvars.c dummy_audiolib.c \
	game.c gamedef.c global.c keyboard.c menues.c player.c premap.c rts.c scriplib.c sector.c sounds.c
OBJECTS=actors.o animlib.o config.o console.o control.o cvar_defs.o cvars.o dummy_audiolib.o \
	game.o gamedef.o global.o keyboard.o menues.o player.o premap.o rts.o scriplib.o sector.o sounds.o

../../libGame.a: audiolib.a libmidi.a $(SOURCES)
	$(GCC) $(CFLAGS) $(CPPFLAGS) -DPLATFORM_UNIX -D_BSD_SOURCE -D_XOPEN_SOURCE=700 \
		-I /usr/include/SDL/ -I ../../Engine/src/ -c $(SOURCES)
	$(AR) cru ../../libGame.a $(OBJECTS) audiolib/*.o midi/*.o
	$(RANLIB) ../../libGame.a

audiolib.a:
	cd audiolib && $(MAKE)
libmidi.a:
	cd midi && $(MAKE)

clean:
	rm -f *.o ../../libGame.a
	cd midi && $(MAKE) clean
	cd audiolib && $(MAKE) clean
