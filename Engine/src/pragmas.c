// converted from asm to c by Jonof

#include <stdio.h>
#include "platform.h"
#include "pragmas.h"

unsigned long getkensmessagecrc(long param) {
    return(0x56c764d4);
}


void clearbuf(void *d, long c, long a)
{
	long *p = (long*)d;
	while ((c--) > 0) *(p++) = a;
}

void clearbufbyte(void *D, long c, long a)
{ // Cringe City
	char *p = (char*)D;
	long m[4] = { 0xffl,0xff00l,0xff0000l,0xff000000l };
	long n[4] = { 0,8,16,24 };
	long z=0;
	while ((c--) > 0) {
		*(p++) = (char)((a & m[z])>>n[z]);
		z=(z+1)&3;
	}
}

void copybuf(void *s, void *d, long c)
{
	long *p = (long*)s, *q = (long*)d;
	while ((c--) > 0) *(q++) = *(p++);
}

void copybufbyte(void *S, void *D, long c)
{
	char *p = (char*)S, *q = (char*)D;
	while((c--) > 0) *(q++) = *(p++);
}

void copybufreverse(void *S, void *D, long c)
{
	char *p = (char*)S, *q = (char*)D;
	while((c--) > 0) *(q++) = *(p--);
}

void qinterpolatedown16(long bufptr, long num, long val, long add)
{ // gee, I wonder who could have provided this...
    long i, *lptr = (long *)bufptr;
    for(i=0;i<num;i++) { lptr[i] = (val>>16); val += add; }
}

void qinterpolatedown16short(long bufptr, long num, long val, long add)
{ // ...maybe the same person who provided this too?
    long i; short *sptr = (short *)bufptr;
    for(i=0;i<num;i++) { sptr[i] = (short)(val>>16); val += add; }
}

