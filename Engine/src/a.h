/*
 * "Build Engine & Tools" Copyright (c) 1993-1997 Ken Silverman
 * Ken Silverman's official web site: "http://www.advsys.net/ken"
 * See the included license file "BUILDLIC.TXT" for license info.
 * This file IS NOT A PART OF Ken Silverman's original release
 */

#ifndef _INCLUDE_A_H_
#define _INCLUDE_A_H_

#if (defined __WATCOMC__)
#error Do not include this header with Watcom C.
#endif

#ifdef __cplusplus
extern "C" {
#endif

long mmxoverlay(void);
long sethlinesizes(long,long,long);
long setpalookupaddress(char *);
long setuphlineasm4(long,long);
long hlineasm4(long,long,long,long,long,long);
long setuprhlineasm4(long,long,long,long,long,long);
long rhlineasm4(long,long,long,long,long,long);
long setuprmhlineasm4(long,long,long,long,long,long);
long rmhlineasm4(long,long,long,long,long,long);
long setupqrhlineasm4(long,long,long,long,long,long);
long qrhlineasm4(long,long,long,long,long,long);
long setvlinebpl(long);
long fixtransluscence(long);
long prevlineasm1(long,long,long,long,long,long);
long vlineasm1(long,long,long,long,long,long);
long setuptvlineasm(long);
long tvlineasm1(long,long,long,long,long,long);
long setuptvlineasm2(long,long,long);
long tvlineasm2(long,long,long,long,long,long);
long mvlineasm1(long,long,long,long,long,long);
long setupvlineasm(long);
long vlineasm4(long,long);
long setupmvlineasm(long);
long mvlineasm4(long,long);
void setupspritevline(long,long,long,long,long,long);
void spritevline(long,long,long,long,long,long);
void msetupspritevline(long,long,long,long,long,long);
void mspritevline(long,long,long,long,long,long);
void tsetupspritevline(long,long,long,long,long,long);
void tspritevline(long,long,long,long,long,long);
long mhline(long,long,long,long,long,long);
long mhlineskipmodify(long,long,long,long,long,long);
long msethlineshift(long,long);
long thline(long,long,long,long,long,long);
long thlineskipmodify(long,long,long,long,long,long);
long tsethlineshift(long,long);
long setupslopevlin(long,long,long);
long slopevlin(long,long,long,long,long,long);
long settransnormal(void);
long settransreverse(void);
long setupdrawslab(long,long);
long drawslab(long,long,long,long,long,long);
long stretchhline(long,long,long,long,long,long);
long is_vmware_running(void);

    /* !!! This part might be better stated as "USE_ASM".  --ryan. */
#ifdef USE_I386_ASM
  long asm_mmxoverlay(void);
  long asm_sethlinesizes(long,long,long);
  long asm_setpalookupaddress(char *);
  long asm_setuphlineasm4(long,long);
  long asm_hlineasm4(long,long,long,long,long,long);
  long asm_setuprhlineasm4(long,long,long,long,long,long);
  long asm_rhlineasm4(long,long,long,long,long,long);
  long asm_setuprmhlineasm4(long,long,long,long,long,long);
  long asm_rmhlineasm4(long,long,long,long,long,long);
  long asm_setupqrhlineasm4(long,long,long,long,long,long);
  long asm_qrhlineasm4(long,long,long,long,long,long);
  long asm_setvlinebpl(long);
  long asm_fixtransluscence(long);
  long asm_prevlineasm1(long,long,long,long,long,long);
  long asm_vlineasm1(long,long,long,long,long,long);
  long asm_setuptvlineasm(long);
  long asm_tvlineasm1(long,long,long,long,long,long);
  long asm_setuptvlineasm2(long,long,long);
  long asm_tvlineasm2(long,long,long,long,long,long);
  long asm_mvlineasm1(long,long,long,long,long,long);
  long asm_setupvlineasm(long);
  long asm_vlineasm4(long,long);
  long asm_setupmvlineasm(long);
  long asm_mvlineasm4(long,long);
  void asm_setupspritevline(long,long,long,long,long,long);
  void asm_spritevline(long,long,long,long,long,long);
  void asm_msetupspritevline(long,long,long,long,long,long);
  void asm_mspritevline(long,long,long,long,long,long);
  void asm_tsetupspritevline(long,long,long,long,long,long);
  void asm_tspritevline(long,long,long,long,long,long);
  long asm_mhline(long,long,long,long,long,long);
  long asm_mhlineskipmodify(long,long,long,long,long,long);
  long asm_msethlineshift(long,long);
  long asm_thline(long,long,long,long,long,long);
  long asm_thlineskipmodify(long,long,long,long,long,long);
  long asm_tsethlineshift(long,long);
  long asm_setupslopevlin(long,long,long);
  long asm_slopevlin(long,long,long,long,long,long);
  long asm_settransnormal(void);
  long asm_settransreverse(void);
  long asm_setupdrawslab(long,long);
  long asm_drawslab(long,long,long,long,long,long);
  long asm_stretchhline(long,long,long,long,long,long);
  long asm_isvmwarerunning(void);

  /*
   * !!! I need a reference to this, for mprotect(), but the actual function
   * !!!  is never called in BUILD...just from other ASM routines. --ryan.
   */
  long asm_prohlineasm4(void);

  #if ((defined __GNUC__) && (!defined C_IDENTIFIERS_UNDERSCORED))

    long asm_mmxoverlay(void) __attribute__ ((alias ("_asm_mmxoverlay")));
    long asm_sethlinesizes(long,long,long) __attribute__ ((alias ("_asm_sethlinesizes")));
    long asm_setpalookupaddress(char *) __attribute__ ((alias ("_asm_setpalookupaddress")));
    long asm_setuphlineasm4(long,long) __attribute__ ((alias ("_asm_setuphlineasm4")));
    long asm_hlineasm4(long,long,long,long,long,long) __attribute__ ((alias ("_asm_hlineasm4")));
    long asm_setuprhlineasm4(long,long,long,long,long,long) __attribute__ ((alias ("_asm_setuprhlineasm4")));
    long asm_rhlineasm4(long,long,long,long,long,long) __attribute__ ((alias ("_asm_rhlineasm4")));
    long asm_setuprmhlineasm4(long,long,long,long,long,long) __attribute__ ((alias ("_asm_setuprmhlineasm4")));
    long asm_rmhlineasm4(long,long,long,long,long,long) __attribute__ ((alias ("_asm_rmhlineasm4")));
    long asm_setupqrhlineasm4(long,long,long,long,long,long) __attribute__ ((alias ("_asm_setupqrhlineasm4")));
    long asm_qrhlineasm4(long,long,long,long,long,long) __attribute__ ((alias ("_asm_qrhlineasm4")));
    long asm_setvlinebpl(long) __attribute__ ((alias ("_asm_setvlinebpl")));
    long asm_fixtransluscence(long) __attribute__ ((alias ("_asm_fixtransluscence")));
    long asm_prevlineasm1(long,long,long,long,long,long) __attribute__ ((alias ("_asm_prevlineasm1")));
    long asm_vlineasm1(long,long,long,long,long,long) __attribute__ ((alias ("_asm_vlineasm1")));
    long asm_setuptvlineasm(long) __attribute__ ((alias ("_asm_setuptvlineasm")));
    long asm_tvlineasm1(long,long,long,long,long,long) __attribute__ ((alias ("_asm_tvlineasm1")));
    long asm_setuptvlineasm2(long,long,long) __attribute__ ((alias ("_asm_setuptvlineasm2")));
    long asm_tvlineasm2(long,long,long,long,long,long) __attribute__ ((alias ("_asm_tvlineasm2")));
    long asm_mvlineasm1(long,long,long,long,long,long) __attribute__ ((alias ("_asm_mvlineasm1")));
    long asm_setupvlineasm(long) __attribute__ ((alias ("_asm_setupvlineasm")));
    long asm_vlineasm4(long,long) __attribute__ ((alias ("_asm_vlineasm4")));
    long asm_setupmvlineasm(long) __attribute__ ((alias ("_asm_setupmvlineasm")));
    long asm_mvlineasm4(long,long) __attribute__ ((alias ("_asm_mvlineasm4")));
    void asm_setupspritevline(long,long,long,long,long,long) __attribute__ ((alias ("_asm_setupspritevline")));
    void asm_spritevline(long,long,long,long,long,long) __attribute__ ((alias ("_asm_spritevline")));
    void asm_msetupspritevline(long,long,long,long,long,long) __attribute__ ((alias ("_asm_msetupspritevline")));
    void asm_mspritevline(long,long,long,long,long,long) __attribute__ ((alias ("_asm_mspritevline")));
    void asm_tsetupspritevline(long,long,long,long,long,long) __attribute__ ((alias ("_asm_tsetupspritevline")));
    void asm_tspritevline(long,long,long,long,long,long) __attribute__ ((alias ("_asm_tspritevline")));
    long asm_mhline(long,long,long,long,long,long) __attribute__ ((alias ("_asm_mhline")));
    long asm_mhlineskipmodify(long,long,long,long,long,long) __attribute__ ((alias ("_asm_mhlineskipmodify")));
    long asm_msethlineshift(long,long) __attribute__ ((alias ("_asm_msethlineshift")));
    long asm_thline(long,long,long,long,long,long) __attribute__ ((alias ("_asm_thline")));
    long asm_thlineskipmodify(long,long,long,long,long,long) __attribute__ ((alias ("_asm_thlineskipmodify")));
    long asm_tsethlineshift(long,long) __attribute__ ((alias ("_asm_tsethlineshift")));
    long asm_setupslopevlin(long,long,long) __attribute__ ((alias ("_asm_setupslopevlin")));
    long asm_slopevlin(long,long,long,long,long,long) __attribute__ ((alias ("_asm_slopevlin")));
    long asm_settransnormal(void) __attribute__ ((alias ("_asm_settransnormal")));
    long asm_settransreverse(void) __attribute__ ((alias ("_asm_settransreverse")));
    long asm_setupdrawslab(long,long) __attribute__ ((alias ("_asm_setupdrawslab")));
    long asm_drawslab(long,long,long,long,long,long) __attribute__ ((alias ("_asm_drawslab")));
    long asm_stretchhline(long,long,long,long,long,long) __attribute__ ((alias ("_asm_stretchhline")));
    long asm_isvmwarerunning(void) __attribute__ ((alias ("_asm_isvmwarerunning")));

    /*
	 * !!! I need a reference to this, for mprotect(), but the actual function
     * !!!  is never called in BUILD...just from other ASM routines. --ryan.
	 */
    long asm_prohlineasm4(void) __attribute__ ((alias ("_asm_prohlineasm4")));

  #endif /* ELF/GCC */
#endif /* defined USE_I386_ASM */

#ifdef __cplusplus
}
#endif

#endif /* include-once-blocker. */

/* end of a.h ... */


