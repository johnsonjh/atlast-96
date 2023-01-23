/*
 * vim: filetype=c:tabstop=2:ai:expandtab
 * SPDX-License-Identifier: CC-PDDC
 * SPDX-FileCopyrightText: Public domain
 *
 * A T L A S T
 * Autodesk Threaded Language Application System Toolkit
 *
 * Program Linkage Definitions
 *
 * Designed and implemented in January of 1990 by John Walker
 */

/*
 * This module contains the definitions needed by programs that invoke the
 * ATLAST system.  It also contains the definitions used internally within
 * ATLAST (which might create conflicts if included in calling programs).
 */

#define ATLAST_VERSION  "20230124-next"

#ifdef ATLAST_64BIT
# include <stdint.h>
  typedef int64_t atl_int;  /* 64-bit stack integer type */
#else
  typedef long atl_int;     /* 32-bit stack integer type */
#endif /* ifdef ATLAST_64BIT */

typedef double atl_real;    /* Real number type */

/*
 * External symbols accessible by the calling program.
 */

extern atl_int  atl_stklen;    /* Init / current stack length        */
extern atl_int  atl_rstklen;   /* Init / current return stack length */
extern atl_int  atl_heaplen;   /* Init / current heap length         */
extern atl_int  atl_ltempstr;  /* Temporary string buffer length     */
extern atl_int  atl_ntempstr;  /* Number of temporary string buffers */
extern atl_int  atl_trace;     /* Trace mode                         */
extern atl_int  atl_walkback;  /* Error walkback enabled mode        */
extern atl_int  atl_comment;   /* Currently ignoring comment         */
extern atl_int  atl_redef;     /* Allow redefining words without     */
                               /*   issuing the "not unique" warning */
extern atl_int  atl_errline;   /* Line number of the last atl_load() */
                               /*   error, or zero (if no error)     */

/*
 * ATL_EVAL return status codes
 */

#define ATL_SNORM           0  /* Normal evaluation                  */
#define ATL_STACKOVER      -1  /* Stack overflow                     */
#define ATL_STACKUNDER     -2  /* Stack underflow                    */
#define ATL_RSTACKOVER     -3  /* Return stack overflow              */
#define ATL_RSTACKUNDER    -4  /* Return stack underflow             */
#define ATL_HEAPOVER       -5  /* Heap overflow                      */
#define ATL_BADPOINTER     -6  /* Pointer outside the heap           */
#define ATL_UNDEFINED      -7  /* Undefined word                     */
#define ATL_FORGETPROT     -8  /* Attempt to forget protected word   */
#define ATL_NOTINDEF       -9  /* Compiler word outside definition   */
#define ATL_RUNSTRING     -10  /* Non-terminated string              */
#define ATL_RUNCOMM       -11  /* Non-terminated comment in file     */
#define ATL_BREAK         -12  /* Asynchronous break signal received */
#define ATL_DIVZERO       -13  /* Attempt to divide by zero          */
#define ATL_APPLICATION   -14  /* Application primitive atl_error()  */

/*
 * Entry points
 */

extern void atl_init(), atl_mark(), atl_unwind(), atl_break();
extern int  atl_eval(), atl_load();
extern void atl_memstat();
