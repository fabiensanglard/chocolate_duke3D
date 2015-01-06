GCC  ?= gcc
MAKE ?= make
AR   ?= ar
RANLIB ?= ranlib


SOURCES=cache.c display.c draw.c dummy_multi.c engine.c filesystem.c fixedPoint_math.c mmulti.c network.c tiles.c
OBJECTS=cache.o display.o draw.o dummy_multi.o engine.o filesystem.o fixedPoint_math.o mmulti.o network.o tiles.o

../../libEngine.a: $(SOURCES)
	$(GCC) $(CFLAGS) $(CPPFLAGS) -DPLATFORM_UNIX -DBYTE_ORDER=LITTLE_ENDIAN -D_XOPEN_SOURCE=500 \
		-I /usr/include/SDL -I enet/include -c $(SOURCES)
	$(AR) cru ../../libEngine.a $(OBJECTS)
	$(RANLIB) ../../libEngine.a

clean:
	rm -f *.o ../../libEngine.a
