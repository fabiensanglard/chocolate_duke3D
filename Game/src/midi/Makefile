GCC  ?= gcc
MAKE ?= make
AR   ?= ar
RANLIB ?= ranlib

SOURCES=sdl_midi.c
OBJECTS=sdl_midi.o

../libmidi.a: $(SOURCES)
	$(GCC) $(CFLAGS) $(CPPFLAGS) -DPLATFORM_UNIX -D_BSD_SOURCE -D_XOPEN_SOURCE=700 -DBYTE_ORDER=LITTLE_ENDIAN \
		-I /usr/include/SDL/ -I ../../../Engine/src/ -c $(SOURCES)
	$(AR) cru $@ $^
	$(RANLIB) $@

clean:
	rm -f ../libmidi.a *.o
