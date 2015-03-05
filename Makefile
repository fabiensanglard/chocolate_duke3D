CC     ?= gcc
MAKE   ?= make
AR     ?= ar
RANLIB ?= ranlib


D3D_CFLAGS   = -m32 -O2 $(shell pkg-config --cflags sdl SDL_mixer) -Wall -Wno-unused-result -Wno-unused-function \
				-Wno-unused-but-set-variable -Wno-parentheses -Wno-maybe-uninitialized $(CFLAGS)
D3D_CPPFLAGS = -DPLATFORM_UNIX $(CPPFLAGS)
D3D_LDFLAGS  = -m32 $(LDFLAGS)
D3D_LIBS     = $(shell pkg-config --libs sdl SDL_mixer) $(LIBS)


GAME_SRCS = $(addprefix Game/src/, \
	actors.c animlib.c config.c console.c control.c cvar_defs.c cvars.c dummy_audiolib.c game.c gamedef.c global.c \
	keyboard.c menues.c player.c premap.c rts.c scriplib.c sector.c sounds.c midi/sdl_midi.c)

GAME_SRCS += $(addprefix Game/src/audiolib/, \
	fx_man.c dsl.c ll_man.c multivoc.c mv_mix.c mvreverb.c nodpmi.c pitch.c user.c)

ENGINE_SRCS = $(addprefix Engine/src/, \
	cache.c display.c draw.c dummy_multi.c engine.c filesystem.c fixedPoint_math.c mmulti.c network.c tiles.c)

GAME_OBJS   = $(GAME_SRCS:%.c=%.o)
ENGINE_OBJS = $(ENGINE_SRCS:%.c=%.o)


all: chocolate-duke3d

chocolate-duke3d: libGame.a libEngine.a
	$(CC) $(D3D_LDFLAGS) $^ $(D3D_LIBS) -o $@

libGame.a: $(GAME_OBJS)
	$(AR) cru $@ $^
	$(RANLIB) $@

libEngine.a: $(ENGINE_OBJS)
	$(AR) cru $@ $^
	$(RANLIB) $@

%.o: %.c
	$(CC) -c $(D3D_CFLAGS) $(D3D_CPPFLAGS) -o $@ $<

clean:
	rm -f $(ENGINE_OBJS) $(GAME_OBJS)
	rm -f libEngine.a libGame.a
	rm -f chocolate-duke3d

distclean: clean

