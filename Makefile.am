SUBDIRS = Game/src Engine/src

bin_PROGRAMS = chocolate-duke3d
chocolate_duke3d_SOURCES =
chocolate_duke3d_LDADD = \
	Game/src/libGame.a \
	Game/src/audiolib/libaudio.a \
	Game/src/midi/libmidi.a \
	Engine/src/libEngine.a \
	$(SDL_LIBS) $(SDL_MIXER_LIBS)

doc_DATA = README.md

pixmapdir = $(datadir)/pixmaps
pixmap_DATA = Game/duke_icon.png
