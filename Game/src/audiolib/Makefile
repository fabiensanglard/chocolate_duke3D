CC=gcc
AR=ar
RANLIB=ranlib
CFLAGS=-g -O2
LDLIBS=

CFLAGS += $(shell sdl-config --cflags) -DPLATFORM_UNIX -D_BSD_SOURCE -D_XOPEN_SOURCE=700 -DBYTE_ORDER=LITTLE_ENDIAN -I /usr/include/SDL -I ../../../Engine/src/
LDLIBS += $(shell sdl-config --libs)

OBJ=fx_man.o dsl.o ll_man.o multivoc.o mv_mix.o mvreverb.o nodpmi.o \
	pitch.o user.o usrhooks.o

../audiolib.a: $(OBJ)
	rm -rf $@
	$(AR) rc $@ $^
	$(RANLIB) $@

clean:
	rm -rf ../audiolib.a *.o

distclean: clean
	rm -rf *~
