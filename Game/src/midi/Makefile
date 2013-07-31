SOURCES=sdl_midi.c
OBJECTS=sdl_midi.o

../libmidi.a: $(SOURCES)
	gcc -DPLATFORM_UNIX -D_BSD_SOURCE -D_XOPEN_SOURCE=700 -DBYTE_ORDER=LITTLE_ENDIAN -I /usr/include/SDL/ -I ../../../Engine/src/ -c $(SOURCES)
	ar cru ../libmidi.a $(OBJECTS)
	ranlib ../libmidi.a

clean:
	rm ../libmidi.a $(OBJECTS)
