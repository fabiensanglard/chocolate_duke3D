// "Build Engine & Tools" Copyright (c) 1993-1997 Ken Silverman
// Ken Silverman's official web site: "http://www.advsys.net/ken"
// See the included license file "BUILDLIC.TXT" for license info.
// This file has been modified from Ken Silverman's original release

/* DDOI - This file is an attempt to reimplement a_nasm.asm in C */

#include "platform.h"
#include "build.h"


#define shrd(a,b,c) (((b)<<(32-(c))) | ((a)>>(c)))
#define shld(a,b,c) (((b)>>(32-(c))) | ((a)<<(c)))

extern int32_t asm1;
extern int32_t asm2;
extern int32_t asm3;
extern int32_t asm4;


/* #pragma aux mmxoverlay modify [eax ebx ecx edx] */
int32_t mmxoverlay(void)
{
    return 0;
} /* mmxoverlay */

/* #pragma aux sethlinesizes parm [eax][ebx][ecx] */
static uint8_t machxbits_al;
static uint8_t machxbits_bl;
static int32_t machxbits_ecx;
void sethlinesizes(int32_t i1, int32_t i2, int32_t i3)
{
    machxbits_al = i1;
    machxbits_bl = i2;
    machxbits_ecx = i3;
} /* sethlinesizes */

static uint8_t* pal_eax;
void setuphlineasm4(int32_t i1, int32_t i2) { }
void setpalookupaddress(uint8_t *i1) { pal_eax = i1; }

//FCS:   Draw ceiling/floors
void hlineasm4(int32_t _count, uint32_t unused_source, int32_t _shade, uint32_t _i4, uint32_t _i5, int32_t i6)
{
    /* force into registers (probably only useful on PowerPC)... */
    uint8_t *dest = (uint8_t *) i6;
    uint32_t i4 = _i4;
    uint32_t i5 = _i5;
    int32_t shifter = ((256-machxbits_al) & 0x1f);
    uint32_t source;
    int32_t shade = _shade & 0xffffff00;
    int32_t count = _count + 1;
    register uint8_t  bits = machxbits_bl;
    register uint8_t  *lookup = (uint8_t *) machxbits_ecx;
    register uint8_t  *pal = (uint8_t *) pal_eax;
    int32_t _asm1 = asm1;
    int32_t _asm2 = asm2;

	if (!RENDER_DRAW_CEILING_AND_FLOOR)
		return;

    while (count) {
	    source = i5 >> shifter;
	    source = shld(source,i4,bits);
	    source = lookup[source];
	    *dest = pal[shade|source];
	    dest--;
	    i5 -= _asm1;
	    i4 -= _asm2;
	    count--;
    }
}

static int32_t rmach_eax;
static int32_t rmach_ebx;
static int32_t rmach_ecx;
static int32_t rmach_edx;
static int32_t rmach_esi;
void setuprhlineasm4(int32_t i1, int32_t i2, int32_t i3, int32_t i4, int32_t i5, int32_t i6)
{
    rmach_eax = i1;
    rmach_ebx = i2;
    rmach_ecx = i3;
    rmach_edx = i4;
    rmach_esi = i5;
} 


void rhlineasm4(int32_t i1, int32_t i2, int32_t i3, uint32_t i4, uint32_t i5, int32_t numPixels)
{
    uint32_t ebp = numPixels - i1;
    uint32_t rmach6b = ebp-1;

    if (i1 <= 0) return;

    numPixels = i1;
    do {
	    i3 = ((i3&0xffffff00)|(*((uint8_t *)i2)));
	    i4 -= rmach_eax;
	    ebp = (((i4+rmach_eax) < i4) ? -1 : 0);
	    i5 -= rmach_ebx;
	    if ((i5 + rmach_ebx) < i5) i2 -= (rmach_ecx+1);
	    else i2 -= rmach_ecx;
	    ebp &= rmach_esi;
	    i1 = ((i1&0xffffff00)|(((uint8_t *)i3)[rmach_edx]));
	    ((uint8_t *)rmach6b)[numPixels] = (i1&0xff);
	    i2 -= ebp;
	    numPixels--;
    } while (numPixels);
} /* rhlineasm4 */

static int32_t rmmach_eax;
static int32_t rmmach_ebx;
static int32_t rmmach_ecx;
static int32_t rmmach_edx;
static int32_t rmmach_esi;
void setuprmhlineasm4(int32_t i1, int32_t i2, int32_t i3, int32_t i4, int32_t i5, int32_t i6)
{
    rmmach_eax = i1;
    rmmach_ebx = i2;
    rmmach_ecx = i3;
    rmmach_edx = i4;
    rmmach_esi = i5;
} 


//FCS: ????
void rmhlineasm4(int32_t i1, int32_t i2, int32_t i3, int32_t i4, int32_t i5, int32_t numPixels)
{
    uint32_t ebp = numPixels - i1;
    uint32_t rmach6b = ebp-1;

    if (i1 <= 0) return;

    numPixels = i1;
    do {
	    i3 = ((i3&0xffffff00)|(*((uint8_t *)i2)));
	    i4 -= rmmach_eax;
	    ebp = (((i4+rmmach_eax) < i4) ? -1 : 0);
	    i5 -= rmmach_ebx;
	    if ((i5 + rmmach_ebx) < i5) i2 -= (rmmach_ecx+1);
	    else i2 -= rmmach_ecx;
	    ebp &= rmmach_esi;
	    if ((i3&0xff) != 255) {
		    i1 = ((i1&0xffffff00)|(((uint8_t  *)i3)[rmmach_edx]));
		    ((uint8_t  *)rmach6b)[numPixels] = (i1&0xff);
	    }
	    i2 -= ebp;
	    numPixels--;
    } while (numPixels);
} 



static int32_t fixchain;
void setvlinebpl(int32_t i1)
{
    fixchain = i1;
} 


static int32_t tmach;
void fixtransluscence(int32_t i1)
{
    tmach = i1;
} 

int32_t vlineasm1(int32_t i1, int32_t i2, int32_t i3, int32_t i4, int32_t i5, int32_t i6);


static uint8_t  mach3_al;

//FCS:  RENDER TOP AND BOTTOM COLUMN
int32_t prevlineasm1(int32_t i1, int32_t i2, int32_t i3, int32_t i4, int32_t i5, int32_t i6)
{
    uint8_t  *source = (uint8_t  *)i5;
    uint8_t  *dest = (uint8_t  *)i6;

	

    if (i3 == 0)
    {
		if (!RENDER_DRAW_TOP_AND_BOTTOM_COLUMN)
		return 0;

	    i1 += i4;
        //FCS
        //((uint32_t)i4) >>= mach3_al;
        i4 = ((uint32_t)i4) >> mach3_al;
	    i4 = (i4&0xffffff00) | (source[i4]&0xff);
	    *dest = ((uint8_t *)i2)[i4];
	    return i1;
    } else {
	    return vlineasm1(i1,i2,i3,i4,i5,i6);
    }
}


//FCS: This is used to draw wall border vertical lines
int32_t vlineasm1(int32_t vince, int32_t palookupoffse, int32_t numPixels, int32_t vplce, int32_t bufplce, int32_t i6)
{
    uint32_t temp;
    uint8_t  *dest = (uint8_t  *)i6;

    if (!RENDER_DRAW_WALL_BORDERS)
		return vplce;

    numPixels++;
    while (numPixels)
    {
	    temp = ((unsigned)vplce) >> mach3_al;
        
	    temp = ((uint8_t  *)bufplce)[temp];
      
        *dest = ((uint8_t *)palookupoffse)[temp];
	    vplce += vince;
	    dest += fixchain;
	    numPixels--;
    }
    return vplce;
} 


static uint8_t  transmach3_al = 32;
void setuptvlineasm(int32_t i1)
{
    transmach3_al = (i1 & 0x1f);
}


static int transrev = 0;
int32_t tvlineasm1(int32_t i1, int32_t i2, int32_t numPixels, int32_t i4, int32_t i5, int32_t i6)
{
	uint8_t  *source = (uint8_t  *)i5;
	uint8_t  *dest = (uint8_t  *)i6;

	numPixels++;
	while (numPixels)
	{
		uint32_t temp = i4;
		temp >>= transmach3_al;
		temp = source[temp];
		if (temp != 255)
		{
			unsigned short val;
			val = ((uint8_t  *)i2)[temp];
			val |= ((*dest)<<8);
			if (transrev) val = ((val>>8)|(val<<8));
			*dest = ((uint8_t  *)tmach)[val];
		}
		i4 += i1;
		dest += fixchain;
		numPixels--;
	}
	return i4;
} /* tvlineasm1 */

/* #pragma aux setuptvlineasm2 parm [eax][ebx][ecx] */
static uint8_t  tran2shr;
static uint32_t tran2pal_ebx;
static uint32_t tran2pal_ecx;
void setuptvlineasm2(int32_t i1, int32_t i2, int32_t i3)
{
	tran2shr = (i1&0x1f);
	tran2pal_ebx = i2;
	tran2pal_ecx = i3;
} /* */


void tvlineasm2(uint32_t i1, uint32_t i2, uint32_t i3, uint32_t i4, uint32_t i5, uint32_t i6)
{
	uint32_t ebp = i1;
	uint32_t tran2inca = i2;
	uint32_t tran2incb = asm1;
	uint32_t tran2bufa = i3;
	uint32_t tran2bufb = i4;
	uint32_t tran2edi = asm2;
	uint32_t tran2edi1 = asm2 + 1;

	i6 -= asm2;

	do {
		i1 = i5 >> tran2shr;
		i2 = ebp >> tran2shr;
		i5 += tran2inca;
		ebp += tran2incb;
		i3 = ((uint8_t  *)tran2bufa)[i1];
		i4 = ((uint8_t  *)tran2bufb)[i2];
		if (i3 == 255) { // skipdraw1
			if (i4 != 255) { // skipdraw3
				unsigned short val;
				val = ((uint8_t  *)tran2pal_ecx)[i4];
				val |= (((uint8_t  *)i6)[tran2edi1]<<8);
				if (transrev) val = ((val>>8)|(val<<8));
				((uint8_t  *)i6)[tran2edi1] =
					((uint8_t  *)tmach)[val];
			}
		} else if (i4 == 255) { // skipdraw2
			unsigned short val;
			val = ((uint8_t  *)tran2pal_ebx)[i3];
			val |= (((uint8_t  *)i6)[tran2edi]<<8);
			if (transrev) val = ((val>>8)|(val<<8));
			((uint8_t  *)i6)[tran2edi] =
				((uint8_t  *)tmach)[val];
		} else {
			unsigned short l = ((uint8_t  *)i6)[tran2edi]<<8;
			unsigned short r = ((uint8_t  *)i6)[tran2edi1]<<8;
			l |= ((uint8_t  *)tran2pal_ebx)[i3];
			r |= ((uint8_t  *)tran2pal_ecx)[i4];
			if (transrev) {
				l = ((l>>8)|(l<<8));
				r = ((r>>8)|(r<<8));
			}
			((uint8_t  *)i6)[tran2edi] =
				((uint8_t  *)tmach)[l];
			((uint8_t  *)i6)[tran2edi1] =
				((uint8_t  *)tmach)[r];
		}
		i6 += fixchain;
	} while (i6 > i6 - fixchain);
	asm1 = i5;
	asm2 = ebp;
} 



static uint8_t  machmv;
int32_t mvlineasm1(int32_t vince, int32_t palookupoffse, int32_t i3, int32_t vplce, int32_t bufplce, int32_t i6)
{
    uint32_t temp;
    uint8_t  *dest = (uint8_t  *)i6;

	// FIX_00087: 1024x768 mode being slow. Undone FIX_00070 and fixed font issue again
    for(;i3>=0;i3--)
    {
	    temp = ((unsigned)vplce) >> machmv;
	    temp = ((uint8_t  *)bufplce)[temp];
	    if (temp != 255) *dest = ((uint8_t *)palookupoffse)[temp];
	    vplce += vince;
	    dest += fixchain;
    }
    return vplce;
} /* mvlineasm1 */


void setupvlineasm(int32_t i1)
{
    mach3_al = (i1&0x1f);
}

extern int32_t vplce[4], vince[4], palookupoffse[4], bufplce[4];

#if HAVE_POWERPC
/* About 25% faster than the scalar version on my 12" Powerbook. --ryan. */
static void vlineasm4_altivec(int32_t i1, int32_t i2)
{
    uint32_t mach_array[4] = { (uint32_t) mach3_al,
                                   (uint32_t) mach3_al,
                                   (uint32_t) mach3_al,
                                   (uint32_t) mach3_al };

    uint32_t temp[4];
    uint32_t index = (i2 + ylookup[i1]);
    uint8_t  *dest = (uint8_t *)(-ylookup[i1]);

    uint32_t vec_temp;
    int32_t vec_vplce;
    int32_t vec_vince;
    int32_t vec_bufplce;
    uint32_t vec_shifter;

    uint8_t  *pal0 = (uint8_t  *) palookupoffse[0];
    uint8_t  *pal1 = (uint8_t  *) palookupoffse[1];
    uint8_t  *pal2 = (uint8_t  *) palookupoffse[2];
    uint8_t  *pal3 = (uint8_t  *) palookupoffse[3];

    vec_shifter = vec_ld(0, mach_array);
    vec_vplce = vec_ld(0, vplce);
    vec_vince = vec_ld(0, vince);
    vec_bufplce = vec_ld(0, bufplce);

    do {
        vec_temp = ( uint32_t) vec_sr(vec_vplce, vec_shifter);
        vec_temp = ( uint32_t) vec_add(vec_bufplce, (vector signed int) vec_temp);
        vec_st(vec_temp, 0x00, temp);
        vec_vplce = vec_add(vec_vplce, vec_vince);
	    dest[index] = pal0[*((uint8_t  *) temp[0])];
	    dest[index+1] = pal1[*((uint8_t  *) temp[1])];
	    dest[index+2] = pal2[*((uint8_t  *) temp[2])];
	    dest[index+3] = pal3[*((uint8_t  *) temp[3])];
        dest += fixchain;
    } while (((unsigned)dest - fixchain) < ((unsigned)dest));

    vec_st(vec_vplce, 0, vplce);
}
#endif


//FCS This is used to fill the inside of a wall
void vlineasm4(int32_t i1, int32_t i2)
{

	if (!RENDER_DRAW_WALL_INSIDE)
		return ;

#if HAVE_POWERPC
    if (has_altivec)
        vlineasm4_altivec(i1, i2);
    else
#endif
    {
        int i;
        uint32_t temp;
        uint32_t index = (i2 + ylookup[i1]);
        uint8_t  *dest = (uint8_t *)(-ylookup[i1]);
        do {
            for (i = 0; i < 4; i++)
            {
        	    temp = ((unsigned)vplce[i]) >> mach3_al;
        	    temp = (((uint8_t *)(bufplce[i]))[temp]);
        	    dest[index+i] = ((uint8_t *)(palookupoffse[i]))[temp];
	            vplce[i] += vince[i];
            }
            dest += fixchain;
        } while (((unsigned)dest - fixchain) < ((unsigned)dest));
    }
} /* vlineasm4 */


void setupmvlineasm(int32_t i1)
{
    machmv = (i1&0x1f);
} /* setupmvlineasm */


void mvlineasm4(int32_t i1, int32_t i2)
{
    int i;
    uint32_t temp;
    uint32_t index = (i2 + ylookup[i1]);
    uint8_t  *dest = (uint8_t *)(-ylookup[i1]);

    do {
        for (i = 0; i < 4; i++)
        {
	    temp = ((unsigned)vplce[i]) >> machmv;
	    temp = (((uint8_t *)(bufplce[i]))[temp]);
	    if (temp != 255)
		    dest[index+i] = ((uint8_t *)(palookupoffse[i]))[temp];
	    vplce[i] += vince[i];
        }
        dest += fixchain;
    } while (((unsigned)dest - fixchain) < ((unsigned)dest));
} /* mvlineasm4 */


static int32_t spal_eax;
static int32_t smach_eax;
static int32_t smach2_eax;
static int32_t smach5_eax;
static int32_t smach_ecx;
void setupspritevline(int32_t i1, int32_t i2, int32_t i3, int32_t i4, int32_t i5, int32_t i6)
{
    spal_eax = i1;
    smach_eax = (i5<<16);
    smach2_eax = (i5>>16)+i2;
    smach5_eax = smach2_eax + i4;
    smach_ecx = i3;
} 


void spritevline(int32_t i1, uint32_t i2, int32_t i3, uint32_t i4, int32_t i5, int32_t i6)
{
    uint8_t  *source = (uint8_t  *)i5;
    uint8_t  *dest = (uint8_t  *)i6;

setup:

    i2 += smach_eax;
    i1 = (i1&0xffffff00) | (*source&0xff);
    if ((i2 - smach_eax) > i2) source += smach2_eax + 1;
    else source += smach2_eax;

draw:
    i1 = (i1&0xffffff00) | (((uint8_t  *)spal_eax)[i1]&0xff);
    *dest = i1;
    dest += fixchain;

    i4 += smach_ecx;
    i4--;
    if (!((i4 - smach_ecx) > i4) && i4 != 0)
	    goto setup;
    if (i4 == 0) return;
    i2 += smach_eax;
    i1 = (i1&0xffffff00) | (*source&0xff);
    if ((i2 - smach_eax) > i2) source += smach5_eax + 1;
    else source += smach5_eax;
    goto draw;
} /* spritevline */


static int32_t mspal_eax;
static int32_t msmach_eax;
static int32_t msmach2_eax;
static int32_t msmach5_eax;
static int32_t msmach_ecx;
void msetupspritevline(int32_t i1, int32_t i2, int32_t i3, int32_t i4, int32_t i5, int32_t i6)
{
    mspal_eax = i1;
    msmach_eax = (i5<<16);
    msmach2_eax = (i5>>16)+i2;
    msmach5_eax = smach2_eax + i4;
    msmach_ecx = i3;
} 


void mspritevline(int32_t i1, int32_t i2, int32_t i3, int32_t i4, int32_t i5, int32_t i6)
{
    uint8_t  *source = (uint8_t  *)i5;
    uint8_t  *dest = (uint8_t  *)i6;

setup:
    i2 += smach_eax;
    i1 = (i1&0xffffff00) | (*source&0xff);
    if ((i2 - smach_eax) > i2) source += smach2_eax + 1;
    else source += smach2_eax;

	draw:
    if ((i1&0xff) != 255)
    {
	    i1 = (i1&0xffffff00) | (((uint8_t  *)spal_eax)[i1]&0xff);
	    *dest = i1;
    }
    dest += fixchain;

    i4 += smach_ecx;
    i4--;
    if (!((i4 - smach_ecx) > i4) && i4 != 0)
	    goto setup;
    if (i4 == 0) return;
    i2 += smach_eax;
    i1 = (i1&0xffffff00) | (*source&0xff);
    if ((i2 - smach_eax) > i2) source += smach5_eax + 1;
    else source += smach5_eax;
    goto draw;
}


uint32_t tspal;
uint32_t tsmach_eax1;
uint32_t tsmach_eax2;
uint32_t tsmach_eax3;
uint32_t tsmach_ecx;
void tsetupspritevline(int32_t i1, int32_t i2, int32_t i3, int32_t i4, int32_t i5, int32_t i6)
{
	tspal = i1;
	tsmach_eax1 = i5 << 16;
	tsmach_eax2 = (i5 >> 16) + i2;
	tsmach_eax3 = tsmach_eax2 + i4;
	tsmach_ecx = i3;
} 


void tspritevline(int32_t i1, int32_t i2, int32_t numPixels, uint32_t i4, int32_t i5, int32_t i6)
{
	while (numPixels)
	{
		numPixels--;
		if (numPixels != 0)
		{
			uint32_t adder = tsmach_eax2;
			i4 += tsmach_ecx;
			if (i4 < (i4 - tsmach_ecx)) adder = tsmach_eax3;
			i1 = *((uint8_t  *)i5);
			i2 += tsmach_eax1;
			if (i2 < (i2 - tsmach_eax1)) i5++;
			i5 += adder;
			// tstartsvline
			if (i1 != 0xff)
			{
				unsigned short val;
				val = ((uint8_t *)tspal)[i1];
				val |= ((*((uint8_t  *)i6))<<8);
				if (transrev) val = ((val>>8)|(val<<8));
				i1 = ((uint8_t  *)tmach)[val];
				*((uint8_t  *)i6) = (i1&0xff);
			}
			i6 += fixchain;
		}
	}
} 


static int32_t mmach_eax;
static int32_t mmach_asm3;
static int32_t mmach_asm1;
static int32_t mmach_asm2;
void mhlineskipmodify(int32_t i1, uint32_t i2, uint32_t i3, int32_t i4, int32_t i5, int32_t i6);
void mhline(int32_t i1, int32_t i2, int32_t i3, int32_t i4, int32_t i5, int32_t i6)
{
    mmach_eax = i1;
    mmach_asm3 = asm3;
    mmach_asm1 = asm1;
    mmach_asm2 = asm2;
    mhlineskipmodify(asm2,i2,i3,i4,i5,i6);
}


static uint8_t  mshift_al = 26;
static uint8_t  mshift_bl = 6;
void mhlineskipmodify(int32_t i1, uint32_t i2, uint32_t i3, int32_t i4, int32_t i5, int32_t i6)
{
    uint32_t ebx;
    int counter = (i3>>16);
    while (counter >= 0)
    {
	    ebx = i2 >> mshift_al;
	    ebx = shld (ebx, (unsigned)i5, mshift_bl);
	    i1 = ((uint8_t  *)mmach_eax)[ebx];
	    if ((i1&0xff) != 0xff)
		    *((uint8_t  *)i6) = (((uint8_t *)mmach_asm3)[i1]);

	    i2 += mmach_asm1;
	    i5 += mmach_asm2;
	    i6++;
	    counter--;
    }
}


void msethlineshift(int32_t i1, int32_t i2)
{
    i1 = 256-i1;
    mshift_al = (i1&0x1f);
    mshift_bl = (i2&0x1f);
} /* msethlineshift */


static int32_t tmach_eax;
static int32_t tmach_asm3;
static int32_t tmach_asm1;
static int32_t tmach_asm2;
void thlineskipmodify(int32_t i1, uint32_t i2, uint32_t i3, int32_t i4, int32_t i5, int32_t i6);
void thline(int32_t i1, int32_t i2, int32_t i3, int32_t i4, int32_t i5, int32_t i6)
{
    tmach_eax = i1;
    tmach_asm3 = asm3;
    tmach_asm1 = asm1;
    tmach_asm2 = asm2;
    thlineskipmodify(asm2,i2,i3,i4,i5,i6);
}

static uint8_t  tshift_al = 26;
static uint8_t  tshift_bl = 6;
void thlineskipmodify(int32_t i1, uint32_t i2, uint32_t i3, int32_t i4, int32_t i5, int32_t i6)
{
    uint32_t ebx;
    int counter = (i3>>16);
    while (counter >= 0)
    {
	    ebx = i2 >> tshift_al;
	    ebx = shld (ebx, (unsigned)i5, tshift_bl);
	    i1 = ((uint8_t  *)tmach_eax)[ebx];
	    if ((i1&0xff) != 0xff)
	    {
		    unsigned short val = (((uint8_t *)tmach_asm3)[i1]);
		    val |= (*((uint8_t  *)i6)<<8);
		    if (transrev) val = ((val>>8)|(val<<8));
		    *((uint8_t  *)i6) = (((uint8_t *)tmach)[val]);
	    }

	    i2 += tmach_asm1;
	    i5 += tmach_asm2;
	    i6++;
	    counter--;
    }
} 


void tsethlineshift(int32_t i1, int32_t i2)
{
    i1 = 256-i1;
    tshift_al = (i1&0x1f);
    tshift_bl = (i2&0x1f);
}


static int32_t slopemach_ebx;
static int32_t slopemach_ecx;
static int32_t slopemach_edx;
static uint8_t  slopemach_ah1;
static uint8_t  slopemach_ah2;
static float asm2_f;
typedef union { unsigned int i; float f; } bitwisef2i;
void setupslopevlin(int32_t i1, int32_t i2, int32_t i3)
{
    bitwisef2i c;
    slopemach_ebx = i2;
    slopemach_ecx = i3;
    slopemach_edx = (1<<(i1&0x1f)) - 1;
    slopemach_edx <<= ((i1&0x1f00)>>8);
    slopemach_ah1 = 32-((i1&0x1f00)>>8);
    slopemach_ah2 = (slopemach_ah1 - (i1&0x1f)) & 0x1f;
    c.f = asm2_f = (float)asm1;
    asm2 = c.i;
}

extern int32_t reciptable[2048];
extern int32_t globalx3, globaly3;
extern int32_t fpuasm;
#define low32(a) ((a&0xffffffff))
#define high32(a) ((int)(((__int64)a&(__int64)0xffffffff00000000)>>32))

/* #pragma aux slopevlin parm [eax][ebx][ecx][edx][esi][edi] */
//FCS: Render RENDER_SLOPPED_CEILING_AND_FLOOR
void slopevlin(int32_t i1, uint32_t i2, int32_t i3, int32_t i4, int32_t i5, int32_t i6)
{
    bitwisef2i c;
    uint32_t ecx,eax,ebx,edx,esi,edi;
    float a = (float) asm3 + asm2_f;
    i1 -= slopemach_ecx;
    esi = i5 + low32((__int64)globalx3 * (__int64)(i2<<3));
    edi = i6 + low32((__int64)globaly3 * (__int64)(i2<<3));
    ebx = i4;

	if (!RENDER_SLOPPED_CEILING_AND_FLOOR)
		return;

    do {
	    // -------------
	    // All this is calculating a fixed point approx. of 1/a
	    c.f = a;
	    fpuasm = eax = c.i;
	    edx = (((int32_t)eax) < 0) ? 0xffffffff : 0;
	    eax = eax << 1;
	    ecx = (eax>>24);	//  exponent
	    eax = ((eax&0xffe000)>>11);
	    ecx = ((ecx&0xffffff00)|((ecx-2)&0xff));
	    eax = reciptable[eax/4];
	    eax >>= (ecx&0x1f);
	    eax ^= edx;
	    // -------------
	    edx = i2;
	    i2 = eax;
	    eax -= edx;
	    ecx = low32((__int64)globalx3 * (__int64)eax);
	    eax = low32((__int64)globaly3 * (__int64)eax);
	    a += asm2_f;

	    asm4 = ebx;
	    ecx = ((ecx&0xffffff00)|(ebx&0xff));
	    if (ebx >= 8) ecx = ((ecx&0xffffff00)|8);

	    ebx = esi;
	    edx = edi;
	    while ((ecx&0xff))
	    {
		    ebx >>= slopemach_ah2;
		    esi += ecx;
		    edx >>= slopemach_ah1;
		    ebx &= slopemach_edx;
		    edi += eax;
		    i1 += slopemach_ecx;
		    edx = ((edx&0xffffff00)|((((uint8_t  *)(ebx+edx))[slopemach_ebx])));
		    ebx = *((uint32_t*)i3); // register trickery
		    i3 -= 4;
		    eax = ((eax&0xffffff00)|(*((uint8_t  *)(ebx+edx))));
		    ebx = esi;
		    *((uint8_t  *)i1) = (eax&0xff);
		    edx = edi;
		    ecx = ((ecx&0xffffff00)|((ecx-1)&0xff));
	    }
	    ebx = asm4;
	    ebx -= 8;	// BITSOFPRECISIONPOW
    } while ((int32_t)ebx > 0);
} /* slopevlin */


void settransnormal(void)
{
	transrev = 0;
} 


void settransreverse(void)
{
	transrev = 1;
} 

