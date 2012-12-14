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

int32_t mmxoverlay(void);
int32_t sethlinesizes(int32_t,int32_t,int32_t);
int32_t setpalookupaddress(uint8_t  *);
int32_t setuphlineasm4(int32_t,int32_t);
int32_t hlineasm4(int32_t,int32_t,int32_t,int32_t,int32_t,int32_t);
int32_t setuprhlineasm4(int32_t,int32_t,int32_t,int32_t,int32_t,int32_t);
int32_t rhlineasm4(int32_t,int32_t,int32_t,int32_t,int32_t,int32_t);
int32_t setuprmhlineasm4(int32_t,int32_t,int32_t,int32_t,int32_t,int32_t);
int32_t rmhlineasm4(int32_t,int32_t,int32_t,int32_t,int32_t,int32_t);
int32_t setupqrhlineasm4(int32_t,int32_t,int32_t,int32_t,int32_t,int32_t);
int32_t qrhlineasm4(int32_t,int32_t,int32_t,int32_t,int32_t,int32_t);
int32_t setvlinebpl(int32_t);
int32_t fixtransluscence(int32_t);
int32_t prevlineasm1(int32_t,int32_t,int32_t,int32_t,int32_t,int32_t);
int32_t vlineasm1(int32_t,int32_t,int32_t,int32_t,int32_t,int32_t);
int32_t setuptvlineasm(int32_t);
int32_t tvlineasm1(int32_t,int32_t,int32_t,int32_t,int32_t,int32_t);
int32_t setuptvlineasm2(int32_t,int32_t,int32_t);
int32_t tvlineasm2(int32_t,int32_t,int32_t,int32_t,int32_t,int32_t);
int32_t mvlineasm1(int32_t,int32_t,int32_t,int32_t,int32_t,int32_t);
int32_t setupvlineasm(int32_t);
int32_t vlineasm4(int32_t,int32_t);
int32_t setupmvlineasm(int32_t);
int32_t mvlineasm4(int32_t,int32_t);
void setupspritevline(int32_t,int32_t,int32_t,int32_t,int32_t,int32_t);
void spritevline(int32_t,int32_t,int32_t,int32_t,int32_t,int32_t);
void msetupspritevline(int32_t,int32_t,int32_t,int32_t,int32_t,int32_t);
void mspritevline(int32_t,int32_t,int32_t,int32_t,int32_t,int32_t);
void tsetupspritevline(int32_t,int32_t,int32_t,int32_t,int32_t,int32_t);
void tspritevline(int32_t,int32_t,int32_t,int32_t,int32_t,int32_t);
int32_t mhline(int32_t,int32_t,int32_t,int32_t,int32_t,int32_t);
int32_t mhlineskipmodify(int32_t,int32_t,int32_t,int32_t,int32_t,int32_t);
int32_t msethlineshift(int32_t,int32_t);
int32_t thline(int32_t,int32_t,int32_t,int32_t,int32_t,int32_t);
int32_t thlineskipmodify(int32_t,int32_t,int32_t,int32_t,int32_t,int32_t);
int32_t tsethlineshift(int32_t,int32_t);
int32_t setupslopevlin(int32_t,int32_t,int32_t);
int32_t slopevlin(int32_t,int32_t,int32_t,int32_t,int32_t,int32_t);
int32_t settransnormal(void);
int32_t settransreverse(void);
int32_t setupdrawslab(int32_t,int32_t);
int32_t drawslab(int32_t,int32_t,int32_t,int32_t,int32_t,int32_t);
int32_t stretchhline(int32_t,int32_t,int32_t,int32_t,int32_t,int32_t);
int32_t is_vmware_running(void);

    
#ifdef __cplusplus
}
#endif

#endif /* include-once-blocker. */

/* end of a.h ... */


