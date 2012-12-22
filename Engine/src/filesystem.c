//
//  filesystem.c
//  Duke3D
//
//  Created by fabien sanglard on 12-12-19.
//  Copyright (c) 2012 fabien sanglard. All rights reserved.
//

#include "filesystem.h"

#include "platform.h"
#include "cache.h"
#include "fixedPoint_math.h"
#include "../../Game/src/global.h"

char game_dir[512];

uint8_t  toupperlookup[256] =
{
	0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,
	0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1a,0x1b,0x1c,0x1d,0x1e,0x1f,
	0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2a,0x2b,0x2c,0x2d,0x2e,0x2f,
	0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3a,0x3b,0x3c,0x3d,0x3e,0x3f,
	0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4a,0x4b,0x4c,0x4d,0x4e,0x4f,
	0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5a,0x5b,0x5c,0x5d,0x5e,0x5f,
	0x60,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4a,0x4b,0x4c,0x4d,0x4e,0x4f,
	0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5a,0x7b,0x7c,0x7d,0x7e,0x7f,
	0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,
	0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9a,0x9b,0x9c,0x9d,0x9e,0x9f,
	0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,
	0xb0,0xb1,0xb2,0xb3,0xb4,0xb5,0xb6,0xb7,0xb8,0xb9,0xba,0xbb,0xbc,0xbd,0xbe,0xbf,
	0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,
	0xd0,0xd1,0xd2,0xd3,0xd4,0xd5,0xd6,0xd7,0xd8,0xd9,0xda,0xdb,0xdc,0xdd,0xde,0xdf,
	0xe0,0xe1,0xe2,0xe3,0xe4,0xe5,0xe6,0xe7,0xe8,0xe9,0xea,0xeb,0xec,0xed,0xee,0xef,
	0xf0,0xf1,0xf2,0xf3,0xf4,0xf5,0xf6,0xf7,0xf8,0xf9,0xfa,0xfb,0xfc,0xfd,0xfe,0xff,
};

int32_t numgroupfiles = 0;			// number of GRP files actually used.
int32_t gnumfiles[MAXGROUPFILES];	// number of files on grp
int32_t groupfil[MAXGROUPFILES] = {-1,-1,-1,-1}; // grp file handles
int32_t groupfilpos[MAXGROUPFILES];
uint8_t  *gfilelist[MAXGROUPFILES];	// name list + size list of all the files in grp
int32_t *gfileoffs[MAXGROUPFILES];	// offset of the files
uint8_t  *groupfil_memory[MAXGROUPFILES]; // addresses of raw GRP files in memory
int32_t groupefil_crc32[MAXGROUPFILES];

uint8_t  filegrp[MAXOPENFILES];
int32_t filepos[MAXOPENFILES];
int32_t filehan[MAXOPENFILES] =
{
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
};



int32_t initgroupfile(const char  *filename)
{
	uint8_t  buf[16];
	int32_t i, j, k;
    
	printf("Loading %s ...\n", filename);
    
	if (numgroupfiles >= MAXGROUPFILES) return(-1);
    
	groupfil_memory[numgroupfiles] = NULL; // addresses of raw GRP files in memory
	groupefil_crc32[numgroupfiles] = 0;
    
	groupfil[numgroupfiles] = open(filename,O_BINARY|O_RDWR,S_IREAD);
	if (groupfil[numgroupfiles] >= 0)
	{
		groupfilpos[numgroupfiles] = 0;
		read(groupfil[numgroupfiles],buf,16);
		if ((buf[0] != 'K') || (buf[1] != 'e') || (buf[2] != 'n') ||
            (buf[3] != 'S') || (buf[4] != 'i') || (buf[5] != 'l') ||
            (buf[6] != 'v') || (buf[7] != 'e') || (buf[8] != 'r') ||
            (buf[9] != 'm') || (buf[10] != 'a') || (buf[11] != 'n'))
		{
			close(groupfil[numgroupfiles]);
			groupfil[numgroupfiles] = -1;
			return(-1);
		}
        
		//FCS: The ".grp" file format is just a collection of a lot of files stored into 1 big one.
		//I tried to make the format as simple as possible: The first 12 bytes contains my name,
		//"KenSilverman". The next 4 bytes is the number of files that were compacted into the
		//group file. Then for each file, there is a 16 byte structure, where the first 12
		//bytes are the filename, and the last 4 bytes are the file's size. The rest of the
		//group file is just the raw data packed one after the other in the same order as the list
		//of files. - ken
        
		gnumfiles[numgroupfiles] = BUILDSWAP_INTEL32(*((int32_t *)&buf[12]));
        
		if ((gfilelist[numgroupfiles] = (uint8_t  *)kmalloc(gnumfiles[numgroupfiles]<<4)) == 0)
        { Error(EXIT_FAILURE, "Not enough memory for file grouping system\n"); }
		if ((gfileoffs[numgroupfiles] = (int32_t *)kmalloc((gnumfiles[numgroupfiles]+1)<<2)) == 0)
        { Error(EXIT_FAILURE, "Not enough memory for file grouping system\n"); }
        
		// load index (name+size)
		read(groupfil[numgroupfiles],gfilelist[numgroupfiles],gnumfiles[numgroupfiles]<<4);
        
		j = 0;
		for(i=0;i<gnumfiles[numgroupfiles];i++)
		{
			k = BUILDSWAP_INTEL32(*((int32_t *)&gfilelist[numgroupfiles][(i<<4)+12])); // get size
			gfilelist[numgroupfiles][(i<<4)+12] = 0;
			gfileoffs[numgroupfiles][i] = j; // absolute offset list of all files. 0 for 1st file
			j += k;
		}
		gfileoffs[numgroupfiles][gnumfiles[numgroupfiles]] = j;
	}
    else
    {
        printf("Unable to find GRP file %s.\n",filename);
		//Let user see the message
		getchar();
        exit(0);
    }
    
	// Compute CRC32 of thw whole grp and implicitely caches the GRP in memory through windows
	lseek(groupfil[numgroupfiles], 0, SEEK_SET);
    
	i = 1000000; // FIX_00086: grp loaded by smaller sucessive chunks to avoid overloading low ram computers
	groupfil_memory[numgroupfiles] = malloc(i);
	while((j=read(groupfil[numgroupfiles], groupfil_memory[numgroupfiles], i)))
	{
		groupefil_crc32[numgroupfiles] = crc32_update((uint8_t *)groupfil_memory[numgroupfiles], j, groupefil_crc32[numgroupfiles]);
	}
    
	free(groupfil_memory[numgroupfiles]);
	groupfil_memory[numgroupfiles] = 0;
    
	numgroupfiles++;
	return(groupfil[numgroupfiles-1]);
    
}

void uninitgroupfile(void)
{
	int32_t i;
    
	for(i=numgroupfiles-1;i>=0;i--)
		if (groupfil[i] != -1)
		{
			kfree(gfilelist[i]);
			kfree(gfileoffs[i]);
			close(groupfil[i]);
			groupfil[i] = -1;
		}
    
}

void crc32_table_gen(unsigned int* crc32_table) /* build CRC32 table */
{
    unsigned int crc, poly;
    int	i, j;
    
    poly = 0xEDB88320L;
    for (i = 0; i < 256; i++)
    {
		crc = i;
		for (j = 8; j > 0; j--)
		{
			if (crc & 1)
				crc = (crc >> 1) ^ poly;
			else
				crc >>= 1;
		}
		crc32_table[i] = crc;
    }
}

unsigned int crc32(uint8_t  *buf, unsigned int length)
{
	unsigned int initial_crc;
    
	initial_crc = 0;
	return(crc32_update(buf, length, initial_crc));
}

unsigned int crc32_update(uint8_t  *buf, unsigned int length, unsigned int crc_to_update)
{
	unsigned int crc32_table[256];
    
	crc32_table_gen(crc32_table);
    
	crc_to_update ^= 0xFFFFFFFF;
    
	while (length--)
		crc_to_update = crc32_table[(crc_to_update ^ *buf++) & 0xFF] ^ (crc_to_update >> 8);
	
	return crc_to_update ^ 0xFFFFFFFF;
}


/*
 *                                      16   12   5
 * this is the CCITT CRC 16 polynomial X  + X  + X  + 1.
 * This is 0x1021 when x is 2, but the way the algorithm works
 * we use 0x8408 (the reverse of the bit pattern).  The high
 * bit is always assumed to be set, thus we only use 16 bits to
 * represent the 17 bit value.
 */

#define POLY 0x8408   /* 1021H bit reversed */

uint16_t crc16(uint8_t  *data_p, uint16_t length)
{
    uint8_t  i;
    unsigned int data;
    unsigned int crc = 0xffff;
    
    if (length == 0)
        return (~crc);
    do
    {
        for (i=0, data=(unsigned int)0xff & *data_p++;
             i < 8;
             i++, data >>= 1)
        {
            if ((crc & 0x0001) ^ (data & 0x0001))
                crc = (crc >> 1) ^ POLY;
            else  crc >>= 1;
        }
    } while (--length);
    
    crc = ~crc;
    data = crc;
    crc = (crc << 8) | (data >> 8 & 0xff);
    
    return (crc);
}

int32_t kopen4load(const char  *filename, int readfromGRP)
{ // FIX_00072: all files are now 1st searched in Duke's root folder and then in the GRP.
	int32_t i, j, k, fil, newhandle;
	uint8_t  bad;
	uint8_t  *gfileptr;
    
	newhandle = MAXOPENFILES-1;
	while (filehan[newhandle] != -1)
	{
		newhandle--;
		if (newhandle < 0)
		{
			Error(EXIT_FAILURE, "Too Many files open!\n");
		}
	}
    
	if(!readfromGRP)
		if ((fil = open(filename,O_BINARY|O_RDONLY)) != -1)
		{
			filegrp[newhandle] = 255;
			filehan[newhandle] = fil;
			filepos[newhandle] = 0;
			printf("Reading external %s \n", filename);
			return(newhandle);
		}
    
	for(k=numgroupfiles-1;k>=0;k--)
	{
		if (groupfil[k] != -1)
		{
			for(i=gnumfiles[k]-1;i>=0;i--)
			{
				gfileptr = (uint8_t  *)&gfilelist[k][i<<4];
                
				bad = 0;
				for(j=0;j<13;j++)
				{
					if (!filename[j]) break;
					if (toupperlookup[(int) filename[j]] != toupperlookup[(int) gfileptr[j]])
                    { bad = 1; break; }
				}
				if (bad) continue;
                
				filegrp[newhandle] = (uint8_t ) k;
				filehan[newhandle] = i;
				filepos[newhandle] = 0;
				return(newhandle);
			}
		}
	}
	return(-1);
    
}

int32_t kread(int32_t handle, void *buffer, int32_t leng)
{
	int32_t i, filenum, groupnum;
    
	filenum = filehan[handle];
	groupnum = filegrp[handle];
    
	if (groupnum == 255) // Reading external
	{
		return(read(filenum,buffer,leng));
	}
    
	if (groupfil[groupnum] != -1)
	{
		i = gfileoffs[groupnum][filenum]+filepos[handle];
		if (i != groupfilpos[groupnum])
		{
			lseek(groupfil[groupnum],i+((gnumfiles[groupnum]+1)<<4),SEEK_SET);
			groupfilpos[groupnum] = i;
		}
		leng = min(leng,(gfileoffs[groupnum][filenum+1]-gfileoffs[groupnum][filenum])-filepos[handle]);
		leng = read(groupfil[groupnum],buffer,leng);
		filepos[handle] += leng;
		groupfilpos[groupnum] += leng;
		return(leng);
	}
    
	return(0);
    
}

int kread16(int32_t handle, short *buffer)
{
    if (kread(handle, buffer, 2) != 2)
        return(0);
    
    *buffer = BUILDSWAP_INTEL16(*buffer);
    return(1);
}

int kread32(int32_t handle, int32_t *buffer)
{
    if (kread(handle, buffer, 4) != 4)
        return(0);
    
    *buffer = BUILDSWAP_INTEL32(*buffer);
    return(1);
}

int kread8(int32_t handle, uint8_t  *buffer)
{
    if (kread(handle, buffer, 1) != 1)
        return(0);
    
    return(1);
}

int32_t klseek(int32_t handle, int32_t offset, int32_t whence)
{
	int32_t i, groupnum;
    
	groupnum = filegrp[handle];
    
	if (groupnum == 255) return((int32_t )lseek(filehan[handle],offset,whence));
	if (groupfil[groupnum] != -1)
	{
		switch(whence)
		{
			case SEEK_SET: filepos[handle] = offset; break;
			case SEEK_END: i = filehan[handle];
                filepos[handle] = (gfileoffs[groupnum][i+1]-gfileoffs[groupnum][i])+offset;
                break;
			case SEEK_CUR: filepos[handle] += offset; break;
		}
		return(filepos[handle]);
	}
	return(-1);
    
}

#ifdef __APPLE__
int32_t filelength(int32_t fd)
{
    struct stat stats;
    fstat(fd, &stats);
    return (int32_t )stats.st_size;
}
#endif

int32_t kfilelength(int32_t handle)
{
	int32_t i, groupnum;
    
	groupnum = filegrp[handle];
	if (groupnum == 255) return(filelength(filehan[handle]));
	i = filehan[handle];
	return(gfileoffs[groupnum][i+1]-gfileoffs[groupnum][i]);
    
}

void kclose(int32_t handle)
{
	if (handle < 0) return;
	if (filegrp[handle] == 255) close(filehan[handle]);
	filehan[handle] = -1;
    
}




/* Internal LZW variables */
#define LZWSIZE 16384           /* Watch out for shorts! */
static uint8_t  *lzwbuf1, *lzwbuf4, *lzwbuf5;
static uint8_t  lzwbuflock[5];
static short *lzwbuf2, *lzwbuf3;

void kdfread(void *buffer, size_t dasizeof, size_t count, int32_t fil)
{
	size_t i, j;
	int32_t k, kgoal;
	short leng;
	uint8_t  *ptr;
    
	lzwbuflock[0] = lzwbuflock[1] = lzwbuflock[2] = lzwbuflock[3] = lzwbuflock[4] = 200;
	if (lzwbuf1 == NULL) allocache(&lzwbuf1,LZWSIZE+(LZWSIZE>>4),&lzwbuflock[0]);
	if (lzwbuf2 == NULL) allocache(&lzwbuf2,(LZWSIZE+(LZWSIZE>>4))*2,&lzwbuflock[1]);
	if (lzwbuf3 == NULL) allocache(&lzwbuf3,(LZWSIZE+(LZWSIZE>>4))*2,&lzwbuflock[2]);
	if (lzwbuf4 == NULL) allocache(&lzwbuf4,LZWSIZE,&lzwbuflock[3]);
	if (lzwbuf5 == NULL) allocache(&lzwbuf5,LZWSIZE+(LZWSIZE>>4),&lzwbuflock[4]);
    
	if (dasizeof > LZWSIZE) { count *= dasizeof; dasizeof = 1; }
	ptr = (uint8_t  *)buffer;
    
	kread(fil,&leng,2); kread(fil,lzwbuf5,(int32_t )leng);
	k = 0;
	kgoal = uncompress(lzwbuf5,leng,lzwbuf4);
    
	copybufbyte(lzwbuf4,ptr,(int32_t )dasizeof);
	k += (int32_t )dasizeof;
    
	for(i=1;i<count;i++)
	{
		if (k >= kgoal)
		{
			kread(fil,&leng,2); kread(fil,lzwbuf5,(int32_t )leng);
			k = 0; kgoal = uncompress(lzwbuf5,(int32_t )leng,lzwbuf4);
		}
		for(j=0;j<dasizeof;j++) ptr[j+dasizeof] = (uint8_t ) ((ptr[j]+lzwbuf4[j+k])&255);
		k += dasizeof;
		ptr += dasizeof;
	}
	lzwbuflock[0] = lzwbuflock[1] = lzwbuflock[2] = lzwbuflock[3] = lzwbuflock[4] = 1;
}

void dfread(void *buffer, size_t dasizeof, size_t count, FILE *fil)
{
	size_t i, j;
	int32_t k, kgoal;
	short leng;
	uint8_t  *ptr;
    
	lzwbuflock[0] = lzwbuflock[1] = lzwbuflock[2] = lzwbuflock[3] = lzwbuflock[4] = 200;
	if (lzwbuf1 == NULL) allocache((int32_t *)&lzwbuf1,LZWSIZE+(LZWSIZE>>4),&lzwbuflock[0]);
	if (lzwbuf2 == NULL) allocache((int32_t *)&lzwbuf2,(LZWSIZE+(LZWSIZE>>4))*2,&lzwbuflock[1]);
	if (lzwbuf3 == NULL) allocache((int32_t *)&lzwbuf3,(LZWSIZE+(LZWSIZE>>4))*2,&lzwbuflock[2]);
	if (lzwbuf4 == NULL) allocache((int32_t *)&lzwbuf4,LZWSIZE,&lzwbuflock[3]);
	if (lzwbuf5 == NULL) allocache((int32_t *)&lzwbuf5,LZWSIZE+(LZWSIZE>>4),&lzwbuflock[4]);
    
	if (dasizeof > LZWSIZE) {
        count *= dasizeof;
        dasizeof = 1;
    }
    
	ptr = (uint8_t  *)buffer;
    
	fread(&leng,2,1,fil);
    fread(lzwbuf5,(int32_t )leng,1,fil);
    
	k = 0;
    kgoal = uncompress(lzwbuf5,(int32_t )leng,lzwbuf4);
    
	copybufbyte(lzwbuf4,ptr,(int32_t )dasizeof);
	k += (int32_t )dasizeof;
    
	for(i=1;i<count;i++)
	{
		if (k >= kgoal)
		{
			fread(&leng,2,1,fil); fread(lzwbuf5,(int32_t )leng,1,fil);
			k = 0; kgoal = uncompress(lzwbuf5,(int32_t )leng,lzwbuf4);
		}
		for(j=0;j<dasizeof;j++) ptr[j+dasizeof] = (uint8_t ) ((ptr[j]+lzwbuf4[j+k])&255);
		k += dasizeof;
		ptr += dasizeof;
	}
	lzwbuflock[0] = lzwbuflock[1] = lzwbuflock[2] = lzwbuflock[3] = lzwbuflock[4] = 1;
}

void dfwrite(void *buffer, size_t dasizeof, size_t count, FILE *fil)
{
	size_t i, j, k;
	short leng;
	uint8_t  *ptr;
    
	lzwbuflock[0] = lzwbuflock[1] = lzwbuflock[2] = lzwbuflock[3] = lzwbuflock[4] = 200;
	if (lzwbuf1 == NULL) allocache(&lzwbuf1,LZWSIZE+(LZWSIZE>>4),&lzwbuflock[0]);
	if (lzwbuf2 == NULL) allocache(&lzwbuf2,(LZWSIZE+(LZWSIZE>>4))*2,&lzwbuflock[1]);
	if (lzwbuf3 == NULL) allocache(&lzwbuf3,(LZWSIZE+(LZWSIZE>>4))*2,&lzwbuflock[2]);
	if (lzwbuf4 == NULL) allocache(&lzwbuf4,LZWSIZE,&lzwbuflock[3]);
	if (lzwbuf5 == NULL) allocache(&lzwbuf5,LZWSIZE+(LZWSIZE>>4),&lzwbuflock[4]);
    
	if (dasizeof > LZWSIZE) { count *= dasizeof; dasizeof = 1; }
	ptr = (uint8_t  *)buffer;
    
	copybufbyte(ptr,lzwbuf4,(int32_t )dasizeof);
	k = dasizeof;
    
	if (k > LZWSIZE-dasizeof)
	{
		leng = (short)compress(lzwbuf4,k,lzwbuf5); k = 0;
		fwrite(&leng,2,1,fil); fwrite(lzwbuf5,(int32_t )leng,1,fil);
	}
    
	for(i=1;i<count;i++)
	{
		for(j=0;j<dasizeof;j++) lzwbuf4[j+k] = (uint8_t ) ((ptr[j+dasizeof]-ptr[j])&255);
		k += dasizeof;
		if (k > LZWSIZE-dasizeof)
		{
			leng = (short)compress(lzwbuf4,k,lzwbuf5); k = 0;
			fwrite(&leng,2,1,fil); fwrite(lzwbuf5,(int32_t )leng,1,fil);
		}
		ptr += dasizeof;
	}
	if (k > 0)
	{
		leng = (short)compress(lzwbuf4,k,lzwbuf5);
		fwrite(&leng,2,1,fil); fwrite(lzwbuf5,(int32_t )leng,1,fil);
	}
	lzwbuflock[0] = lzwbuflock[1] = lzwbuflock[2] = lzwbuflock[3] = lzwbuflock[4] = 1;
}

int32_t compress(uint8_t  *lzwinbuf, int32_t uncompleng, uint8_t  *lzwoutbuf)
{
	int32_t i, addr, newaddr, addrcnt, zx, *longptr;
	int32_t bytecnt1, bitcnt, numbits, oneupnumbits;
	short *shortptr;
    
	for(i=255;i>=0;i--) { lzwbuf1[i] = (uint8_t ) i; lzwbuf3[i] = (short) ((i+1)&255); }
	clearbuf((void *) FP_OFF(lzwbuf2),256>>1,0xffffffff);
	clearbuf((void *) FP_OFF(lzwoutbuf),((uncompleng+15)+3)>>2,0L);
    
	addrcnt = 256; bytecnt1 = 0; bitcnt = (4<<3);
	numbits = 8; oneupnumbits = (1<<8);
	do
	{
		addr = lzwinbuf[bytecnt1];
		do
		{
			bytecnt1++;
			if (bytecnt1 == uncompleng) break;
			if (lzwbuf2[addr] < 0) {lzwbuf2[addr] = (short) addrcnt; break;}
			newaddr = lzwbuf2[addr];
			while (lzwbuf1[newaddr] != lzwinbuf[bytecnt1])
			{
				zx = lzwbuf3[newaddr];
				if (zx < 0) {lzwbuf3[newaddr] = (short) addrcnt; break;}
				newaddr = zx;
			}
			if (lzwbuf3[newaddr] == addrcnt) break;
			addr = newaddr;
		} while (addr >= 0);
		lzwbuf1[addrcnt] = lzwinbuf[bytecnt1];
		lzwbuf2[addrcnt] = -1;
		lzwbuf3[addrcnt] = -1;
        
		longptr = (int32_t *)&lzwoutbuf[bitcnt>>3];
		longptr[0] |= (addr<<(bitcnt&7));
		bitcnt += numbits;
		if ((addr&((oneupnumbits>>1)-1)) > ((addrcnt-1)&((oneupnumbits>>1)-1)))
			bitcnt--;
        
		addrcnt++;
		if (addrcnt > oneupnumbits) { numbits++; oneupnumbits <<= 1; }
	} while ((bytecnt1 < uncompleng) && (bitcnt < (uncompleng<<3)));
    
	longptr = (int32_t *)&lzwoutbuf[bitcnt>>3];
	longptr[0] |= (addr<<(bitcnt&7));
	bitcnt += numbits;
	if ((addr&((oneupnumbits>>1)-1)) > ((addrcnt-1)&((oneupnumbits>>1)-1)))
		bitcnt--;
    
	shortptr = (short *)lzwoutbuf;
	shortptr[0] = (short)uncompleng;
	if (((bitcnt+7)>>3) < uncompleng)
	{
		shortptr[1] = (short)addrcnt;
		return((bitcnt+7)>>3);
	}
	shortptr[1] = (short)0;
	for(i=0;i<uncompleng;i++) lzwoutbuf[i+4] = lzwinbuf[i];
	return(uncompleng+4);
}

int32_t uncompress(uint8_t  *lzwinbuf, int32_t compleng, uint8_t  *lzwoutbuf)
{
	int32_t strtot, currstr, numbits, oneupnumbits;
	int32_t i, dat, leng, bitcnt, outbytecnt, *longptr;
	short *shortptr;
    
	shortptr = (short *)lzwinbuf;
	strtot = (int32_t )shortptr[1];
	if (strtot == 0)
	{
		copybuf((void *)(FP_OFF(lzwinbuf)+4),(void *)(FP_OFF(lzwoutbuf)),((compleng-4)+3)>>2);
		return((int32_t )shortptr[0]); /* uncompleng */
	}
	for(i=255;i>=0;i--) { lzwbuf2[i] = (short) i; lzwbuf3[i] = (short) i; }
	currstr = 256; bitcnt = (4<<3); outbytecnt = 0;
	numbits = 8; oneupnumbits = (1<<8);
	do
	{
		longptr = (int32_t *)&lzwinbuf[bitcnt>>3];
		dat = ((longptr[0]>>(bitcnt&7)) & (oneupnumbits-1));
		bitcnt += numbits;
		if ((dat&((oneupnumbits>>1)-1)) > ((currstr-1)&((oneupnumbits>>1)-1)))
        { dat &= ((oneupnumbits>>1)-1); bitcnt--; }
        
		lzwbuf3[currstr] = (short) dat;
        
		for(leng=0;dat>=256;leng++,dat=lzwbuf3[dat])
			lzwbuf1[leng] = (uint8_t ) lzwbuf2[dat];
        
		lzwoutbuf[outbytecnt++] = (uint8_t ) dat;
		for(i=leng-1;i>=0;i--) lzwoutbuf[outbytecnt++] = lzwbuf1[i];
        
		lzwbuf2[currstr-1] = (short) dat; lzwbuf2[currstr] = (short) dat;
		currstr++;
		if (currstr > oneupnumbits) { numbits++; oneupnumbits <<= 1; }
	} while (currstr < strtot);
	return((int32_t )shortptr[0]); /* uncompleng */
}

int SafeFileExists ( const char  * _filename );
int32_t TCkopen4load(const char  *filename, int readfromGRP)
{
	char  fullfilename[512];
	int32_t result = 0;
    
	if(game_dir[0] != '\0' && !readfromGRP)
	{
		sprintf(fullfilename, "%s\\%s", game_dir, filename);
		if (!SafeFileExists(fullfilename)) // try root
			sprintf(fullfilename, "%s", filename);
	}
	else
	{
		sprintf(fullfilename, "%s", filename);
	}
    
	result = kopen4load(fullfilename, readfromGRP);
    
	return result;
}


void   setGameDir(char* gameDir){
    if (gameDir == NULL)
        return;
    
    strncpy(game_dir,gameDir,sizeof(game_dir));
}

char*  getGameDir(void){
    return game_dir;
}


