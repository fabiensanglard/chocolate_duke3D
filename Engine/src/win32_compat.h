/*
 * win32 compatibility header. Takes care of some legacy code issues
 *  and incompatibilities at the source level.
 *
 *  Written by Ryan C. Gordon (icculus@clutteredmind.org)
 *
 * Please do NOT harrass Ken Silverman about any code modifications
 *  (including this file) to BUILD.
 */

/*
 * "Build Engine & Tools" Copyright (c) 1993-1997 Ken Silverman
 * Ken Silverman's official web site: "http://www.advsys.net/ken"
 * See the included license file "BUILDLIC.TXT" for license info.
 * This file IS NOT A PART OF Ken Silverman's original release
 */
  
#ifndef _INCLUDE_WIN32_COMPAT_H_
#define _INCLUDE_WIN32_COMPAT_H_

#if (!defined PLATFORM_WIN32)
#error PLATFORM_WIN32 is not defined.
#endif

#define PLATFORM_SUPPORTS_SDL

#include <stdio.h>

#if (!defined _MSC_VER)
#include <unistd.h>
#endif

#include <stdlib.h>
#include <io.h>
#include <direct.h>
#include <conio.h>
#include <dos.h>
#include <assert.h>

extern const int hbits[];   /* !!! what is this, and why is it here? */

/*
  Do some bitwise magic to approximate an algebraic (sign preserving)
  right shift.
 */
#define shift_algebraic_right(value,distance) \
(((value) >> (distance))| \
 (hbits[(distance) + (((value) & 0x80000000) >> 26)]))

/* !!! remove me later! */
/* !!! remove me later! */
/* !!! remove me later! */
#define outpw(x, y)   printf("outpw(0x%X, 0x%X) call in %s, line %d.\n", \
                              (x), (y), __FILE__, __LINE__)

#define koutpw(x, y)  printf("koutpw(0x%X, 0x%X) call in %s, line %d.\n", \
                              (x), (y), __FILE__, __LINE__)

#define outb(x, y)    printf("outb(0x%X, 0x%X) call in %s, line %d.\n", \
                              (x), (y), __FILE__, __LINE__)

#define koutb(x, y)   printf("koutb(0x%X, 0x%X) call in %s, line %d.\n", \
                              (x), (y), __FILE__, __LINE__)

#define outp(x, y)    printf("outp(0x%X, 0x%X) call in %s, line %d.\n", \
                              (x), (y), __FILE__, __LINE__)

#define koutp(x, y)   printf("koutp(0x%X, 0x%X) call in %s, line %d.\n", \
                              (x), (y), __FILE__, __LINE__)

#define kinp(x)       _kinp_handler((x), __FILE__, __LINE__)
#define inp(x)        _inp_handler((x), __FILE__, __LINE__)

int _inp_handler(int port, char *source_file, int source_line);
int _kinp_handler(int port, char *source_file, int source_line);
/* !!! remove me later! */
/* !!! remove me later! */
/* !!! remove me later! */


#define __far
#define __interrupt
#define interrupt
#define far
#define kmalloc(x) malloc(x)
#define kkmalloc(x) malloc(x)
#define kfree(x) free(x)
#define kkfree(x) free(x)

#ifdef FP_OFF
#undef FP_OFF
#endif

#define FP_OFF(x) ((long) (x))

/* !!! This might be temporary. */
#define printext16 printext256
#define printext16_noupdate printext256_noupdate

#ifndef max
#define max(x, y)  (((x) > (y)) ? (x) : (y))
#endif

#ifndef min
#define min(x, y)  (((x) < (y)) ? (x) : (y))
#endif

#if (defined __WATCOMC__)
#define inline
#pragma intrinsic(min);
#pragma intrinsic(max);
#define __int64 long long
#endif

#if (defined _MSC_VER)
#if ((!defined _INTEGRAL_MAX_BITS) || (_INTEGRAL_MAX_BITS < 64))
#error __int64 type not supported
#endif

#define open _open
#define O_BINARY _O_BINARY
#define O_RDONLY _O_RDONLY
#define O_WRONLY _O_WRONLY
#define O_RDWR _O_RDWR
#define O_TRUNC _O_TRUNC
#define O_CREAT _O_CREAT
#define S_IREAD _S_IREAD
#define S_IWRITE _S_IWRITE
#define S_IRDWR _S_IRDWR
#endif /* defined _MSC_VER */

#endif

/* end of win32_compat.h ... */



