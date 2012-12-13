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
int setgamemode(char davidoption, int32_t daxdim, int32_t daydim);
int getceilzofslope(short sectnum, int32_t dax, int32_t day);
int getflorzofslope(short sectnum, int32_t dax, int32_t day);
void getzsofslope(short sectnum, int32_t dax, int32_t day, int32_t *ceilz, int32_t *florz);
void setaspect(int32_t daxrange, int32_t daaspect);
int insertsprite(short sectnum, short statnum);
void updatesector(int32_t x, int32_t y, short *sectnum);
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
void drawrooms(int32_t daposx, int32_t daposy, int32_t daposz,
               short daang, int32_t dahoriz, short dacursectnum);
int loadboard(char *filename, int32_t *daposx, int32_t *daposy,
			  int32_t *daposz, short *daang, short *dacursectnum);
void drawmasks(void);
void printext256(int32_t xpos, int32_t ypos, short col, short backcol,
			char name[82], char fontsize);
void printext256_noupdate(int32_t xpos, int32_t ypos, short col, short backcol,
			char name[82], char fontsize);
void initengine(void);
void uninitengine(void);
int loadpics(char *filename, char* gamedir);
int saveboard(char *filename, int32_t *daposx, int32_t *daposy, int32_t *daposz,
                         short *daang, short *dacursectnum);
void plotpixel(int32_t x, int32_t y, char col);
uint8_t  getpixel(int32_t x, int32_t y);
void setbrightness(char dabrightness, uint8_t  *dapal);
int screencapture(char *filename, char inverseit);
void getmousevalues(short *mousx, short *mousy, short *bstatus);
int clipmove (int32_t *x, int32_t *y, int32_t *z, short *sectnum, int32_t xvect,
			int32_t yvect, int32_t walldist, int32_t ceildist,
			int32_t flordist, uint32_t  cliptype);
void getzrange(int32_t x, int32_t y, int32_t z, short sectnum,
			int32_t *ceilz, int32_t *ceilhit, int32_t *florz, int32_t *florhit,
			int32_t walldist, uint32_t  cliptype);
int getangle(int32_t xvect, int32_t yvect);
void alignceilslope(short dasect, int32_t x, int32_t y, int32_t z);
void alignflorslope(short dasect, int32_t x, int32_t y, int32_t z);
int hitscan(int32_t xs, int32_t ys, int32_t zs, short sectnum,
            int32_t vx, int32_t vy, int32_t vz,
	        short *hitsect, short *hitwall, short *hitsprite,
	        int32_t *hitx, int32_t *hity, int32_t *hitz, uint32_t  cliptype);
int inside (int32_t x, int32_t y, short sectnum);
void setfirstwall(short sectnum, short newfirstwall);
void rotatepoint(int32_t xpivot, int32_t ypivot, int32_t x, int32_t y, short daang,
			int32_t *x2, int32_t *y2);
int drawtilescreen(int32_t pictopleft, int32_t picbox);
void clearview(int32_t dacol);
void clearallviews(int32_t dacol);
void draw2dgrid(int32_t posxe, int32_t posye, short ange, int32_t zoome,
			short gride);
void draw2dscreen(int32_t posxe, int32_t posye, short ange, int32_t zoome,
			short gride);
int sectorofwall(short theline);
int setsprite(short spritenum, int32_t newx, int32_t newy, int32_t newz);
void dragpoint(short pointhighlight, int32_t dax, int32_t day);
int ksqrt(int32_t num);
int loopnumofsector(short sectnum, short wallnum);
int cansee(int32_t x1, int32_t y1, int32_t z1, short sect1,
            int32_t x2, int32_t y2, int32_t z2, short sect2);
int lintersect(int32_t x1, int32_t y1, int32_t z1, int32_t x2, int32_t y2, int32_t z2,
               int32_t x3, int32_t y3, int32_t x4, int32_t y4, int32_t *intx,
               int32_t *inty, int32_t *intz);
int rintersect(int32_t x1, int32_t y1, int32_t z1, int32_t vx, int32_t vy, int32_t vz,
               int32_t x3, int32_t y3, int32_t x4, int32_t y4, int32_t *intx,
               int32_t *inty, int32_t *intz);
int allocatepermanenttile(short tilenume, int32_t xsiz, int32_t ysiz);
void drawline256 (int32_t x1, int32_t y1, int32_t x2, int32_t y2, uint8_t  col);
void copytilepiece(int32_t tilenume1, int32_t sx1, int32_t sy1, int32_t xsiz, int32_t ysiz,
                   int32_t tilenume2, int32_t sx2, int32_t sy2);
int nextsectorneighborz(short sectnum, int32_t thez,
                        short topbottom, short direction);
int neartag(int32_t xs, int32_t ys, int32_t zs, short sectnum, short ange,
            short *neartagsector, short *neartagwall, short *neartagsprite,
            int32_t *neartaghitdist, int32_t neartagrange, char tagsearch);
int pushmove(int32_t *x, int32_t *y, int32_t *z, short *sectnum,
             int32_t walldist, int32_t ceildist, int32_t flordist,
             uint32_t  cliptype);
#ifdef DBGRECORD
int krand(int line, char* file);
#else
int krand(void);
#endif
void flushperms(void);
void rotatesprite(int32_t sx, int32_t sy, int32_t z, short a, short picnum,
                  int8_t dashade, char dapalnum, char dastat,
                  int32_t cx1, int32_t cy1, int32_t cx2, int32_t cy2);
void makepalookup(int32_t palnum, char *remapbuf, int8_t r,
                  int8_t g, int8_t b, char dastat);
void drawmapview(int32_t dax, int32_t day, int32_t zoome, short ang);
void setview(int32_t x1, int32_t y1, int32_t x2, int32_t y2);
void setviewtotile(short tilenume, int32_t xsiz, int32_t ysiz);
void setviewback(void);
void squarerotatetile(short tilenume);
void preparemirror(int32_t dax, int32_t day, int32_t daz,
                   short daang, int32_t dahoriz, short dawall,
                   short dasector, int32_t *tposx, int32_t *tposy,
                   short *tang);
void completemirror(void);
int clipinsidebox(int32_t x, int32_t y, short wallnum, int32_t walldist);

#ifdef SUPERBUILD
void qloadkvx(int32_t voxindex, char *filename);
#endif

#ifdef __cplusplus
}
#endif

#endif /* !defined _INCLUDE_ENGINE_H_ */

/* end of engine.h ... */



