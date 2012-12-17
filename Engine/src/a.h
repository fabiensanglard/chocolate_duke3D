/*
 * "Build Engine & Tools" Copyright (c) 1993-1997 Ken Silverman
 * Ken Silverman's official web site: "http://www.advsys.net/ken"
 * See the included license file "BUILDLIC.TXT" for license info.
 * This file IS NOT A PART OF Ken Silverman's original release
 */

#ifndef _INCLUDE_A_H_
#define _INCLUDE_A_H_

#ifdef _WIN32
   #include "windows/inttypes.h"
#else
   #include <inttypes.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif
    
extern uint8_t  *globalpalwritten;

void sethlinesizes(int32_t,int32_t,int32_t);


void hlineasm4(int32_t,int32_t,uint32_t,uint32_t,int32_t);
void setuprhlineasm4(int32_t,int32_t,int32_t,int32_t,int32_t,int32_t);
void rhlineasm4(int32_t,int32_t,int32_t,uint32_t,uint32_t,int32_t);
void setuprmhlineasm4(int32_t,int32_t,int32_t,int32_t,int32_t,int32_t);
void rmhlineasm4(int32_t,int32_t,int32_t,int32_t,int32_t,int32_t);


void setBytesPerLine(int32_t);
void fixtransluscence(uint8_t*);
int32_t prevlineasm1(int32_t,int32_t,int32_t,int32_t,int32_t,int32_t);
int32_t vlineasm1(int32_t,int32_t,int32_t,int32_t,int32_t,int32_t);
void setuptvlineasm(int32_t);
int32_t tvlineasm1(int32_t,int32_t,int32_t,int32_t,int32_t,int32_t);
void setuptvlineasm2(int32_t,int32_t,int32_t);
void tvlineasm2(uint32_t,uint32_t,uint32_t,uint32_t,uint32_t,uint32_t);
int32_t mvlineasm1(int32_t,int32_t,int32_t,int32_t,int32_t,int32_t);
void setupvlineasm(int32_t);
void vlineasm4(int32_t,int32_t);
void setupmvlineasm(int32_t);
void mvlineasm4(int32_t,int32_t);
void setupspritevline(int32_t,int32_t,int32_t,int32_t,int32_t,int32_t);
void spritevline(int32_t,uint32_t,int32_t,uint32_t,int32_t,int32_t);
void msetupspritevline(int32_t,int32_t,int32_t,int32_t,int32_t,int32_t);
void mspritevline(int32_t,int32_t,int32_t,int32_t,int32_t,int32_t);
void tsetupspritevline(int32_t,int32_t,int32_t,int32_t,int32_t,int32_t);
void tspritevline(int32_t,int32_t,int32_t,uint32_t,int32_t,int32_t);
void mhline(int32_t,int32_t,int32_t,int32_t,int32_t,int32_t);
void mhlineskipmodify(int32_t,uint32_t,uint32_t,int32_t,int32_t,int32_t);
void msethlineshift(int32_t,int32_t);
void thline(int32_t,int32_t,int32_t,int32_t,int32_t,int32_t);
void thlineskipmodify(int32_t,uint32_t,uint32_t,int32_t,int32_t,int32_t);
void tsethlineshift(int32_t,int32_t);
void setupslopevlin(int32_t,int32_t,int32_t);
void slopevlin(int32_t,uint32_t,int32_t,int32_t,int32_t,int32_t);
#define TRANS_NORMAL  0
#define TRANS_REVERSE 1
void settrans(int32_t type);



int32_t is_vmware_running(void);

    
#ifdef __cplusplus
}
#endif

//FCS: In order to see how the engine renders different part of the screen you can set the following macros
//VISUALIZE RENDERER

#define MAX_PIXEL_RENDERERED (800*600)
extern uint32_t pixelsAllowed;

#define RENDER_DRAW_WALL_BORDERS 1
#define RENDER_DRAW_WALL_INSIDE 1
#define RENDER_DRAW_CEILING_AND_FLOOR 1
#define RENDER_DRAW_TOP_AND_BOTTOM_COLUMN 1
#define RENDER_SLOPPED_CEILING_AND_FLOOR 1

#if RENDER_DRAW_WALL_BORDERS && RENDER_DRAW_WALL_INSIDE && RENDER_DRAW_CEILING_AND_FLOOR  && RENDER_DRAW_TOP_AND_BOTTOM_COLUMN && RENDER_SLOPPED_CEILING_AND_FLOOR && MAX_PIXEL_RENDERERED!=0
   #define CLEAR_FRAMEBUFFER 0
#else
   #define CLEAR_FRAMEBUFFER 1
#endif
//END VISUALIZE RENDERER

#endif /* include-once-blocker. */

/* end of a.h ... */


