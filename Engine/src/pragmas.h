/*
 * "Build Engine & Tools" Copyright (c) 1993-1997 Ken Silverman
 * Ken Silverman's official web site: "http://www.advsys.net/ken"
 * See the included license file "BUILDLIC.TXT" for license info.
 * This file has been modified from Ken Silverman's original release
 */

#ifndef __PRAGMAS_H__
#define __PRAGMAS_H__

#include "platform.h" //for __int64

static __inline void swapchar(unsigned char *p1, unsigned char *p2)
{ unsigned char tmp = *p1; *p1 = *p2; *p2 = tmp; }
static __inline void swapshort(short *p1, short *p2)
{ short tmp = *p1; *p1 = *p2; *p2 = tmp; }
static __inline void swaplong(long *p1, long *p2)
{ long tmp = *p1; *p1 = *p2; *p2 = tmp; }
static __inline void swapchar2(unsigned char *p1, unsigned char *p2, int xsiz)
{
    swapchar(p1, p2);
    swapchar(p1 + 1, p2 + xsiz);
}


unsigned long getkensmessagecrc(long param);

static __inline long msqrtasm(unsigned long c)
{
	unsigned long a,b;

	a = 0x40000000l;		// mov eax, 0x40000000
	b = 0x20000000l;		// mov ebx, 0x20000000
	do {				// begit:
		if (c >= a) {		// cmp ecx, eax	 /  jl skip
			c -= a;		// sub ecx, eax
			a += b*4;	// lea eax, [eax+ebx*4]
		}			// skip:
		a -= b;			// sub eax, ebx
		a >>= 1;		// shr eax, 1
		b >>= 2;		// shr ebx, 2
	} while (b);			// jnz begit
	if (c >= a)			// cmp ecx, eax
		a++;			// sbb eax, -1
	a >>= 1;			// shr eax, 1
	return a;
}

void vlin16first (long i1, long i2);

static __inline int sqr (int input1) { return input1*input1; }

/* internal use:32x32 = 64bit */
static __inline __int64 mul32_64(int i1,int i2)
{
	return (__int64)i1*i2;
}
static __inline int scale (int input1, int input2, int input3)
{
	return mul32_64(input1,input2)/input3;
}
static __inline int mulscale (int input1, int input2, int input3)
{
	return mul32_64(input1,input2)>>input3;
}
static __inline int dmulscale  (int input1, int input2, int input3,int input4,int input5)
{
	return (mul32_64(input1,input2) + mul32_64(input3,input4))>>input5;
}
static __inline int tmulscale(int i1, int i2, int i3, int i4, int i5, int i6,int shift)
{
	return (mul32_64(i1,i2) + mul32_64(i3,i4) + mul32_64(i5,i6))>>shift;
}
static __inline int divscale(int i1, int i2, int i3)
{
	return ((__int64)i1<<i3)/i2;
}

#define DEFFUNCS \
DEFFUN(1)\
DEFFUN(2)\
DEFFUN(3)\
DEFFUN(4)\
DEFFUN(5)\
DEFFUN(6)\
DEFFUN(7)\
DEFFUN(8)\
DEFFUN(9)\
DEFFUN(10)\
DEFFUN(11)\
DEFFUN(12)\
DEFFUN(13)\
DEFFUN(14)\
DEFFUN(15)\
DEFFUN(16)\
DEFFUN(17)\
DEFFUN(18)\
DEFFUN(19)\
DEFFUN(20)\
DEFFUN(21)\
DEFFUN(22)\
DEFFUN(23)\
DEFFUN(24)\
DEFFUN(25)\
DEFFUN(26)\
DEFFUN(27)\
DEFFUN(28)\
DEFFUN(29)\
DEFFUN(30)\
DEFFUN(31)\
DEFFUN(32)

#define DEFFUN(N) \
static __inline int mulscale##N(int input1, int input2) \
{ return mulscale(input1,input2,N); }
DEFFUNCS
#undef DEFFUN

#define DEFFUN(N) \
static __inline int dmulscale##N(int input1, int input2,int input3,int input4) \
{ return dmulscale(input1,input2,input3,input4,N); }
DEFFUNCS
#undef DEFFUN

#define DEFFUN(N) \
static __inline int tmulscale##N(int i1, int i2,int i3,int i4,int i5,int i6) \
{ return tmulscale(i1,i2,i3,i4,i5,i6,N); }
DEFFUNCS
#undef DEFFUN

#define DEFFUN(N) \
static __inline int divscale##N(int input1, int input2) \
{ return divscale(input1,input2,N); }
DEFFUNCS
#undef DEFFUN

static __inline int ksgn(int i1)
{
  if (i1 < 0) return -1;
  else if (i1 > 0) return 1;
  else return 0;
}

static __inline int sgn(int i1) { return ksgn(i1); }
static __inline int klabs (int i1)
{
  if (i1 < 0) i1 = -i1;
  return i1;
}
static __inline int mul3 (int i1) { return i1*3; }
static __inline int mul5 (int i1) { return i1*5; }
static __inline int mul9 (int i1) { return i1*9; }

void copybufreverse(void *S, void *D, long c);
void copybuf(void *s, void *d, long c);
void clearbuf(void *d, long c, long a);
void clearbufbyte(void *D, long c, long a);
void copybufbyte(void *S, void *D, long c);

void qinterpolatedown16 (long bufptr, long num, long val, long add);
void qinterpolatedown16short (long bufptr, long num, long val, long add);

#endif /* !defined _INCLUDE_PRAGMAS_H_ */


