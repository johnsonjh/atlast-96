# ATLAST 96
# SPDX-License-Identifier: CC-PDDC
# SPDX-FileCopyrightText: Public domain
###############################################################################

ifndef 64BIT
  ifdef 32BIT
    ATLAST_32BIT := 1
  endif
endif

###############################################################################

ifndef ATLAST_32BIT
  ATLAST_64BIT := 1
endif

###############################################################################

ifdef ATLAST_64BIT
  64CFLAGS := -DATLAST_64BIT
endif

###############################################################################

ifdef ATLAST_64BIT
  COPTIONS := -m64
else
  COPTIONS := -m32
endif

###############################################################################

CC         ?= gcc
SHELL       = /bin/sh
MAKE       ?= make

###############################################################################

LIBRARIES   = -lm
INCLUDE     = -I.

###############################################################################

OPTFLAGS   ?= -O3 -flto

###############################################################################

ATLCONFIG   = -DMEMSTAT
ATLCONFIG  += -DEXPORT
ATLCONFIG  += -DREADONLYSTRINGS
ATLCONFIG  += -DALIGNMENT
#ATLCONFIG += -DANSIFLOAT

###############################################################################

CFLAGS  += $(OPTFLAGS) $(COMFLAGS) $(COPTIONS) \
	   $(INCLUDE) $(ATLCONFIG) $(64CFLAGS)

###############################################################################

APPS = atlast primdeftest

###############################################################################

.PHONY: all
.NOTPARALLEL: all
all:
ifdef ATLAST_64BIT
	+@test -x ./atlast &&   \
	  ./atlast -U 2>&1 |    \
	  grep -q '64-bit' || { \
	  printf '\n%s\n'       \
	  	"  **** Cleaning 32-bit ATLAST ****" 2> /dev/null; \
	  $(MAKE) -s --no-print-directory clean ||                 \
	  true; }
	-@printf '%s\n' ""
	-@printf '%s'                                    \
		"  **** Building 64-bit ATLAST"          \
		" (\"$(MAKE) 32BIT=1\" for 32-bit) ****" \
		2> /dev/null
	-@printf '\n\n' ""
	+@$(MAKE) $(APPS) || {                                         \
	  printf '\n%s\n\n'                                            \
	  	"  **** 64-bit build FAILED!!! ****" 2> /dev/null &&   \
	  printf '%s\n\n'                                              \
	  	"  >>>> Try \"$(MAKE) 32BIT=1\" ?? <<<<" 2> /dev/null; \
	  exit 1; }; true
	-@printf '\n%s\n\n' "  **** 64-bit build complete! ****" 2> /dev/null
  ifneq (all,$(findstring all,$(MAKECMDGOALS)))
	-@printf '%s\n\n'   "  >>>> You may run \"$(MAKE) test\" now <<<<" \
		2> /dev/null
  endif
else
	+@test -x ./atlast &&   \
	  ./atlast -U 2>&1 |    \
	  grep -q '32-bit' || { \
	  printf '\n%s\n'       \
	  	"  **** Cleaning 64-bit ATLAST ****" 2> /dev/null; \
	  $(MAKE) -s --no-print-directory clean ||                 \
	  true; }
	-@printf '\n%s\n\n'                          \
		"  **** Building 32-bit ATLAST ****" \
		2> /dev/null
	+@$(MAKE) $(APPS) || {                                         \
	  printf '\n%s\n\n'                                            \
	  	"  **** 32-bit build FAILED!!! ****" 2> /dev/null &&   \
	  printf '%s\n\n'                                              \
	  	"  >>>> Try \"$(MAKE) 64BIT=1\" ?? <<<<" 2> /dev/null; \
	  exit 1; }; true
	-@printf '\n%s\n\n' "  **** 32-bit build complete! ****" 2> /dev/null
  ifneq (all,$(findstring all,$(MAKECMDGOALS)))
	-@printf '%s\n\n'                                              \
		"  **** You may run \"$(MAKE) test 32BIT=1\" now ****" \
		2> /dev/null
  endif
endif

###############################################################################

.NOTPARALLEL: atlast
atlast: atlmain.c atlast.c atldef.h atlast.h
ifdef ATLAST_64BIT
	-@printf '\n%s\n\n' "  **** Linking 64-bit ATLAST ****" 2> /dev/null
else
	-@printf '\n%s\n\n' "  **** Linking 32-bit ATLAST ****" 2> /dev/null
endif
	$(CC) $(CFLAGS) \
		atlmain.c atlast.c -o atlast $(LIBRARIES)

###############################################################################

.NOTPARALLEL: primdeftest
primdeftest: primdeftest.c atlast.c atldef.h atlast.h
	$(CC) $(CFLAGS) \
		primdeftest.c atlast.c -o primdeftest $(LIBRARIES)

###############################################################################

.PHONY: test check dotest docheck
.NOTPARALLEL: test check dotest docheck
test check dotest docheck:
ifdef ATLAST_64BIT
	+@test -x ./atlast && ./atlast -U 2>&1 |                       \
	  grep -q '64-bit' || $(MAKE) -s --no-print-directory clean || \
	  true
	+@$(MAKE) --no-print-directory all && \
	  ./atlast -U 2>&1 | grep -q '64-bit'
	-@printf '%s\n\n'   "  **** Testing 64-bit ATLAST ****"
	+@$(MAKE) --no-print-directory check64 && {                           \
	  printf '\n%s\n\n' "  **** 64-bit testing PASSED ****" 2> /dev/null; \
	  exit 0; }; exit 1
else
	+@test -x ./atlast && ./atlast -U 2>&1 |                       \
	  grep -q '32-bit' || $(MAKE) -s --no-print-directory clean || \
	  true
	+@$(MAKE) --no-print-directory all && \
	  ./atlast -U 2>&1 | grep -q '32-bit'
	-@printf '%s\n\n'   "  **** Testing 32-bit ATLAST ****"
	+@$(MAKE) --no-print-directory check32 && {                           \
	  printf '\n%s\n\n' "  **** 32-bit testing PASSED ****" 2> /dev/null; \
	  exit 0; }; exit 1
endif

###############################################################################

.PHONY: check32
.NOTPARALLEL: check32
check32: $(APPS)
	-@rm -f /tmp/regout.tmp
	-@rm -f /tmp/regin.tmp
	@echo testcons > /tmp/regin.tmp
	@echo Test 1234 >> /tmp/regin.tmp
	@echo ls atlast.c >> /tmp/regin.tmp
	@echo >> /tmp/regin.tmp
	@echo >> /tmp/regin.tmp
	@./atlast -iregress32.atl < /tmp/regin.tmp > /tmp/regout.tmp
	-@dos2unix -f /tmp/regout.tmp 2> /dev/null || {                   \
		echo "WARNING: dos2unix failed to execute." 2> /dev/null; \
		true; }
	@diff -U0 regout32.txt /tmp/regout.tmp
	@rm -f /tmp/regout.tmp
	@rm -f /tmp/regin.tmp

###############################################################################

.PHONY: check64
.NOTPARALLEL: check64
check64: $(APPS)
	-@rm -f /tmp/regout.tmp
	-@rm -f /tmp/regin.tmp
	@echo testcons > /tmp/regin.tmp
	@echo Test 1234 >> /tmp/regin.tmp
	@echo ls atlast.c >> /tmp/regin.tmp
	@echo >> /tmp/regin.tmp
	@echo >> /tmp/regin.tmp
	@./atlast -iregress64.atl < /tmp/regin.tmp > /tmp/regout.tmp
	-@dos2unix -f /tmp/regout.tmp 2> /dev/null || {                   \
		echo "WARNING: dos2unix failed to execute." 2> /dev/null; \
		true; }
	@diff -U0 regout64.txt /tmp/regout.tmp
	@rm -f /tmp/regout.tmp
	@rm -f /tmp/regin.tmp

###############################################################################

.PHONY: time bench benchmark
.NOTPARALLEL: time bench benchmark
time bench benchmark: $(APPS)
	+@test -x ./atlast &&                                  \
	  ./atlast -U 2>&1 |                                   \
	  grep -q '64-bit' || {                                \
	  printf '\n%s\n\n'                                    \
	  	"  **** ERROR: 64-bit ATLAST is required ****" \
		2> /dev/null;                                  \
	  exit 1; }
	-@printf '\n%s\n\n'                                    \
		"  **** Benchmarking 20000000 iterations ****" \
		2> /dev/null
	+@time sh -c "printf '%s\n'        \
			'20000000 niter !' \
			'cbenchmark'       \
			'sbenchmark' |     \
		./atlast -isqrt.atl"       \
	  > /dev/null

###############################################################################

.PHONY: distclean
.NOTPARALLEL: distclean
distclean: clean
	-rm -f atlast32 atlast64

###############################################################################

.PHONY: clean
.NOTPARALLEL: clean
clean:
	-rm -f $(APPS)
	-rm -f *.bak *.o *.dvi *.aux *.log
	-rm -f core core.* cscope.out

###############################################################################
