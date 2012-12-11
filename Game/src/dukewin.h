#ifndef _INCL_DUKEWIN_H_
#define _INCL_DUKEWIN_H_ 1

#ifndef _MSC_VER  /* might need this. */
typedef long long __int64;
#endif

#pragma warning(disable:4761)

#if USE_SDL
#include "SDL.h"
#endif

#ifdef _DEBUG
#define STUBBED(x) printf("STUB: %s in %s:%d\n", x, __FILE__, __LINE__)
#else
#define STUBBED(x)
#endif

#define __far
#define __interrupt

#define PATH_SEP_CHAR '\\'
#define PATH_SEP_STR  "\\"

#include <sys/stat.h>
#include <io.h>
#include <assert.h>

struct find_t
{
	long handle;
    struct _finddata_t data;
	char name[MAX_PATH];
};
int _dos_findfirst(char *filename, int x, struct find_t *f);
int _dos_findnext(struct find_t *f);

struct dosdate_t
{
    unsigned char day;
    unsigned char month;
    unsigned int year;
    unsigned char dayofweek;
};

void _dos_getdate(struct dosdate_t *date);

#ifndef min
#define min(x, y) ((x) < (y) ? (x) : (y))
#endif

#ifndef max
#define max(x, y) ((x) > (y) ? (x) : (y))
#endif

#ifdef FP_OFF
#undef FP_OFF
#endif
#define FP_OFF(x) ((long) (x))

// 64 megs should be enough for anybody.  :)  --ryan.
#define Z_AvailHeap() ((64 * 1024) * 1024)

#define printchrasm(x,y,ch) printf("%c", (char) (ch & 0xFF))

#define cdecl

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

#define S_IRUSR S_IREAD
#define S_IWUSR S_IWRITE
#define S_IRGRP 0
#define S_IWGRP 0

#define F_OK 0

#define HAVE_PRAGMA_PACK 1

#endif
