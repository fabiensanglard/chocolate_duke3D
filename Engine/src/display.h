/*
 * "Build Engine & Tools" Copyright (c) 1993-1997 Ken Silverman
 * Ken Silverman's official web site: "http://www.advsys.net/ken"
 * See the included license file "BUILDLIC.TXT" for license info.
 * This file IS NOT A PART OF Ken Silverman's original release
 */

#ifndef _INCLUDE_DISPLAY_H_
#define _INCLUDE_DISPLAY_H_

#include "platform.h"

#if (defined PLATFORM_SUPPORTS_SDL)
#include "SDL.h"

/* environment variables names... */
/* These are only honored by the SDL driver. */
#define BUILD_NOMOUSEGRAB    "BUILD_NOMOUSEGRAB"
#define BUILD_WINDOWED       "BUILD_WINDOWED"
#define BUILD_SDLDEBUG       "BUILD_SDLDEBUG"
#define BUILD_RENDERER       "BUILD_RENDERER"
#define BUILD_GLLIBRARY      "BUILD_GLLIBRARY"
#define BUILD_USERSCREENRES  "BUILD_USERSCREENRES"
#define BUILD_MAXSCREENRES   "BUILD_MAXSCREENRES"
#define BUILD_HALLOFMIRRORS  "BUILD_HALLOFMIRRORS"
#define BUILD_GLDUMP         "BUILD_GLDUMP"
#define BUILD_SDLJOYSTICK    "BUILD_SDLJOYSTICK"

/* This part sucks. */
#if (defined __WATCOMC__)
#pragma aux (__cdecl) SDL_Init;
#pragma aux (__cdecl) SDL_PumpEvents;
#pragma aux (__cdecl) SDL_PollEvent;
#pragma aux (__cdecl) SDL_GetMouseState;
#pragma aux (__cdecl) SDL_WM_GrabInput;
#pragma aux (__cdecl) SDL_GetError;
#pragma aux (__cdecl) SDL_SetEventFilter;
#pragma aux (__cdecl) SDL_WM_SetCaption;
#pragma aux (__cdecl) SDL_ClearError;
#pragma aux (__cdecl) SDL_SetVideoMode;
#pragma aux (__cdecl) SDL_ClearError;
#pragma aux (__cdecl) SDL_Quit;
#pragma aux (__cdecl) SDL_QuitSubSystem;
#pragma aux (__cdecl) SDL_GetTicks;
#pragma aux (__cdecl) SDL_GetVideoInfo;
#pragma aux (__cdecl) SDL_ListModes;
#pragma aux (__cdecl) SDL_SetColors;
#pragma aux (__cdecl) SDL_ShowCursor;
#pragma aux (__cdecl) SDL_LockSurface;
#pragma aux (__cdecl) SDL_UnlockSurface;
#pragma aux (__cdecl) SDL_FillRect;
#pragma aux (__cdecl) SDL_Delay;
#pragma aux (__cdecl) SDL_AddTimer;
#pragma aux (__cdecl) SDL_RemoveTimer;
#pragma aux (__cdecl) SDL_Flip;
#pragma aux (__cdecl) SDL_UpdateRect;
#pragma aux (__cdecl) SDL_GetVideoSurface;
#pragma aux (__cdecl) SDL_VideoDriverName;
#pragma aux (__cdecl) SDL_SetPalette;
#pragma aux (__cdecl) SDL_VideoModeOK;
#pragma aux (__cdecl) SDL_GetClipRect;
#pragma aux (__cdecl) SDL_SetClipRect;
#pragma aux (__cdecl) SDL_WM_ToggleFullScreen;
#pragma aux (__cdecl) SDL_Linked_Version;
#endif  /* defined __WATCOMC__ */

#endif  /* defined PLATFORM_SUPPORTS_SDL */

/* set these in your _platform_init() implementation. */
extern int _argc;
extern char **_argv;

/* !!! gads, look at all the namespace polution... */
extern long xres, yres, bytesperline, imageSize, maxpages;
extern char *screen, vesachecked;
extern long buffermode, origbuffermode, linearmode;
extern char permanentupdate, vgacompatible;
extern char moustat;
extern long *horizlookup, *horizlookup2, horizycent;
extern long oxdimen, oviewingrange, oxyaspect;
extern long curbrightness;
extern long qsetmode;
extern long frameplace, frameoffset, pageoffset, ydim16;
extern char textfont[1024], smalltextfont[1024];
extern char pow2char[8];
extern volatile long stereomode, visualpage, activepage, whiteband, blackband;
extern long searchx, searchy;
extern long wx1, wy1, wx2, wy2, ydimen;
extern long xdimen, xdimenrecip, halfxdimen, xdimenscale, xdimscale;

/*
 * !!! used to be static. If we ever put the original setgamemode() back, this
 * !!! can be made static again.  --ryan.
 * !!! (Actually, most of these extern declarations used to be static...rcg.)
 */
extern unsigned char permanentlock;

// defined in the game project:
extern long BFullScreen;  // defined in Game\src\config.c
extern long ScreenMode;


/* these need to be implemented by YOUR driver. */
void _platform_init(int argc, char **argv, const char *title, const char *icon);
void _idle(void);
void _handle_events(void);
void *_getVideoBase(void);
void initkeys(void);
void uninitkeys(void);
void _nextpage(void);
void _uninitengine(void);
void _joystick_init(void);
void _joystick_deinit(void);
int _joystick_update(void);
int _joystick_axis(int axis);
int _joystick_hat(int hat);
int _joystick_button(int button);

/*
 * VESA replacement code: The Unix (not-actually-VESA) version of this is
 *  originally using SDL (Simple Directmedia Layer: http://www.libsdl.org/),
 *  and is stored in sdl_driver.c, but there's no reason another driver
 *  couldn't be dropped in, so long as it implements these functions. Please
 *  reference sdl_driver.c and ves2.h (the original code) for all the nuances
 *  and global variables that need to get set up correctly.
 */
void getvalidvesamodes(void);
int VBE_getPalette(long start, long num, char *dapal);
int VBE_setPalette(long start, long num, char *palettebuffer);
int setvesa(long x, long y);
void uninitvesa(void);
void setvmode(int mode);
unsigned char readpixel(long offset);
void drawpixel(long offset, Uint8 pixel);
void drawpixels(long offset, Uint16 pixels);
void drawpixelses(long offset, Uint32 pixelses);
void drawpixel16(long offset);
void fillscreen16 (long input1, long input2, long input3);
void limitrate(void);
void setactivepage(long dapagenum);
void clear2dscreen(void);
void _updateScreenRect(long x, long y, long w, long h);

/* mouse/keystuff stuff. Also implemented in sdl_driver.c ... */
int setupmouse(void);
void readmousexy(short *x, short *y);
void readmousebstatus(short *bstatus);
void __interrupt __far keyhandler(void);
unsigned char _readlastkeyhit(void);

/* timer krap. */
int inittimer(int);
void uninittimer(void);

/* this is implemented in the game, and your driver calls it. */
void __interrupt __far timerhandler(void);

/* resolution inits. sdl_driver.c ... */
int _setgamemode(char davidoption, long daxdim, long daydim);

unsigned long getticks();

void drawline16(long XStart, long YStart, long XEnd, long YEnd, char Color);
void setcolor16(int i1);

int using_opengl(void);

#endif  /* _INCLUDE_DISPLAY_H_ */

/* end of display.h ... */


