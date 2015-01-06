GCC  ?= gcc
MAKE ?= make
AR   ?= ar
RANLIB ?= ranlib

SOURCES=fx_man.c dsl.c ll_man.c multivoc.c mv_mix.c mvreverb.c nodpmi.c pitch.c user.c usrhooks.c
OBJECTS=fx_man.o dsl.o ll_man.o multivoc.o mv_mix.o mvreverb.o nodpmi.o pitch.o user.o usrhooks.o

../audiolib.a: $(SOURCES)
	$(GCC) $(CFLAGS) $(CPPFLAGS) $(shell sdl-config --cflags) \
		-DPLATFORM_UNIX -D_BSD_SOURCE -D_XOPEN_SOURCE=700 -DBYTE_ORDER=LITTLE_ENDIAN \
		-I /usr/include/SDL/ -I ../../../Engine/src/ -c $(SOURCES)
	$(AR) rc $@ $^
	$(RANLIB) $@

clean:
	rm -f ../audiolib.a *.o

