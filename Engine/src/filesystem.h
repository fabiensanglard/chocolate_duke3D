//
//  filesystem.h
//  Duke3D
//
//  Created by fabien sanglard on 12-12-19.
//  Copyright (c) 2012 fabien sanglard. All rights reserved.
//

#ifndef Duke3D_filesystem_h
#define Duke3D_filesystem_h

#include "stdio.h"
#include "platform.h"

#define MAXGROUPFILES 4     /* Warning: Fix groupfil if this is changed */
#define MAXOPENFILES 64     /* Warning: Fix filehan if this is changed  */

int32_t initgroupfile(const char  *filename);
void uninitgroupfile(void);
uint16_t crc16(uint8_t  *data_p, uint16_t length);
unsigned int crc32_update(uint8_t  *buf, unsigned int length, unsigned int crc_to_update);
int32_t kopen4load(const char  *filename, int readfromGRP);
int32_t kread(int32_t handle, void *buffer, int32_t leng);
int kread8(int32_t handle, uint8_t  *buffer);
int kread16(int32_t handle, short *buffer);
int kread32(int32_t handle, int32_t *buffer);
int32_t klseek(int32_t handle, int32_t offset, int32_t whence);
int32_t kfilelength(int32_t handle);
void kclose(int32_t handle);
void kdfread(void *buffer, size_t dasizeof, size_t count, int32_t fil);
void dfread(void *buffer, size_t dasizeof, size_t count, FILE *fil);
void dfwrite(void *buffer, size_t dasizeof, size_t count, FILE *fil);
int32_t compress(uint8_t  *lzwinbuf, int32_t uncompleng, uint8_t  *lzwoutbuf);
int32_t uncompress(uint8_t  *lzwinbuf, int32_t compleng, uint8_t  *lzwoutbuf);

extern char*  getGameDir(void);
extern void   setGameDir(char* gameDir);

extern int32_t TCkopen4load(const char  *filename, int readfromGRP);

#ifdef __APPLE__
    int32_t filelength(int32_t fd);
#endif

#endif
