/*
 * Cache1d declarations.
 *
 *  Written by Ryan C. Gordon. (icculus@clutteredmind.org)
 *
 * Please do NOT harrass Ken Silverman about any code modifications
 *  (including this file) to BUILD.
 */

/*
 * "Build Engine & Tools" Copyright (c) 1993-1997 Ken Silverman
 * Ken Silverman's official web site: "http://www.advsys.net/ken"
 * See the included license file "BUILDLIC.TXT" for license info.
 * This file has been modified from Ken Silverman's original release
 */

#ifndef _INCLUDE_CACHE1D_H_
#define _INCLUDE_CACHE1D_H_

#define MAXGROUPFILES 4     /* Warning: Fix groupfil if this is changed */
#define MAXOPENFILES 64     /* Warning: Fix filehan if this is changed  */

void initcache(long dacachestart, long dacachesize);
void allocache (long *newhandle, long newbytes, unsigned char *newlockptr);
void suckcache (long *suckptr);
void agecache(void);
void reportandexit(char *errormessage);
long initgroupfile(const char *filename);
void uninitgroupfile(void);
unsigned short crc16(char *data_p, unsigned short length);
unsigned int crc32_update(unsigned char *buf, unsigned int length, unsigned int crc_to_update);
long kopen4load(const char *filename, int readfromGRP);
long kread(long handle, void *buffer, long leng);
int kread8(long handle, char *buffer);
int kread16(long handle, short *buffer);
int kread32(long handle, long *buffer);
long klseek(long handle, long offset, long whence);
long kfilelength(long handle);
void kclose(long handle);
void kdfread(void *buffer, size_t dasizeof, size_t count, long fil);
void dfread(void *buffer, size_t dasizeof, size_t count, FILE *fil);
void dfwrite(void *buffer, size_t dasizeof, size_t count, FILE *fil);
long compress(char *lzwinbuf, long uncompleng, char *lzwoutbuf);
long uncompress(char *lzwinbuf, long compleng, char *lzwoutbuf);

extern char game_dir[512];
extern long TCkopen4load(const char *filename, int readfromGRP);

#endif  /* !defined _INCLUDE_CACHE1D_H_ */

/* end of cache1d.h ... */



