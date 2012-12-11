//-------------------------------------------------------------------------
/*
Copyright (C) 1996, 2003 - 3D Realms Entertainment

This file is part of Duke Nukem 3D version 1.5 - Atomic Edition

Duke Nukem 3D is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/
//-------------------------------------------------------------------------

/* Prototypes for the build engine */

#if 0
/* game.c */
extern void initsb(char dadigistat, char damusistat, long dasamplerate, char danumspeakers, char dabytespersample, char daintspersec, char daquality);
extern void uninitsb(void);
extern int loadsong(char *filename);
extern void musicon(void);
extern void musicoff(void);
extern void wsayfollow(char *dafilename, long dafreq, long davol, long *daxplc, long *dayplc, char followstat);
extern void wsay(char *dafilename, long dafreq, long volume1, long volume2);
extern void preparesndbuf(void);
extern void setears(long daposx, long daposy, long daxvect, long dayvect);
extern void timerhandler(void);
extern void keyhandler(void);
extern void initlava(void);
extern void movelava(char *dapic);
extern void drawtilebackground(long thex, long they, short tilenum, signed char shade, long cx1, long cy1, long cx2, long cy2, char dapalnum);
extern void printext(long x, long y, char *buffer, short tilenum, char invisiblecol);
extern void drawstatusflytime(short snum);
extern void drawstatusbar(short snum);
extern void setup3dscreen(void);
extern void setinterpolation(long *posptr);
extern void stopinterpolation(long *posptr);
extern void updateinterpolations(void);
extern void restoreinterpolations(void);
extern void searchmap(short startsector);
extern void prepareboard(char *daboardfilename);
extern long changehealth(short snum, short deltahealth);
extern void changenumbombs(short snum, short deltanumbombs);
extern void changenummissiles(short snum, short deltanummissiles);
extern void changenumgrabbers(short snum, short deltanumgrabbers);
extern void findrandomspot(long *x, long *y, short *sectnum);
extern void operatesector(short dasector);
extern void shootgun(short snum, long x, long y, long z, short daang, long dahoriz, short dasectnum, char guntype);
extern void operatesprite(short dasprite);
extern void checktouchsprite(short snum, short sectnum);
extern void checkgrabbertouchsprite(short snum, short sectnum);
extern void activatehitag(short dahitag);
extern void processinput(short snum);
extern void movethings(void);
extern void fakedomovethings(void);
extern void fakedomovethingscorrect(void);
extern void doanimations(void);
extern void warp(long *x, long *y, long *z, short *daang, short *dasector);
extern void warpsprite(short spritenum);
extern int testneighborsectors(short sect1, short sect2);
extern void tagcode(void);
extern void bombexplode(long i);
extern void statuslistcode(void);
extern void checkmasterslaveswitch(void);
extern void getpackets(void);
extern void initplayersprite(short snum);
extern void analyzesprites(long dax, long day);
extern void updatesectorz(long x, long y, long z, short *sectnum);
extern void drawoverheadmap(long cposx, long cposy, long czoom, short cang);
extern void drawscreen(short snum, long dasmoothratio);
extern int loadgame(void);
extern int savegame(void);
extern void faketimerhandler(void);
extern void waitforeverybody(void);
#endif

/* cache1d.c */
extern void initcache(long dacachestart, long dacachesize);
extern void allocache(long *newhandle, long newbytes, unsigned char *newlockptr);
extern void suckcache(long *suckptr);
extern void agecache(void);
extern void reportandexit(char *errormessage);
extern long initgroupfile(const char *filename);
extern void uninitgroupfile(void);
extern long kopen4load(const char *filename,int readfromGRP);
extern long kread(long handle, void *buffer, long leng);
extern long klseek(long handle, long offset, long whence);
extern long kfilelength(long handle);
extern void kclose(long handle);
extern void kdfread(void *buffer, size_t dasizeof, size_t count, long fil);
extern void dfread(void *buffer, size_t dasizeof, size_t count, FILE *fil);
extern void dfwrite(void *buffer, size_t dasizeof, size_t count, FILE *fil);
extern long compress(char *lzwinbuf, long uncompleng, char *lzwoutbuf);
extern long uncompress(char *lzwinbuf, long compleng, char *lzwoutbuf);

/* sdl_driver.c */
extern int using_opengl(void);
extern void _handle_events(void);
extern unsigned char _readlastkeyhit(void);
extern int mprotect_align(const void *addr, size_t len, int prot);
extern void unprotect_ASM_pages(void);
extern void _platform_init(int argc, char **argv, const char *title, const char *icon);
extern int setvesa(long x, long y);
extern int screencapture(char *filename, char inverseit);
extern void setvmode(int mode);
extern int _setgamemode(char davidoption, long daxdim, long daydim);
extern void getvalidvesamodes(void);
extern int VBE_setPalette(long start, long num, char *palettebuffer);
extern int VBE_getPalette(long start, long num, char *palettebuffer);
extern void _uninitengine(void);
extern void uninitvesa(void);
extern int setupmouse(void);
extern void readmousexy(short *x, short *y);
extern void readmousebstatus(short *bstatus);
extern void _updateScreenRect(long x, long y, long w, long h);
extern void _nextpage(void);
extern unsigned char readpixel(long offset);
extern void drawpixel(long offset, unsigned char pixel);
extern void drawpixels(long offset, unsigned short pixels);
extern void drawpixelses(long offset, unsigned int pixelses);
extern void setcolor16(int col);
extern void drawpixel16(long offset);
extern void fillscreen16(long offset, long color, long blocksize);
extern void drawline16(long XStart, long YStart, long XEnd, long YEnd, char Color);
extern void clear2dscreen(void);
extern void _idle(void);
extern void *_getVideoBase(void);
extern void setactivepage(long dapagenum);
extern void limitrate(void);
extern int inittimer(int);
extern void uninittimer(void);
extern void initkeys(void);
extern void uninitkeys(void);
extern void set16color_palette(void);
extern void restore256_palette(void);
extern unsigned long getticks(void);

/* mmulti.c */
// converted to function pointers
/*
void (*callcommit)(void);
void (*initcrc)(void);
long (*getcrc)(char *buffer, short bufleng);
void (*initmultiplayers)(char damultioption, char dacomrateoption, char dapriority);
void (*sendpacket)(long other, char *bufptr, long messleng);
void (*setpackettimeout)(long datimeoutcount, long daresendagaincount);
void (*uninitmultiplayers)(void);
void (*sendlogon)(void);
void (*sendlogoff)(void);
int (*getoutputcirclesize)(void);
void (*setsocket)(short newsocket);
short (*getpacket)(short *other, char *bufptr);
void (*flushpackets)(void);
void (*genericmultifunction)(long other, char *bufptr, long messleng, long command);
*/
void callcommit(void);
void initcrc(void);
long getcrc(char *buffer, short bufleng);
void initmultiplayers(char damultioption, char dacomrateoption, char dapriority);
void sendpacket(long other, char *bufptr, long messleng);
void setpackettimeout(long datimeoutcount, long daresendagaincount);
void uninitmultiplayers(void);
void sendlogon(void);
void sendlogoff(void);
int getoutputcirclesize(void);
void setsocket(short newsocket);
short getpacket(short *other, char *bufptr);
void flushpackets(void);
void genericmultifunction(long other, char *bufptr, long messleng, long command);

/* engine.c */
extern int setgotpic(long i1);
//extern static __inline long getclipmask(long a, long b, long c, long d);
extern int wallfront(long l1, long l2);
extern void drawrooms(long daposx, long daposy, long daposz, short daang, long dahoriz, short dacursectnum);
extern int loadboard(char *filename, long *daposx, long *daposy, long *daposz, short *daang, short *dacursectnum);
extern int saveboard(char *filename, long *daposx, long *daposy, long *daposz, short *daang, short *dacursectnum);
extern int setgamemode(char davidoption, long daxdim, long daydim);
extern void setmmxoverlay(int isenabled);
extern int getmmxoverlay(void);
extern void initengine(void);
extern void uninitengine(void);
extern void nextpage(void);
extern void loadtile(short tilenume);
extern int allocatepermanenttile(short tilenume, long xsiz, long ysiz);
extern int loadpics(char *filename, char* gamedir);
extern void qloadkvx(long voxindex, char *filename);
extern int clipinsidebox(long x, long y, short wallnum, long walldist);
extern void drawline256(long x1, long y1, long x2, long y2, unsigned char col);
extern int inside(long x, long y, short sectnum);
extern int getangle(long xvect, long yvect);
extern int ksqrt(long num);
extern void copytilepiece(long tilenume1, long sx1, long sy1, long xsiz, long ysiz, long tilenume2, long sx2, long sy2);
extern void drawmasks(void);
extern int setsprite(short spritenum, long newx, long newy, long newz);
extern void initspritelists(void);
extern int insertsprite(short sectnum, short statnum);
extern int insertspritesect(short sectnum);
extern int insertspritestat(short statnum);
extern int deletesprite(short spritenum);
extern int deletespritesect(short deleteme);
extern int deletespritestat(short deleteme);
extern int changespritesect(short spritenum, short newsectnum);
extern int changespritestat(short spritenum, short newstatnum);
extern int nextsectorneighborz(short sectnum, long thez, short topbottom, short direction);
extern int cansee(long x1, long y1, long z1, short sect1, long x2, long y2, long z2, short sect2);
extern int lintersect(long x1, long y1, long z1, long x2, long y2, long z2, long x3, long y3, long x4, long y4, long *intx, long *inty, long *intz);
extern int rintersect(long x1, long y1, long z1, long vx, long vy, long vz, long x3, long y3, long x4, long y4, long *intx, long *inty, long *intz);
extern int hitscan(long xs, long ys, long zs, short sectnum, long vx, long vy, long vz, short *hitsect, short *hitwall, short *hitsprite, long *hitx, long *hity, long *hitz, unsigned long cliptype);
extern int neartag(long xs, long ys, long zs, short sectnum, short ange, short *neartagsector, short *neartagwall, short *neartagsprite, long *neartaghitdist, long neartagrange, char tagsearch);
extern void dragpoint(short pointhighlight, long dax, long day);
extern int lastwall(short point);
extern int clipmove(long *x, long *y, long *z, short *sectnum, long xvect, long yvect, long walldist, long ceildist, long flordist, unsigned long cliptype);
extern int pushmove(long *x, long *y, long *z, short *sectnum, long walldist, long ceildist, long flordist, unsigned long cliptype);
extern void updatesector(long x, long y, short *sectnum);
extern void rotatepoint(long xpivot, long ypivot, long x, long y, short daang, long *x2, long *y2);
extern int initmouse(void);
extern void getmousevalues(short *mousx, short *mousy, short *bstatus);
extern void draw2dgrid(long posxe, long posye, short ange, long zoome, short gride);
extern void draw2dscreen(long posxe, long posye, short ange, long zoome, short gride);
extern void printext256(long xpos, long ypos, short col, short backcol, char name[82], char fontsize);
extern void printext256_noupdate(long xpos, long ypos, short col, short backcol, char name[82], char fontsize);
#ifdef DBGRECORD
extern int krand(int line, char* file);
#else
extern int krand(void);
#endif
extern void getzrange(long x, long y, long z, short sectnum, long *ceilz, long *ceilhit, long *florz, long *florhit, long walldist, unsigned long cliptype);
extern void setview(long x1, long y1, long x2, long y2);
extern void setaspect(long daxrange, long daaspect);
extern void flushperms(void);
extern void rotatesprite(long sx, long sy, long z, short a, short picnum, signed char dashade, char dapalnum, char dastat, long cx1, long cy1, long cx2, long cy2);
extern void makepalookup(long palnum, char *remapbuf, signed char r, signed char g, signed char b, char dastat);
extern void setbrightness(char dabrightness, unsigned char *dapal);
extern void drawmapview(long dax, long day, long zoome, short ang);
extern void clearview(long dacol);
extern void clearallviews(long dacol);
extern void plotpixel(long x, long y, char col);
extern unsigned char getpixel(long x, long y);
extern void setviewtotile(short tilenume, long xsiz, long ysiz);
extern void setviewback(void);
extern void squarerotatetile(short tilenume);
extern void preparemirror(long dax, long day, long daz, short daang, long dahoriz, short dawall, short dasector, long *tposx, long *tposy, short *tang);
extern void completemirror(void);
extern int sectorofwall(short theline);
extern int getceilzofslope(short sectnum, long dax, long day);
extern int getflorzofslope(short sectnum, long dax, long day);
extern void getzsofslope(short sectnum, long dax, long day, long *ceilz, long *florz);
extern void alignceilslope(short dasect, long x, long y, long z);
extern void alignflorslope(short dasect, long x, long y, long z);
extern int loopnumofsector(short sectnum, short wallnum);
extern void setfirstwall(short sectnum, short newfirstwall);
