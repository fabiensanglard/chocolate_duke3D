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

Original Source: 1996 - Todd Replogle
Prepared for public release: 03/21/2003 - Charlie Wiederhold, 3D Realms
*/
//-------------------------------------------------------------------------
#ifndef _INCL_DUKE3D_H_
#define _INCL_DUKE3D_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>

#include <fcntl.h>
#include <time.h>
#include <ctype.h>

#include "cache1d.h"

#if (!defined MAX_PATH)
  #if (defined MAXPATHLEN)
    #define MAX_PATH MAXPATHLEN
  #elif (defined PATH_MAX)
    #define MAX_PATH PATH_MAX
  #else
    #define MAX_PATH 256
  #endif
#endif

#if PLATFORM_DOS
#include <dos.h>
#include <bios.h>
#include <io.h>
#define PATH_SEP_CHAR '\\'
#define PATH_SEP_STR  "\\"
#endif

#if PLATFORM_UNIX
#include "dukeunix.h"
#endif

#if PLATFORM_WIN32
#include "dukewin.h"
#endif

#if USE_SDL
#include "SDL.h"
#include "SDL_mixer.h"
#endif

#include "build.h"
#include "function.h"

//  FIX_00022: Automatically recognize the shareware grp (v1.3) + full version (1.3d) +
//             atomic (1.4/1.5 grp) and the con files version (either 1.3 or 1.4) (JonoF's idea)

extern unsigned char conVersion;
extern unsigned char grpVersion;
extern long groupefil_crc32[MAXGROUPFILES];

#define RANCID_ID 1
#define	XDUKE_ID  2
#define JONOF_ID  3

#define DUKE_ID			XDUKE_ID
#define	XDUKE_REV_X		19
#define XDUKE_REV_DOT_Y	7   // rev is: vXDUKE_REV_X.XDUKE_REV_DOT_Y
#define XDUKE_SUBVERSION 1

#define MAX_KNOWN_GRP 4

enum
{
	UNKNOWN_GRP = 0,
	SHAREWARE_GRP13,
	REGULAR_GRP13D,
	ATOMIC_GRP14_15,
	DUKEITOUTINDC_GRP
};

#define CRC_BASE_GRP_SHAREWARE_13	0x983AD923
#define CRC_BASE_GRP_FULL_13		0xBBC9CE44
#define CRC_BASE_GRP_PLUTONIUM_14	0xF514A6AC
#define CRC_BASE_GRP_ATOMIC_15		0xFD3DCFF1 

#define PLUTOPAK  (!VOLUMEONE && !VOLUMEALL) // implies  conVersion == 14 or conVersion == 15
#define VOLUMEONE (groupefil_crc32[0]==CRC_BASE_GRP_SHAREWARE_13)
// VOLUMEALL = 1.3d full
#define VOLUMEALL (groupefil_crc32[0]==CRC_BASE_GRP_FULL_13 || conVersion == 13 && groupefil_crc32[0]!=CRC_BASE_GRP_SHAREWARE_13 && groupefil_crc32[0]!=CRC_BASE_GRP_PLUTONIUM_14 && groupefil_crc32[0]!=CRC_BASE_GRP_ATOMIC_15)

#define SCREENSHOTPATH "screenshots"

// #define ONELEVELDEMO

// #define TEN
// #define BETA

// #define AUSTRALIA

#define MAXSLEEPDIST  16384
#define SLEEPTIME 24*64

extern int BYTEVERSION;

extern int BYTEVERSION_27;
extern int BYTEVERSION_28;
extern int BYTEVERSION_29; // really needed???
extern int BYTEVERSION_116;
extern int BYTEVERSION_117; 
extern int BYTEVERSION_118; 
extern int BYTEVERSION_1_3;


#define NUMPAGES 1

#define AUTO_AIM_ANGLE          48
#define RECSYNCBUFSIZ 2520   //2520 is the (LCM of 1-8)*3
#define MOVEFIFOSIZ 256

#define FOURSLEIGHT (1<<8)

struct player_struct;

#include "types.h"
#include "file_lib.h"
#include "develop.h"
#include "gamedefs.h"
#include "keyboard.h"
#include "util_lib.h"
#include "function.h"
#include "audiolib\fx_man.h"
#include "config.h"
#include "sounds.h"
#include "control.h"
#include "_rts.h"
#include "rts.h"
#include "soundefs.h"

#if PLATFORM_DOS
#include "audiolib\task_man.h"
#include "audiolib\sndcards.h"
#endif
#include "audiolib\music.h"

#include "names.h"

#include "engine.h"
#include "pragmas.h"

//#define TICRATE (120)
//#define TICSPERFRAME (TICRATE/26)

extern int g_iTickRate;
extern int g_iTicksPerFrame;

#define TICRATE g_iTickRate
#define TICSPERFRAME (TICRATE/g_iTicksPerFrame)

// #define GC (TICSPERFRAME*44)

#define NUM_SOUNDS 450

#define    ALT_IS_PRESSED ( KB_KeyPressed( sc_RightAlt ) || KB_KeyPressed( sc_LeftAlt ) )
#define    SHIFTS_IS_PRESSED ( KB_KeyPressed( sc_RightShift ) || KB_KeyPressed( sc_LeftShift ) )
#define    RANDOMSCRAP EGS(s->sectnum,s->x+(TRAND&255)-128,s->y+(TRAND&255)-128,s->z-(8<<8)-(TRAND&8191),SCRAP6+(TRAND&15),-8,48,48,TRAND&2047,(TRAND&63)+64,-512-(TRAND&2047),i,5)

#define    BLACK 0
#define    DARKBLUE 1
#define    DARKGREEN 2
#define    DARKCYAN 3
#define    DARKRED 4
#define    DARKPURPLE 5
#define    BROWN 6
#define    LIGHTGRAY 7

#define    DARKGRAY 8
#define    BLUE 9
#define    GREEN 10
#define    CYAN 11
#define    RED 12
#define    PURPLE 13
#define    YELLOW 14
#define    WHITE 15

#define    PHEIGHT (38<<8)

// #define P(X) printf("%ld\n",X);

#define WAIT(X) ototalclock=totalclock+(X);while(totalclock<ototalclock)


#define MODE_MENU       1
#define MODE_DEMO       2
#define MODE_GAME       4
#define MODE_EOL        8
#define MODE_TYPE       16
#define MODE_RESTART    32
#define MODE_SENDTOWHOM 64
#define MODE_END        128


#define MAXANIMWALLS 512
#define MAXINTERPOLATIONS 2048
#define NUMOFFIRSTTIMEACTIVE 192

#define MAXCYCLERS 256
#define MAXSCRIPTSIZE 20460
#define MAXANIMATES 64

#define SP  sprite[i].yvel
#define SX  sprite[i].x
#define SY  sprite[i].y
#define SZ  sprite[i].z
#define SS  sprite[i].shade
#define PN  sprite[i].picnum
#define SA  sprite[i].ang
#define SV  sprite[i].xvel
#define ZV  sprite[i].zvel
#define RX  sprite[i].xrepeat
#define RY  sprite[i].yrepeat
#define OW  sprite[i].owner
#define CS  sprite[i].cstat
#define SH  sprite[i].extra
#define CX  sprite[i].xoffset
#define CY  sprite[i].yoffset
#define CD  sprite[i].clipdist
#define PL  sprite[i].pal
#define SLT  sprite[i].lotag
#define SHT  sprite[i].hitag
#define SECT sprite[i].sectnum

#define face_player 1
#define geth 2
#define getv 4
#define random_angle 8
#define face_player_slow 16
#define spin 32
#define face_player_smart 64
#define fleeenemy 128
#define jumptoplayer 257
#define seekplayer 512
#define furthestdir 1024
#define dodgebullet 4096

#ifdef DBGRECORD
#define TRAND krand(__LINE__,__FILE__)
#else
#define TRAND krand()
#endif

#define MAX_WEAPONS  12

#define KNEE_WEAPON          0
#define PISTOL_WEAPON        1
#define SHOTGUN_WEAPON       2
#define CHAINGUN_WEAPON      3
#define RPG_WEAPON           4
#define HANDBOMB_WEAPON      5
#define SHRINKER_WEAPON      6
#define DEVISTATOR_WEAPON    7
#define TRIPBOMB_WEAPON      8
#define FREEZE_WEAPON        9
#define HANDREMOTE_WEAPON    10
#define GROW_WEAPON          11

#define T1  hittype[i].temp_data[0]
#define T2  hittype[i].temp_data[1]
#define T3  hittype[i].temp_data[2]
#define T4  hittype[i].temp_data[3]
#define T5  hittype[i].temp_data[4]
#define T6  hittype[i].temp_data[5]

#define ESCESCAPE if(KB_KeyPressed( sc_Escape ) ) gameexit(" ");

#define IFWITHIN(B,E) if((PN)>=(B) && (PN)<=(E))
#define KILLIT(KX) {deletesprite(KX);goto BOLT;}


#define IFMOVING if(ssp(i,CLIPMASK0))
#define IFHIT j=ifhitbyweapon(i);if(j >= 0)
#define IFHITSECT j=ifhitsectors(s->sectnum);if(j >= 0)

#define AFLAMABLE(X) (X==BOX||X==TREE1||X==TREE2||X==TIRE||X==CONE)


#define IFSKILL1 if(player_skill<1)
#define IFSKILL2 if(player_skill<2)
#define IFSKILL3 if(player_skill<3)
#define IFSKILL4 if(player_skill<4)

#define rnd(X) ((TRAND>>8)>=(255-(X)))

typedef struct
{
    short i;
    int voice;
} SOUNDOWNER;

#define __USRHOOKS_H

enum USRHOOKS_Errors
   {
   USRHOOKS_Warning = -2,
   USRHOOKS_Error   = -1,
   USRHOOKS_Ok      = 0
   };

#pragma pack(push)
#pragma pack(1)

typedef struct
{
    signed char avel, horz;
    short fvel, svel;
    unsigned long bits;
} input;

#pragma pack(pop)

/* !!! FIXME: "sync" is defined in unistd.h ... :(  --ryan. */
#define sync duke_sync
extern input inputfifo[MOVEFIFOSIZ][MAXPLAYERS], sync[MAXPLAYERS];
extern input recsync[RECSYNCBUFSIZ];

extern long movefifosendplc;

typedef struct
{
    char *ptr;
    volatile char lock;
    int  length, num;
} SAMPLE;

struct animwalltype
{
        short wallnum;
        long tag;
};
extern struct animwalltype animwall[MAXANIMWALLS];
extern short numanimwalls,probey,lastprobey;

extern char *mymembuf;
extern char typebuflen,typebuf[41];
extern char MusicPtr[72000];
extern long msx[2048],msy[2048];
extern short cyclers[MAXCYCLERS][6],numcyclers;
extern char myname[2048];

struct user_defs
{
    char god,warp_on,cashman,eog,showallmap;
    char show_help,scrollmode,clipping;
    char user_name[MAXPLAYERS][32];
    char ridecule[10][40];
    char savegame[10][22];
    char pwlockout[128],rtsname[128];
    char overhead_on,last_overhead;

    short pause_on,from_bonus;
    short camerasprite,last_camsprite;
    short last_level,secretlevel;

    long const_visibility,uw_framerate;
    long camera_time,folfvel,folavel,folx,foly,fola;
    long reccnt;

    int32 entered_name,screen_tilting,shadows,fta_on,executions,auto_run;
    int32 coords,tickrate,m_coop,coop,screen_size,extended_screen_size,lockout,crosshair,showweapons;
    int32 mywchoice[MAX_WEAPONS],wchoice[MAXPLAYERS][MAX_WEAPONS],playerai;

    int32 respawn_monsters,respawn_items,respawn_inventory,recstat,monsters_off,brightness;
    int32 m_respawn_items,m_respawn_monsters,m_respawn_inventory,m_recstat,m_monsters_off,detail;
	// FIX_00082: /q option taken off when playing a demo (multimode_bot)    
	int32 m_ffire,ffire,m_player_skill,m_level_number,m_volume_number,multimode,multimode_bot;
    int32 player_skill,level_number,volume_number,m_marker,marker,mouseflip;

	int32 showcinematics, hideweapon;
	int32 auto_aim, gitdat_mdk; //AutoAim toggle variable.
	int32 weaponautoswitch;

	// FIX_00015: Backward compliance with older demos (down to demos v27, 28, 116 and 117 only)
	char playing_demo_rev;

	unsigned long groupefil_crc32[MAXPLAYERS][MAXGROUPFILES];
	unsigned short conSize[MAXPLAYERS];

#ifdef CHECK_XDUKE_REV
	char rev[MAXPLAYERS][10];
#endif
	unsigned long mapCRC[MAXPLAYERS];
	unsigned long exeCRC[MAXPLAYERS];
	unsigned long conCRC[MAXPLAYERS];
};

struct player_orig
{
    long ox,oy,oz;
    short oa,os;
};


extern char numplayersprites;
extern char picsiz[MAXTILES];

typedef struct
{
	unsigned int crc32;
	char* name;
	unsigned long size;
} crc32_t;

extern crc32_t crc32lookup[];

void add_ammo( short, short, short, short );


extern long fricxv,fricyv;

struct player_struct
{
    long zoom,exitx,exity,loogiex[64],loogiey[64],numloogs,loogcnt;
    long posx, posy, posz, horiz, ohoriz, ohorizoff, invdisptime;
    long bobposx,bobposy,oposx,oposy,oposz,pyoff,opyoff;
    long posxv,posyv,poszv,last_pissed_time,truefz,truecz;
    long player_par,visibility;
    long bobcounter,weapon_sway;
    long pals_time,randomflamex,crack_time;

    int32 aim_mode;

    short ang,oang,angvel,cursectnum,look_ang,last_extra,subweapon;
    short ammo_amount[MAX_WEAPONS],wackedbyactor,frag,fraggedself;

    short curr_weapon, last_weapon, tipincs, horizoff, wantweaponfire;
    short holoduke_amount,newowner,hurt_delay,hbomb_hold_delay;
    short jumping_counter,airleft,knee_incs,access_incs;
    short fta,ftq,access_wallnum,access_spritenum;
    short kickback_pic,got_access,weapon_ang,firstaid_amount;
    short somethingonplayer,on_crane,i,one_parallax_sectnum;
    short over_shoulder_on,random_club_frame,fist_incs;
    short one_eighty_count,cheat_phase;
    short dummyplayersprite,extra_extra8,quick_kick;
    short heat_amount,actorsqu,timebeforeexit,customexitsound;

    short weaprecs[16],weapreccnt;
	unsigned long interface_toggle_flag;

    short rotscrnang,dead_flag,show_empty_weapon;
    short scuba_amount,jetpack_amount,steroids_amount,shield_amount;
    short holoduke_on,pycount,weapon_pos,frag_ps;
    short transporter_hold,last_full_weapon,footprintshade,boot_amount;

    int scream_voice;

    char gm,on_warping_sector,footprintcount;
    char hbomb_on,jumping_toggle,rapid_fire_hold,on_ground;
    char name[32],inven_icon,buttonpalette;

    char jetpack_on,spritebridge,lastrandomspot;
    char scuba_on,footprintpal,heat_on;

    char  holster_weapon,falling_counter;
    char  gotweapon[MAX_WEAPONS],refresh_inventory,*palette;

    char toggle_key_flag,knuckle_incs; // ,select_dir;
    char walking_snd_toggle, palookup, hard_landing;
    char max_secret_rooms,secret_rooms,/*fire_flag,*/pals[3];
    char max_actors_killed,actors_killed,return_to_center;

	// local but synch variables (ud is local but not synch):

	// FIX_00023: Moved Addfaz's autoaim handler to synch variables (to avoid out of synch)
	int32 auto_aim; //AutoAim toggle variable.

	// FIX_00012: added "weapon autoswitch" toggle allowing to turn the autoswitch off
	//            when picking up new weapons. The weapon sound on pickup will remain on, to not 
	//           affect the opponent's gameplay (so he can still hear you picking up new weapons)
	int32 weaponautoswitch;

	char fakeplayer;
};

extern unsigned char tempbuf[2048], packbuf[576];

extern long gc,max_player_health,max_armour_amount,max_ammo_amount[MAX_WEAPONS];

extern long impact_damage,respawnactortime,respawnitemtime;

#define MOVFIFOSIZ 256

extern short spriteq[1024],spriteqloc,spriteqamount;
extern struct player_struct ps[MAXPLAYERS];
extern struct player_orig po[MAXPLAYERS];
extern struct user_defs ud;

// ported build engine has this, too.  --ryan.
#if PLATFORM_DOS
extern short int moustat;
#endif

extern short int global_random;
extern long scaredfallz;
extern char buf[80]; //My own generic input buffer

extern char fta_quotes[NUMOFFIRSTTIMEACTIVE][64];
extern char scantoasc[128],ready2send;
extern char scantoascwithshift[128];

extern fx_device device;
extern SAMPLE Sound[ NUM_SOUNDS ];
extern int32 VoiceToggle,AmbienceToggle, OpponentSoundToggle;
extern int32 mouseSensitivity_X, mouseSensitivity_Y;
extern SOUNDOWNER SoundOwner[NUM_SOUNDS][4];

extern char playerreadyflag[MAXPLAYERS],playerquitflag[MAXPLAYERS];
extern char sounds[NUM_SOUNDS][14];

extern long script[MAXSCRIPTSIZE],*scriptptr,*insptr,*labelcode,labelcnt;
extern char *label,*textptr,error,warning,killit_flag;
extern long *actorscrptr[MAXTILES],*parsing_actor;
extern char actortype[MAXTILES];
extern char *music_pointer;

extern char ipath[80],opath[80];

extern char music_fn[4][11][13],music_select;
extern char env_music_fn[4][13];
extern short camsprite;

// extern char gotz;
extern char inspace(short sectnum);


struct weaponhit
{
    char cgg;
    short picnum,ang,extra,owner,movflag;
    short tempang,actorstayput,dispicnum;
    short timetosleep;
    long floorz,ceilingz,lastvx,lastvy,bposx,bposy,bposz;
    long temp_data[6];
};

extern struct weaponhit hittype[MAXSPRITES];

extern input loc;
extern input recsync[RECSYNCBUFSIZ];
extern long avgfvel, avgsvel, avgavel, avghorz, avgbits;

extern short numplayers, myconnectindex;
extern short connecthead, connectpoint2[MAXPLAYERS];   //Player linked list variables (indeces, not connection numbers)
extern short screenpeek;

extern int current_menu;
extern long tempwallptr,animatecnt;
extern long lockclock,frameplace;
extern char display_mirror,rtsplaying;

extern long movefifoend[MAXPLAYERS];
extern long ototalclock;

extern long *animateptr[MAXANIMATES], animategoal[MAXANIMATES];
extern long animatevel[MAXANIMATES];
// extern long oanimateval[MAXANIMATES];
extern short neartagsector, neartagwall, neartagsprite;
extern long neartaghitdist;
extern short animatesect[MAXANIMATES];
extern long movefifoplc, vel,svel,angvel,horiz;

extern short mirrorwall[64], mirrorsector[64], mirrorcnt;

#define NUMKEYS 19

extern long frameplace, chainplace, chainnumpages;
extern volatile long checksume;

#include "funct.h"
#include "engine_protos.h"

extern char screencapt;
extern short soundps[NUM_SOUNDS],soundpe[NUM_SOUNDS],soundvo[NUM_SOUNDS];
extern char soundpr[NUM_SOUNDS],soundm[NUM_SOUNDS];
extern long soundsiz[NUM_SOUNDS];
extern char level_names[44][33];
extern long partime[44],designertime[44];
extern char volume_names[4][33];
extern char skill_names[5][33];
extern char level_file_names[44][128];

extern int32 SoundToggle,MusicToggle;
extern short last_threehundred,lastsavedpos;
extern char restorepalette;

extern short buttonstat;
extern long cachecount;
extern char boardfilename[128],waterpal[768],slimepal[768],titlepal[768],drealms[768],endingpal[768];
extern char betaname[80];
extern char cachedebug,earthquaketime;
extern char networkmode;
extern char lumplockbyte[11];

    //DUKE3D.H - replace the end "my's" with this
extern long myx, omyx, myxvel, myy, omyy, myyvel, myz, omyz, myzvel;
extern short myhoriz, omyhoriz, myhorizoff, omyhorizoff, globalskillsound;
extern short myang, omyang, mycursectnum, myjumpingcounter;
extern char myjumpingtoggle, myonground, myhardlanding,myreturntocenter;
extern long fakemovefifoplc;
extern long myxbak[MOVEFIFOSIZ], myybak[MOVEFIFOSIZ], myzbak[MOVEFIFOSIZ];
extern long myhorizbak[MOVEFIFOSIZ];
extern short myangbak[MOVEFIFOSIZ];

extern short weaponsandammosprites[15];




//DUKE3D.H:
typedef struct
{
        short frag[MAXPLAYERS], got_access, last_extra, shield_amount, curr_weapon;
        short ammo_amount[MAX_WEAPONS], holoduke_on;
        char gotweapon[MAX_WEAPONS], inven_icon, jetpack_on, heat_on;
        short firstaid_amount, steroids_amount, holoduke_amount, jetpack_amount;
        short heat_amount, scuba_amount, boot_amount;
        short last_weapon, weapon_pos, kickback_pic;

} STATUSBARTYPE;

extern STATUSBARTYPE sbar;
extern short frags[MAXPLAYERS][MAXPLAYERS];
extern long cameradist, cameraclock, dukefriction,show_shareware;
extern char networkmode, movesperpacket;
extern char gamequit;

extern char pus,pub,camerashitable,freezerhurtowner,lasermode;
extern char syncstat, syncval[MAXPLAYERS][MOVEFIFOSIZ];
extern signed char multiwho, multipos, multiwhat, multiflag;
extern long syncvalhead[MAXPLAYERS], syncvaltail, syncvaltottail;
extern long numfreezebounces,rpgblastradius,pipebombblastradius,tripbombblastradius,shrinkerblastradius,morterblastradius,bouncemineblastradius,seenineblastradius;
// CTW - MODIFICATION
// extern char stereo,eightytwofifty,playerswhenstarted,playonten,everyothertime;
extern char stereo,eightytwofifty,playerswhenstarted,everyothertime;
// CTW END - MODIFICATION
extern long myminlag[MAXPLAYERS], mymaxlag, otherminlag, bufferjitter;

extern long numinterpolations, startofdynamicinterpolations;
extern long oldipos[MAXINTERPOLATIONS];
extern long bakipos[MAXINTERPOLATIONS];
extern long *curipos[MAXINTERPOLATIONS];

extern short numclouds,clouds[128],cloudx[128],cloudy[128];
extern long cloudtotalclock,totalmemory;

extern long stereomode, stereowidth, stereopixelwidth;

extern long myaimmode, myaimstat, omyaimstat;

extern unsigned char nHostForceDisableAutoaim;

#endif  // include-once header.

