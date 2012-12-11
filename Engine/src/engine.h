/*
 * A list of all symbols exported from engine.c for a game's use.
 *
 *  Put together by Ryan C. Gordon (icculus@clutteredmind.org)
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

#ifndef _INCLUDE_ENGINE_H_
#define _INCLUDE_ENGINE_H_

#ifdef __cplusplus
extern "C" {
#endif

//#define SUPERBUILD  /* don't touch this. */

/*
 * this must be implemented by every program that uses the BUILD engine.
 *  engine.c calls this function in several places.
 *  See Ken's test game (in game.c), and his editor (in bstub.c) for examples.
 */
void faketimerhandler(void);

/*
 * exported engine functions, in absolutely no particular order.
 *  See build.txt, build2.txt...and anything else with a .txt extention for
 *  information on using these functions that may or may not be accurate. :)
 */
int initmouse(void);
int setgamemode(char davidoption, long daxdim, long daydim);
int getceilzofslope(short sectnum, long dax, long day);
int getflorzofslope(short sectnum, long dax, long day);
void getzsofslope(short sectnum, long dax, long day, long *ceilz, long *florz);
void setaspect(long daxrange, long daaspect);
int insertsprite(short sectnum, short statnum);
void updatesector(long x, long y, short *sectnum);
int lastwall(short point);
void initspritelists(void);
int deletesprite(short spritenum);
int insertspritesect(short sectnum);
int deletespritesect(short deleteme);
int deletespritestat (short deleteme);
int insertspritestat(short statnum);
int changespritesect(short spritenum, short newsectnum);
int changespritestat(short spritenum, short newstatnum);
void loadtile(short tilenume);
void setmmxoverlay(int isenabled);
int getmmxoverlay(void);
void nextpage(void);
void drawrooms(long daposx, long daposy, long daposz,
               short daang, long dahoriz, short dacursectnum);
int loadboard(char *filename, long *daposx, long *daposy,
			  long *daposz, short *daang, short *dacursectnum);
void drawmasks(void);
void printext256(long xpos, long ypos, short col, short backcol,
			char name[82], char fontsize);
void printext256_noupdate(long xpos, long ypos, short col, short backcol,
			char name[82], char fontsize);
void initengine(void);
void uninitengine(void);
int loadpics(char *filename, char* gamedir);
int saveboard(char *filename, long *daposx, long *daposy, long *daposz,
                         short *daang, short *dacursectnum);
void plotpixel(long x, long y, char col);
unsigned char getpixel(long x, long y);
void setbrightness(char dabrightness, unsigned char *dapal);
int screencapture(char *filename, char inverseit);
void getmousevalues(short *mousx, short *mousy, short *bstatus);
int clipmove (long *x, long *y, long *z, short *sectnum, long xvect,
			long yvect, long walldist, long ceildist,
			long flordist, unsigned long cliptype);
void getzrange(long x, long y, long z, short sectnum,
			long *ceilz, long *ceilhit, long *florz, long *florhit,
			long walldist, unsigned long cliptype);
int getangle(long xvect, long yvect);
void alignceilslope(short dasect, long x, long y, long z);
void alignflorslope(short dasect, long x, long y, long z);
int hitscan(long xs, long ys, long zs, short sectnum,
            long vx, long vy, long vz,
	        short *hitsect, short *hitwall, short *hitsprite,
	        long *hitx, long *hity, long *hitz, unsigned long cliptype);
int inside (long x, long y, short sectnum);
void setfirstwall(short sectnum, short newfirstwall);
void rotatepoint(long xpivot, long ypivot, long x, long y, short daang,
			long *x2, long *y2);
int drawtilescreen(long pictopleft, long picbox);
void clearview(long dacol);
void clearallviews(long dacol);
void draw2dgrid(long posxe, long posye, short ange, long zoome,
			short gride);
void draw2dscreen(long posxe, long posye, short ange, long zoome,
			short gride);
int sectorofwall(short theline);
int setsprite(short spritenum, long newx, long newy, long newz);
void dragpoint(short pointhighlight, long dax, long day);
int ksqrt(long num);
int loopnumofsector(short sectnum, short wallnum);
int cansee(long x1, long y1, long z1, short sect1,
            long x2, long y2, long z2, short sect2);
int lintersect(long x1, long y1, long z1, long x2, long y2, long z2,
               long x3, long y3, long x4, long y4, long *intx,
               long *inty, long *intz);
int rintersect(long x1, long y1, long z1, long vx, long vy, long vz,
               long x3, long y3, long x4, long y4, long *intx,
               long *inty, long *intz);
int allocatepermanenttile(short tilenume, long xsiz, long ysiz);
void drawline256 (long x1, long y1, long x2, long y2, unsigned char col);
void copytilepiece(long tilenume1, long sx1, long sy1, long xsiz, long ysiz,
                   long tilenume2, long sx2, long sy2);
int nextsectorneighborz(short sectnum, long thez,
                        short topbottom, short direction);
int neartag(long xs, long ys, long zs, short sectnum, short ange,
            short *neartagsector, short *neartagwall, short *neartagsprite,
            long *neartaghitdist, long neartagrange, char tagsearch);
int pushmove(long *x, long *y, long *z, short *sectnum,
             long walldist, long ceildist, long flordist,
             unsigned long cliptype);
#ifdef DBGRECORD
int krand(int line, char* file);
#else
int krand(void);
#endif
void flushperms(void);
void rotatesprite(long sx, long sy, long z, short a, short picnum,
                  signed char dashade, char dapalnum, char dastat,
                  long cx1, long cy1, long cx2, long cy2);
void makepalookup(long palnum, char *remapbuf, signed char r,
                  signed char g, signed char b, char dastat);
void drawmapview(long dax, long day, long zoome, short ang);
void setview(long x1, long y1, long x2, long y2);
void setviewtotile(short tilenume, long xsiz, long ysiz);
void setviewback(void);
void squarerotatetile(short tilenume);
void preparemirror(long dax, long day, long daz,
                   short daang, long dahoriz, short dawall,
                   short dasector, long *tposx, long *tposy,
                   short *tang);
void completemirror(void);
int clipinsidebox(long x, long y, short wallnum, long walldist);

#ifdef SUPERBUILD
void qloadkvx(long voxindex, char *filename);
#endif

#ifdef __cplusplus
}
#endif

#endif /* !defined _INCLUDE_ENGINE_H_ */

/* end of engine.h ... */



