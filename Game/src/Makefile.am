SUBDIRS = audiolib midi

noinst_LIBRARIES = libGame.a
libGame_a_SOURCES = \
	actors.c animlib.c config.c console.c control.c cvar_defs.c cvars.c dummy_audiolib.c game.c \
	gamedef.c global.c keyboard.c menues.c player.c premap.c rts.c scriplib.c sector.c sounds.c
libGame_a_LIBADD = audiolib/libaudio.a midi/libmidi.a
libGame_a_CFLAGS = -I$(top_srcdir)/Engine/src

# starting a new game will lead to a crash if built with -O1/-O2/-O3
premap.o: CFLAGS+=-O0
