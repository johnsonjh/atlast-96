/*
 * vim: filetype=c:tabstop=2:ai:expandtab
 * SPDX-License-Identifier: CC-PDDC
 * SPDX-FileCopyrightText: Public domain
 *
 * A T L A S T
 * PRIMDEFTEST
 *
 * Test primitive definition in ATLAST
 *
 * Designed and implemented in January of 1990 by John Walker
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#include "atldef.h"

prim
ptime()
{
  So(1);
  Push = time(NULL);
}

prim
phhmmss()
{
  struct tm *lt;

  Sl(1);
  So(2);
  lt    = localtime(&S0);
  S0    = lt->tm_hour;
  Push  = lt->tm_min;
  Push  = lt->tm_sec;
}

prim
pleibniz()
{
  long    nterms;
  double   sum = 0.0;
  double numer = 1.0;
  double denom = 1.0;

  Sl(1);
  nterms = S0;
  Pop;

  So(Realsize);
  Push = 0;
  while (nterms-- > 0)
    {
      sum    += numer / denom;
      numer   = -numer;
      denom  += 2.0;
    }
  SREAL0(sum * 4.0);
}

static struct primfcn timep[] = { { "0TIME",    ptime      },
                                  { "0HHMMSS",  phhmmss    },
                                  { "0LEIBNIZ", pleibniz   },
                                  { NULL,       (codeptr)0 } };

int
main()
{
  char t[132];

  atl_init();
  atl_primdef(timep);
  while (fprintf(stdout, "-> "), fgets(t, 132, stdin) != NULL) /* //-V639 */
    {
      atl_eval(t);
    }
  return 0;
}
