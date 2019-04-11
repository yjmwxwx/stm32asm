

################## FXT makefile ##########################

PROJ=fxt


include flags.mk

#### choose the FLAG combo here:
FXT_CXXFLAGS  = -pipe -fno-exceptions
#FXT_CXXFLAGS  = -std=c++11
FXT_CXXFLAGS += $(OFLAGS) # uncomment for OPTIMIZATION
#FXT_CXXFLAGS += -O3 # test -O3
#FXT_CXXFLAGS += $(GFLAGS) # uncomment for DEBUGGING
#FXT_CXXFLAGS += $(PFLAGS) # uncomment for PROFILING
FXT_CXXFLAGS += $(WFLAGS) # uncomment for WARNINGS
#FXT_CXXFLAGS += -D__NO_MATH_INLINES
FXT_CXXFLAGS += $(FXT_EXTRA_FLAGS)

#FXT_CXXFLAGS += -fprofile-arcs -ftest-coverage # for gcov
#FXT_CXXFLAGS += -fno-unroll-loops # for valgrind/sgcheck

#FXT_CXXFLAGS += -Wstrict-overflow=5

# Uncomment to use AMD64 popcnt (bit-count) instruction
# (should better be auto-detected):
#FXT_CXXFLAGS += -DHAVE_AMD64_POPCNT


## for clang++:
## export LD_LIBRARY_PATH="/usr/local/lib:/usr/lib:/usr/local/lib64:/usr/lib64:"
#FXT_CXXFLAGS += -Werror
#FXT_CXXFLAGS += -Weverything
#FXT_CXXFLAGS += -Wno-c++11-long-long
#FXT_CXXFLAGS += -Wno-missing-prototypes
#FXT_CXXFLAGS += -Wno-missing-variable-declarations
#FXT_CXXFLAGS += -Wno-documentation
#FXT_CXXFLAGS += -Wno-weak-vtables
#FXT_CXXFLAGS += -Wno-padded
#FXT_CXXFLAGS += -Wno-unused
#FXT_CXXFLAGS += -Wno-global-constructors -Wno-exit-time-destructors
#FXT_CXXFLAGS += -Wsometimes-uninitialized
#FXT_CXXFLAGS += -fsanitize=undefined # very useful indeed
#FXT_CXXFLAGS += -fsanitize=address # tries to allocate 15392894357504 bytes
#FXT_CXXFLAGS += -ftrapv
#FXT_CXXFLAGS += -fno-builtin

## for GCC >= 4.9.0:
#FXT_CXXFLAGS += -fsanitize=address # broken as in clang++
#FXT_CXXFLAGS += -fsanitize=undefined
#FXT_CXXFLAGS += -fsanitize=shift
#FXT_CXXFLAGS += -fdiagnostics-color=auto
#FXT_CXXFLAGS += -fsanitize=undefined,shift,integer-divide-by-zero,unreachable,null,return,signed-integer-overflow

## set CXXFLAGS only if not supplied:
CXXFLAGS ?= $(FXT_CXXFLAGS)


#.PHONY: foo
#foo:
#	echo 'CXXFLAGS=$(CXXFLAGS)'
#	echo 'FXT_CXXFLAGS=$(FXT_CXXFLAGS)'

#CXXFLAGS += -Werror # make all warnings errors

#CXXFLAGS += -DTIMING

## set CXX only if not supplied:
CXX ?= c++
## export CXX=/usr/bin/g++
## export CXX=/usr/local/bin/g++-4.8.0
## export CXX=/usr/local/bin/g++


PPLIBS = -lm -lstdc++

# gcc:
#IFLAGS =-I. -Isrc
IFLAGS =-Isrc
# llvm/clang++ (for versions <= 2.9 define CLANG for file fxtalloca.h):
#IFLAGS = \
#-Isrc \
# -I/usr/local/lib/clang/3.4/include
# -DCLANG


#### aux: ####

#TMPDIR=/tmp
TMPDIR=./

#-------------------------------------

FXTLIB=libfxt.a
LIBS = $(FXTLIB) $(PPLIBS)

SCRIPTDIR=./scripts

FXTIDIR=./src

REPLACE=$(SCRIPTDIR)/replace

TNT=test "$$?" -eq "1" ## tricky: The Not-Trick

#-------------------------------------

.PHONY: default  ## the default: build the lib
default: lib

#-------------------------------------

include files.mk

#-------------------------------------

DEP=depend.mk

include $(DEP)

.PHONY: dep depend  ## create depend.mk
dep depend:
	rm -f $(DEP)
	$(MAKE) $(DEP)

$(DEP):
	: '[$@]'
	: 'File by file generation to have full pathname with dependencies:'
	@for f in $(SRC); do  $(CXX) -MM -MT $${f%.cc}.o $(IFLAGS) $$f;  done > $(DEP)
#	cp $(DEP) sss-dep.mk ## to compare
#	@$(CXX) -MM $(IFLAGS) $(SRC) > $(DEP)
#	cp $(DEP) tmp-dep
#	@echo 'FIXING $(DEP), sigh ...'
#	@$(SCRIPTDIR)/fixdepend.pl '$(strip $(OBJS))' < depend.mk > depend.fixed
#	mv depend.fixed depend.mk

## compare:
##  replace -f -o depend-nn.mk '\\\\\\n' '' depend.mk
##  replace -f -o sss-dep-nn.mk '\\\\\\n' '' sss-dep.mk
##  diff -dbw depend-nn.mk sss-dep-nn.mk
##  mgdiff -g 1200x1000+0+0 -args "-dbw" depend-nn.mk sss-dep-nn.mk &

TMPDEPH=tmp-depend-h.mk
.PHONY: invdep ##x
invdep:
	: '[$@]'
	: 'List of headers and files depending on them:'
	cp $(DEP) $(TMPDEPH)
	@for f in $(SRC); do  $(CXX) -MM -MT $${f} $(IFLAGS) $$f;  done > $(TMPDEPH)
#	: 'Ignore the error messages "Do not include directly, ..." '
	@for f in $(FXTHDRS); do $(CXX) -DFXT_NO_WARN_HDR -MM -MT $${f} $(IFLAGS) $$f >> $(TMPDEPH) ;  done
	: 'Creating depend.inv (list of headers and files depending on them) ...'
	$(SCRIPTDIR)/mkinvdep.sh
	: '[$@ OK]'

.PHONY: whodep ##x list which files depend on what is given as PAT
whodep:
	@test -n "$(PAT)" || { echo "Usage:  make whodep PAT=filename" 1>&2; exit 1;}
#	$(SCRIPTDIR)/whodep.sh "$(PAT)"
	grep --color '.*$(PAT).*:' depend.inv

#-------------------------------------

src/aux0/version.o:  src/aux0/version.cc
	$(CXX) $< -DOFLAGS='"$(OFLAGS)"' $(CXXFLAGS) $(IFLAGS) -c -o $@
#	$(CXX) $< -DOFLAGS='"$(OFLAGS)"' $(CXXFLAGS) $(IFLAGS) -E | less

%.o : %.cc
#	$(CXX) $< $(CXXFLAGS) $(IFLAGS) -E > ./pre.cc
	$(CXX) $< $(CXXFLAGS) $(IFLAGS) -c -o $@
#	rm -f ./pre.cc

.PHONY: lib  ## build the library
lib: $(FXTLIB)

.PHONY: all  ## build the library
all: lib

$(FXTLIB): $(OBJS)
	: '[$@]'
#	@echo ' ===== making FXT lib ====='
	@ar rcs $(FXTLIB) $(OBJS)
#	nm -C $(FXTLIB)
#	@echo ' ===== make FXT lib DONE. ====='


.PHONY: obj objs  ## compile *.cc --> *.o
obj objs: $(OBJS)


#### be BSD-aware (2015-July-19: breaks on FreeBSD):
#ifeq ($(strip $(BSD_INSTALL_DATA)),)
### if ( variable empty ) simply use copy (unless variable FXT_INSTALL is supplied):
FXT_INSTALL ?= cp -puv
#else
### use the given mechanism:
#FXT_INSTALL = $(BSD_INSTALL_DATA)
#endif
#### end "BSD-aware"

## PREFIX is only set if not supplied
## for other locations use e.g.  "make install PREFIX=/opt/"
PREFIX ?= /usr/local/
LIBDIR=$(PREFIX)/lib
INCDIR=$(PREFIX)/include/fxt
.PHONY: install  ## install to $(PREFIX)/lib/ and $(PREFIX)/include/fxt/
install: lib
	: '[$@]'
	@echo 'PREFIX=$(PREFIX)  LIBDIR=$(LIBDIR)  INCDIR=$(INCDIR)'
	@:
	@test -d $(INCDIR)  ||  mkdir $(INCDIR)
	@$(FXT_INSTALL) $(FXTIDIR)/*.h $(INCDIR)/
	@cd src && for f in $(SHFXTSRCDIRS); do mkdir -p $(INCDIR)/$$f; done
	@cd src && for f in $(SHFXTSRCDIRS); do $(FXT_INSTALL) $$f/*.h $(INCDIR)/$$f; done
	@:
	@test -d $(LIBDIR)  ||  mkdir $(LIBDIR)
	@$(FXT_INSTALL) $(FXTLIB) $(LIBDIR)/
	: '[$@ OK]'

.PHONY: chk-install ##x print whether installed header files are up to date
chk-install:
	@(cd src  &&  find . -maxdepth 2 -name \*.h) > tmp-hdr1
	@(cd $(INCDIR)/  &&  find . -name \*.h) > tmp-hdr2
	@-diff tmp-hdr1 tmp-hdr2
	@rm tmp-hdr1 tmp-hdr2

.PHONY: uninstall  ## uninstall headers and lib, but leave directory $(INCDIR)
uninstall:
	: '[$@]'  ## note: we do not remove $(INCDIR)
	rm -rf $(INCDIR)/*
	rm -f $(LIBDIR)/$(FXTLIB)

.PHONY: reinstall  ## uninstall and install
reinstall: # uninstall install
	-$(MAKE) uninstall # ignore if we cannot remove the lib ...
	$(MAKE) install    # ... as long as we can overwrite it


#-------------------------------------

#ADEF=-Dstatic= -Dinline=
.PHONY: asm ##x usage: make asm ASRC=dir/file
asm:
	@test -n "$(ASRC)" ||  { echo 'USAGE:  make $@ ASRC=dir/some-file.cc'; exit 1; }
	$(CXX) $(ASRC) -fverbose-asm $(ADEF) -S -g $(CXXFLAGS) $(IFLAGS) -c -o asm.s
	echo '// -*- C++ -*-' > asm.lst
	as -alhnd asm.s >> asm.lst
	rm -f asm.s

#-------------------------------------

#GCOVno=$(OBJS:.o=.gcno)
.PHONY: rmgcov  ##x remove gcov files (from program runs)
rmgcov:
	: '[$@]'
#	ls $(GCOVno)
#	@rm -f $(GCOVno)
	rm -f $$(find . -name '*.gcov')
	rm -f $$(find . -name '*.gcda')

.PHONY: rmgcno  ##x remove gcov (graph) files (from compiling)
rmgcno:
	: '[$@]'
	rm -f $$(find . -name '*.gcno')

.PHONY: clean  ## cleanup
clean: rmgcov rmgcno
	: '[$@]'
	rm -f  a.out core .gdb_history gmon.out $(TESTBIN) $(GENBIN) $(DEMOBIN)
	-find . -name \*.o -exec rm -f {} \;
	rm -f $(CALLSRC)
	rm -f asm.lst asm.s asm.cpp
	rm -fv tmp-*

.PHONY: clobber ## cleanup incl. lib
clobber: clean
	: '[$@]'
	rm -f  $(FXTLIB)
	rm -f $(SCRIPTDIR)/depend.nn depend.nn
	rm -f $(TESTLOG)

.PHONY: new  ## cleanup and recompile everything
new: clobber depend all


#-------------------------------------
#-------------------------------------

## files that depend on BITS_USE_ASM:
# export CH='*/*.h */*.cc'
# grep -l BITS_USE_ASM $CH
# make -n  $(grep -l BITS_USE_ASM $CH | (while read a; do echo "-W $a"; done))
#
# make -n test 2>&1 | g 1test
#RUNTEST=$(TESTBIN)
#NOBITASM="$(CXXFLAGS) -DDISABLE_BIT_ASM"
#.NOTPARALLEL: test
.PHONY: test  ##x run several self tests (demos are much more useful now)
test: lib
	: '[$@]'
	CXXFLAGS="$(CXXFLAGS)" $(SCRIPTDIR)/run-tests.sh

#
TESTBIN=./bin
RUNTEST=MALLOC_CHECK_=2 $(TESTBIN)
#.NOTPARALLEL: 1test
.PHONY: 1test  ## called by 'test', usage:  make 1test TESTSRC=test/test-WHAT.cc
1test:
	: '[$@]'
	@test -n "$(TESTSRC)" || { echo 'USAGE:  make $@ TESTSRC=test/some-test.cc'; exit 1; }
#	@echo '========== routines tested: =========='
#	grep -E '(CHECK)|(ECHO)|(EQUIV)' $(TESTSRC)
	$(CXX) test/aux-test.cc $(TESTSRC) $(CXXFLAGS) $(IFLAGS) $(LIBS) -o $(TESTBIN)
	$(RUNTEST)  >  /dev/null  ||  $(MAKE) failedtest
	: '[$@ OK  (with TESTSRC=$(TESTSRC))]'
	:
#	@echo '==========  OK. ($(TESTSRC)) =========='
#	@echo

TESTLOG=failed-test.log
.PHONY: failedtest  ## called if a test failed, hopefully never
failedtest:
	: '[$@]'
	@echo -e '\n\n*********** AAARGH !  something went wrong ***********'
	@echo '  repeating with logfile := $(TESTLOG)'
	$(CXX) test/aux-test.cc $(TESTSRC) -DVERBOSE_TEST $(CXXFLAGS) $(IFLAGS) $(LIBS) -o $(TESTBIN)
	-$(RUNTEST)  >  $(TESTLOG)
	grep -B5 -A9999 "FAIL" $(TESTLOG)
	grep 'FAIL'  $(TESTLOG)
	@echo -e '\n********* =--> please contact the author <--= *********'
	false # finally fail and start being depressive

#.PHONY: tt ##x for debugging
#tt:
#	$(CXX) test/tt.cc $(CXXFLAGS) -o ./bin
##	$(CXX) test/tt.cc $(CXXFLAGS) -E > tmp.ii
##	$(CXX) test/tt.cc $(CXXFLAGS) -E | grep -v '^#' > tmp.ii
##	:
##	$(CXX) $(CXXFLAGS)  tmp.ii -o ./bin
#	:
#	./bin


.PHONY: chkdtim ##x make sure no demo has TIMING defined
chkdtim:
	: '[$@]'
	@if grep -E '^#define[ ]+TIMING' $(DEMOS); then false; else true; fi

DEMOS=demo/*/*.cc
.PHONY: chkdemo  ## some pedantic checks for the demos
chkdemo:
	: '[$@]'
	@echo "Checking Emacs-targets of demos ..."
	$(SCRIPTDIR)/chkdemo-etargets.sh
	:
	@echo "Checking demos ..."
	$(SCRIPTDIR)/chkdemo.sh
	:
	@echo "Checking includes of demos ..."
	$(SCRIPTDIR)/chkdemoincl.sh
	:
	$(MAKE) chkdtim


.PHONY: chkincl   ## some pedantic checks for correct #includes
chkincl:
	: '[$@]'
	: 'Doing some pedantic checks about #includes ...'
	:
	@echo "Running $(SCRIPTDIR)/chkifdef.sh ..."
	@bash $(SCRIPTDIR)/chkifdef.sh $(FXTHDRS)
	:
	@echo "Running $(SCRIPTDIR)/chkallincl.sh ..."
	@NONSRCDIRS="$(NONSRCDIRS)" FXTSRCDIRS="$(FXTSRCDIRS)" bash $(SCRIPTDIR)/chkallincl.sh
	:
	@echo "Running $(SCRIPTDIR)/chkinclex.sh ..."
	@FXTSRCDIRS="$(FXTSRCDIRS)"  bash $(SCRIPTDIR)/chkinclex.sh
	:
	@echo "Running $(SCRIPTDIR)/chkinclpath.sh ..."
	@FXTSRCDIRS="$(FXTSRCDIRS)"  bash $(SCRIPTDIR)/chkinclpath.sh
	:
#	@echo "Running $(SCRIPTDIR)/chkdirs.sh ..."
#	@NONSRCDIRS="$(NONSRCDIRS)" FXTSRCDIRS="$(FXTSRCDIRS)"  bash $(SCRIPTDIR)/chkdirs.sh
#	:
	:
	: '[$@ OK]'

.PHONY: chkascii ## list files containing non-ASCII chars (or tabs)
chkascii:
	: '[$@]'
	LC_ALL=C grep -l -r '[^ -~]' . ## only makefile should be listed

.PHONY: check chk  ## some pedantic checks for the code and makefile
check chk: chkcopyright chkincl chksrc
	: '[$@]'
	@echo 'CXX is $(CXX)'
	:
	@echo 'CXXFLAGS are $(CXXFLAGS)'
	:
	@echo 'IFLAGS are $(IFLAGS)'
	@echo 'OFLAGS are $(OFLAGS)'
	: '[$@ OK]'

.PHONY: chkopt  ##x check whether optimization is turned off
chkopt:
	: '[$@]'
#	@$(SCRIPTDIR)/chkopt.zsh
	@$(SCRIPTDIR)/chkopt.sh

.PHONY: xchk ## do all (non-interactive) checks
xchk:   chkopt chk doc chkdemo dep demodep
	: '[$@ OK]'


OKFILES =
#OKFILES += 00readme.txt
OKFILES += makefile COPYING.txt
OKFILES += depend.mk files.mk flags.mk fxt.lsm
OKFILES += depend.inv
OKFILES += INSTALL.txt
OKDIRS =
OKDIRS += data doc demo scripts src test
.PHONY: chkxfiles ##x check whether there are spurious files
chkxfiles:
	: '[$@]'
	@OKFILES='$(OKFILES)' OKDIRS='$(OKDIRS)' $(SCRIPTDIR)/chkxfiles.sh


.PHONY: chksrc ## check whether all sources referenced in comments exist
chksrc:
	: '[$@]'
	: 'check whether all sources referenced in comments exist:'
	@echo "Running $(SCRIPTDIR)/chksrc.sh ..."
	@SRC='$(SRC)' $(SCRIPTDIR)/chksrc.sh
	: '[$@ OK]'

.PHONY: chkcopyright ## check copyright statements
chkcopyright:
	: '[$@]'
	: 'checking copyright statements:'
	$(SCRIPTDIR)/chk-copyright.zsh
	: '[$@ OK]'

TMP1=$(TMPDIR)/tmp-1
TMP2=$(TMPDIR)/tmp-2
.PHONY: chkdblfiles  ##x find filenames that exist more than once
chkdblfiles:
	: '[$@]'
	find . -type f  | grep -v attic | grep -E -v '.*\.o$$' > $(TMP1)
	-for f in $$(cat $(TMP1)); do echo $$(basename $$f); done  | sort | uniq -d > $(TMP2)
	-for f in $$(cat $(TMP2)); do echo "$$f:"; find . -name $$f; echo ; done
	rm -fv  $(TMP1) $(TMP2)

.PHONY: rts  ##x remove trailing spaces
rts:
	: '[$@]'
	@-$(REPLACE) -qN '[ ]+$$' '' $$(grep -lE ' +$$' $(FXTHDRS))
	@-$(REPLACE) -qN '[ ]+$$' '' $$(grep -lE ' +$$' $(SRC))
	@-$(REPLACE) -qN '[ ]+$$' '' $$(grep -lE ' +$$' $(DEMOSRC))
# try: sed -ri 's/[ ]+$//;' FILEs

.PHONY: showglobals ##x show global vars in lib, omit class-global vars
showglobals: #$(FXTLIB)
	: '[$@]'
	-nm -n -A -C $(FXTLIB) | cat -n | grep -P ' [RdDbB] ' | grep -v '::'

.PHONY: chkdef  ##x heuristic check for includes
chkdef:
	: '[$@]'
	@SRC='$(SRC)' FXTHDRS='$(FXTHDRS)' bash $(SCRIPTDIR)/chkdef.sh


THINK=' !*THINK*!   ctrl-C to interrupt, enter for next check'
.PHONY: ichk  ##x some interactive checks for the code (don't do that)
ichk:
	: '[$@]'
	$(SCRIPTDIR)/chk-demo-xref.zsh | grep -v 'return' | grep -vF "=" || true
	-@read -p "(done demo crossrefs) $(THINK)" dummy
	bash $(SCRIPTDIR)/alloca.sh | grep -v 'return' | grep -vF "=" || true
	-@read -p "(done ALLOCA) $(THINK)" dummy
	@echo; echo; echo;
	@$(MAKE) rts
	-@read -p "(done TRAILING SPACES) $(THINK)" dummy
	@echo; echo; echo;
	$(MAKE) chkundoc
	-@read -p "(done UNDOC)  $(THINK)" dummy
	@echo; echo; echo;
	$(MAKE) mrtdoc
	-@read -p "(done MRTDOC)  $(THINK)" dummy
	@echo; echo; echo;
	$(MAKE) chkdef
	-@read -p "(done CHKDEF)  $(THINK)" dummy
	@echo; echo; echo;
	$(MAKE) showsrc
	-@read -p "(done SHOWSRC)  $(THINK)" dummy
	@echo; echo; echo;
	$(MAKE) showglobals
	-@read -p "(done SHOWGLOBALS)  $(THINK)" dummy
	@echo; echo; echo;
	@grep -C1 -F '/*=' $(FXTHDRS) || true
	$(MAKE) chkdblfiles
	-@read -p "(done DBLFILES) $(THINK)" dummy
	-$(MAKE) chkxfiles
	-@read -p "(done XFILES) $(THINK)" dummy
	@echo; echo; echo;


############## DEMO ##############

DEMOSCRIPT=$(SCRIPTDIR)/demo.zsh
DEMOBIN=./bin
RUNDEMO=$(DEMOBIN)
DEMODIR=./demo
DEMOSRC=$(DEMODIR)/*/*-demo.cc


#.NOTPARALLEL: demo
.PHONY: demo  ## refresh all demos (also useful as test)
demo: lib chkdtim
	WHICH='all' $(DEMOSCRIPT)

#.PHONY: odemo  ## refresh all demos (also useful as test), Oldest OUTput first
#odemo: lib
#	WHICH='oout' $(DEMOSCRIPT)

#.NOTPARALLEL: vgdemo
.PHONY: vgdemo ## check all demos with valgrind (use DSRC to select files)
vgdemo: lib chkdtim
	@echo 'With anything suspicious: disable optimization, enable debugging, and repeat.'
	WHICH='vg' $(DEMOSCRIPT)
	@echo 'With anything suspicious: disable optimization, enable debugging, and repeat.'


## use DEMOFLAGS e.g. for -DTIMING
## limit filesize, virtual memory, and time to prevent runaway:
#D_ULIMIT=ulimit -f 500 -v 16000 -t 100
## portability: limit only filesize:
D_ULIMIT=ulimit -f 500
#D_ULIMIT=true
#.NOTPARALLEL: 1demo
.PHONY: 1demo  ## called by 'demo', usage:  make 1demo DSRC=demo/WHICH-demo.cc
1demo: lib
	@test -n "$(DSRC)" || { echo 'USAGE:  make $@ DSRC=demo/dir/some-demo.cc'; exit 1; }
#	@echo "CXX=$(CXX)" 1>&2 ## show compiler executable
#	-$(CXX) --version 1>&2 ## show compiler version
	$(CXX) $(DSRC) $(CXXFLAGS) $(DEMOFLAGS) $(IFLAGS) $(LIBS) -o $(DEMOBIN)
	@echo "// output of $(DSRC):"; echo "// Description:"; grep '^//%' $(DSRC); echo "";
#	@grep '^#define TIMING' $(DSRC) || true
	$(D_ULIMIT);  $(RUNDEMO)
#	ulimit -f 500; MALLOC_CHECK_=2  $(RUNDEMO);  ## slow...
#	@echo $(CXX) 1>&2

#.PHONY: tdemo  ##x just compile demo
#tdemo: lib
#	@test -n "$(DSRC)" || { echo 'USAGE:  make $@ DSRC=demo/dir/some-demo.cc'; exit 1; }
#	$(CXX) $(DSRC) $(CXXFLAGS) $(DEMOFLAGS) $(IFLAGS) $(LIBS) -o $(DEMOBIN)
#	rm $(DEMOBIN)


## optional pattern:  make bench PAT=foo
#.NOTPARALLEL: bench
.PHONY: bench  ## run all benchmarks (demo files that contain a 'BENCHARGS=' line)
bench: chkopt
#	PAT='$(PAT)' $(SCRIPTDIR)/bench.zsh
	PAT='$(PAT)' $(SCRIPTDIR)/bench.zsh 2>&1 | tee bench-log-new.txt
	ls -l bench-log-new.txt


#.NOTPARALLEL: odemo
.PHONY: odemo  ##x do demos, starting with oldest
odemo: lib
	WHICH='old' $(DEMOSCRIPT)

#.NOTPARALLEL: ndemo
.PHONY: ndemo  ##x do "New" (i.e. last modified) demo
ndemo: lib
	$(MAKE) 1demo DSRC=$$(\ls -1t $(DEMOSRC) | head -1);

#.NOTPARALLEL: ndemo2
.PHONY: ndemo2  ##x do "almost New" (i.e. second-last modified) demo
ndemo2: lib
	$(MAKE) 1demo DSRC=$$(\ls -1t $(DEMOSRC) | head -2 | tail -1);

#.NOTPARALLEL: ntdemo
.PHONY: ntdemo  ##x do demos with sources Newer Than their output
ntdemo: lib chkdtim
	WHICH='nt' $(DEMOSCRIPT)

#.PHONY: Etarget2
#Etarget2:
#	@$(MAKE) -s --no-print-directory ntdemo;  ## tricky: no garbage in output

#.NOTPARALLEL: hdemo
.PHONY: hdemo  ##x do demos that include Header matching $PAT, usage: make hdemo PAT=cyclic
hdemo: lib
	@test -n "$(PAT)" || { echo 'USAGE:  make $@ PAT=some-pattern'; exit 1; }
	WHICH='header' PAT='$(PAT)' $(DEMOSCRIPT)

#.NOTPARALLEL: fdemo
.PHONY: fdemo  ##x do demos whose Filename contains pattern $PAT, usage: make fdemo PAT=pol
fdemo: lib
	@test -n "$(PAT)" || { echo 'USAGE:  make $@ PAT=some-pattern'; exit 1; }
	WHICH='files' PAT='$(PAT)' $(DEMOSCRIPT)

#.NOTPARALLEL: gdemo
.PHONY: gdemo  ##x do demos "grep -El $PAT demo/*/*-demo.cc", usage: make gdemo PAT=irreduc
gdemo: lib
	@test -n "$(PAT)" || { echo 'USAGE:  make $@ PAT=some-pattern'; exit 1; }
	WHICH='grep' PAT='$(PAT)' $(DEMOSCRIPT)

#.NOTPARALLEL: kdemo
.PHONY: kdemo  ##x do demos, do not stop on errors ("Keep going")
kdemo: lib
	DEMO_KEEP_GOING='1' WHICH='all' $(DEMOSCRIPT)

#.PHONY: ddemo  ##x pretend to do the demos, ("Dry-run")
#ddemo: lib
#	DEMO_DRY_RUN='1' WHICH='all' $(DEMOSCRIPT)

.PHONY: demodep ##x make sure that demos do not have invalid #includes, else unused
demodep:
	: '[$@]'
	g++ -MM $(IFLAGS) $$(\ls -1t $(DEMODIR)/*/*-demo.cc) > dep-demo.mk
	rm dep-demo.mk

##TBIN1 ?= 5
##TBIN2 ?= $(TBIN1)
#.PHONY: tbin ##x
#tbin:
#	test -z "$(TBIN2)" || \
# for n in $$(seq $(TBIN1) $(TBIN2)); do echo $$n; ./bin $$n > /dev/null || break; done

.PHONY: ctdemo  ##x how many demo programs do we have?
ctdemo:
	find ./demo/ -name \*-demo.cc | wc -l

.PHONY: ctsrc  ##x how many source files do we have?
ctsrc:
	echo ./src/*/*.cc ./src/*/*.h  | wc -w


############### PROFILING ##############

PRTMP=tmp-prof.txt
.PHONY: prof  ##x profiling: compile profiling code and run it _before_ 'make prof'
prof:
	test -f gmon.out
	gprof -b $(TESTBIN)  |  grep -B 9999 'Call graph' > $(PRTMP)
	-$(REPLACE) -fq 'unsigned long' 'ulong'  $(PRTMP)
	-$(REPLACE) -fq 'complex<double>' 'Complex'  $(PRTMP)
	cat  $(PRTMP)
# try sed

############### CALLALL ##############
#
#CALLSRC= callall.cc
#.PHONY: ca callall  ##x generate and link code that calls many funcs (check for completeness)
#ca callall: lib casrc
#	$(CXX) $(CALLSRC) $(CXXFLAGS) $(IFLAGS) -g -O1 $(LIBS) -o $(TESTBIN)
#	$(RUNTEST)
##	rm $(TESTBIN)
#	rm $(CALLSRC)
#	@echo 'OK.'
#
#.PHONY: casrc ##x generate src for callall
#casrc:
#	cat $(SCRIPTDIR)/callall.head > $(CALLSRC)
#	$(SCRIPTDIR)/mkcallall.pl < ntt/ntt.h >> $(CALLSRC)
#	cat $(SCRIPTDIR)/callall.tail >> $(CALLSRC)


############## AUTODOC ##############


#-------------------------------------

DATADOCFILE=doc/data-doc.txt
.PHONY: datadoc  ##x extract doc from files in data/
datadoc:
	: '[$@]'
	echo -e ' Generated file: doc for tables in the data/ directory\n' > $(DATADOCFILE)
	for f in data/*.txt; do grep -F '#.' $$f >/dev/null || exit 1; done
	LC_ALL=C; for f in data/*.txt; do \
 echo '----- '$$(basename $$f)":"; grep -B25 -F '#.' $$f ; echo; \
 done >> $(DATADOCFILE)


#ADOC=zsh $(SCRIPTDIR)/autodoc.zsh
AUTODOCLOG=$(TMPDIR)/tmp-autodoc.log
#REDIRECT1=1> /dev/null
#REDIRECT2=2>> $(AUTODOCLOG)

DOCTMP=$(TMPDIR)/autodoc/
.PHONY: doc autodoc  ##x generate some documentation-oids
doc autodoc: datadoc
	$(MAKE) doautodoc  ||  { tail -55 $(AUTODOCLOG); echo 1>&2 " *** There is a problem. See $(AUTODOCLOG)." ; exit 1; }
	rm -f $(AUTODOCLOG)


.PHONY: doautodoc  ##x called by autodoc
doautodoc:
	: '[$@]'
	-mkdir -p $(DOCTMP)
	-cp -a doc/* $(DOCTMP)
#	rm -f doc/*-doc.txt
	rm -f $(AUTODOCLOG)
	AUTODOCLOG='$(AUTODOCLOG)' FXTSRCDIRS='$(FXTSRCDIRS)' scripts/doc-all.zsh
	-diff -rd  $(DOCTMP) doc/
	-diff -rq  $(DOCTMP) doc/
	rm -rf  $(DOCTMP)
	: '[$@ OK]'


# format in docfiles:
#// ========== HEADER FILE bpol/bitpol.h: ==========
.PHONY: chkundoc  ##x find possibly undocumented headers
chkundoc:
	: '[$@]'
	$(SCRIPTDIR)/chkundoc.zsh | grep -v -- '-all.h'

.PHONY: mrtdoc  ##x find funcs with missing return types in documentation
mrtdoc:
	: '[$@]'
	-grep '^[a-zA-Z0-9_]\+(' doc/*.txt


############## SHOWFYI ##############
#
#.PHONY: fyi showfyi  ##x show tuning settings (#warning 'FYI: ...')
#fyi showfyi:
#	: '[$@]'
#	@FYISRC=$$(grep -l '^#.*FYI' $(SRC)); \
# for f in $$FYISRC; do \
#  echo "----- $$f: -----"; \
#  grep -v '^//#' $$f | grep -B1 'FYI'; \
#  echo; \
# done

############### FIND FILE IN FXTBOOK ##############
#
#.PHONY: ff ##x find file in fxtbook.  Usage:  make ff PAT=the-file-name
#ff:
#	@test -n "$(PAT)" || { echo 'USAGE:  make $@ PAT=file-pat'; exit 1; }
#	xdvi -findstring '$(PAT)'
#

############## get OEIS A-numbers: ##############

.PHONY: oeis ## show OEIS sequence numbers mentioned in files, see http://oeis.org
oeis:
#	@$(SCRIPTDIR)/extract-oeis-anums.pl src/*/*.{h,cc} # dash (Debian) does not grok this
	@$(SCRIPTDIR)/extract-oeis-anums.pl src/*/*.h
	@$(SCRIPTDIR)/extract-oeis-anums.pl src/*/*.cc
	@$(SCRIPTDIR)/extract-oeis-anums.pl demo/*/*.cc

.PHONY: ctoeis ## count OEIS sequence numbers mentioned in files, see http://oeis.org
ctoeis:
	: 'total OEIS refs:'
	$(MAKE) oeis | wc -l
	: 'unique OEIS refs:'
	$(MAKE) oeis | cut -s -d: -f1 | sort -u | wc -l

############## MKCOMPL: ##############

MKCOMPL=../../$(SCRIPTDIR)/mkcompl.sh
.PHONY: compl mkcompl  ##x generate type complex versions of some routines
compl mkcompl:
	: '[$@]'
	export NAME=fhtdit.cc;    export CNAME=c$$NAME;  cd src/fht  && $(MKCOMPL)
	export NAME=fhtdif.cc;    export CNAME=c$$NAME;  cd src/fht  && $(MKCOMPL)
	export NAME=fht0.cc;      export CNAME=c$$NAME;  cd src/fht  && $(MKCOMPL)
	export NAME=fhtcnvla.cc;  export CNAME=c$$NAME;  cd src/convolution  && $(MKCOMPL)
	export NAME=fhtcnvl.cc;   export CNAME=c$$NAME;  cd src/convolution  && $(MKCOMPL)
	export NAME=fhtcnvlcore.cc; export CNAME=c$$NAME;  cd src/convolution  && $(MKCOMPL)
	export NAME=fhtcnvlacore.cc; export CNAME=c$$NAME;  cd src/convolution  && $(MKCOMPL)


#.PHONY: pre  ##x dump defines
#pre:
#	$(CXX) -E -dM  $(CXXFLAGS) $(IFLAGS) test/test.h 2>&1

#-------------------------------------

ALLHDRS=$$(shell find . -name \*.h)
CCFILES=$$(find .  -maxdepth 2 -name \*.cc)
.PHONY: showsrc  ##x find *.cc files that are unused for the library
showsrc:
	: '[$@]'
	@SRC='$(SRC)' zsh $(SCRIPTDIR)/showsrc.zsh

#.PHONY: freehdrs  ##x  show installed headers that have no dependend lib source
#freehdrs: $(DEP)
#	@for h in */*.h; do \
# grep -L $$h depend.mk &>/dev/null || echo $$h ; done
#
##	@for h in $$(ls -1 $(INCDIR) ); do \

#.PHONY: shownotes ##x show comments that contain the string "note"
#shownotes:
#	-@grep -iP '\bnote\b' $(CCFILES) $(FXTDRS)

.PHONY: showtodo ##x show comments that contain "todo" or "TBD"
showtodo:
	-@grep -iP '\b(todo)|(TBD)\b' $(CCFILES) $(FXTHDRS)

.PHONY: aall  ##x more than all  ;-)
aall: clobber xchk check version doc dep demodep mkcompl
	$(MAKE) lib
#	$(MAKE) test
	$(MAKE) -s demo ## option -s to avoid changing demo's output with make's message "entering dir blah"
	-$(MAKE) invdep
	: '[$@ OK]'


#LSMDATE=$(shell date +'%d%b%Y' | tr a-z A-Z)
LSMDATE=$(shell date +'%Y-%m-%d')
VERSDATE=$(shell date +'%d-%B-%Y')
.PHONY: version ## update lsm-file and version info
version:
#	$(REPLACE) 'Entered-date.*$$' "Entered-date:   $(LSMDATE)" fxt.lsm
	$(REPLACE) -f '[0-9]{4}-[0-9]{2}-[0-9]{2}'   '$(LSMDATE)' fxt.lsm
	$(REPLACE) -f '(version_string *= *)"[^"]+"(.*)' '$$1'"\"$(VERSDATE)\""'$$2' src/aux0/version.cc
## try sed -r 's/[0-9]{4}-[0-9]{2}-[0-9]{2}/'$(date +'%Y-%m-%d')'/;' fxt.lsm
## try sed -r 's/[0-9]{4}-[0-9]{2}-[0-9]{2}/$(LSMDATE)/;' fxt.lsm

############# BACKUP ###########


#.PHONY: tmp-hbak
#tmp-hbak: clobber
#	test -n $(BAKHOST)
##	( R=$${PWD}/; cd .. && rsync -avz $$R jj@$(BAKHOST):$$R --delete --dry-run )
##	: ' ctrl-c to abort '
#	( R=$${PWD}/; cd .. && rsync -avz $$R jj@$(BAKHOST):$$R --delete )


#MYBAKDIR=$(BAKDIR)/work/fxt/
RELDIR:=$${PWD\#$$HOME}
MYBAKDIR=$(BAKDIR)/$(RELDIR)
.PHONY: testbakdir ##x called by bak and fbak
testbakdir:
	test -n "$(BAKDIR)"
	test -d $(BAKDIR)
	test -n "$(MYBAKDIR)"
	test -d $(MYBAKDIR)

.PHONY: bak  ##x copy files to some backup dir
bak: clobber testbakdir
	cp -aru doc/* $(MYBAKDIR)/doc # copy doc silently
	cp -aru demo/* $(MYBAKDIR)/demo # copy demo output silently
	cp -aruv * $(MYBAKDIR)

#.PHONY: fbak ##x fast backup without 'clean'
#fbak: testbakdir
#	rm -f $(FXTLIB)
#	find . -type f -a ! -name \*.o | (while read f; do cp -uav $$f $(MYBAKDIR)/$$f; done )

.PHONY: syncdry ##x rsync incl. delete (dry run)
syncdry: testbakdir
	rsync -avW ./ $(MYBAKDIR) --delete --dry-run

.PHONY: sync  ##x rsync incl. delete
sync: testbakdir
	rsync -avW ./ $(MYBAKDIR) --delete

EXCL= ## files to exclude: --exclude 'filepat'
ZBAKDATE=$(shell date '+%Y.%m.%d')
MYZBAKDIR=$(ZBAKDIR)/$(PROJ)
ZBAK=$(MYZBAKDIR)/$(PROJ)-$(ZBAKDATE).tgz
.PHONY: zbak dist  ##x create archive with date (for backup and distribution)
zbak dist:
	$(MAKE) clobber chkxfiles check xchk version
	grep -En '^CXXFLAGS \+= -Werror' makefile; $(TNT)
	test -n "$(ZBAKDIR)"
	test -d $(ZBAKDIR)
	test -n "$(MYZBAKDIR)"
	test -d $(MYZBAKDIR)
	$(MAKE) chkxfiles
	cd ..  &&  tar -czf $(ZBAK) $(EXCL) $(PROJ)
	ls -ltr $(MYZBAKDIR)/ | tail -5

#CHKZBAK=$(HOME)/bin/chkzbak.sh
.PHONY: chkzbak  ##x check how up-to-date the last archived backup is
chkzbak: diff-old
#	test -x $(CHKZBAK)
#	-$(CHKZBAK)

.PHONY: diff-old ##x compare (dirdiff) to old version (unpacked in /dev/shm)
diff-old:
	test -d "${MYZBAKDIR}"
#	ls -hF $(WEBLOC)/fxt-20*.tgz
	( cd $(WEBLOC) && ls -hF ./fxt-20*.tgz; )
	$(SCRIPTDIR)/diff-old.zsh

.PHONY: build-old ##x build old version in /dev/shm
build-old:
	test -d "${MYZBAKDIR}"
	BDATE=$(BDATE) $(SCRIPTDIR)/build-old.zsh

.PHONY: tzbak  ##x zbak to /tmp
tzbak:
	$(MAKE) zbak ZBAKDIR=/tmp MYZBAKDIR=/tmp ZBAKDATE=$(shell date '+%Y.%m.%d-%H.%M.%S')



WEBLOC=$(WEBDIR)/fxt/
.PHONY: chkweb ##x check whether $(WEBLOC) exists
chkweb:
	: '[$@]'
	test -n "$(WEBDIR)"
	test -d $(WEBLOC)

.PHONY: 2web 4web  ##x copy stuff where it gets rsync'd to my website
2web 4web: chkweb
	: '[$@]'
	test -f $(ZBAK)  # version of today
	:
	test -n "$(WEBLOC)"
	test -d $(WEBLOC)
	:
	cp -puv $(ZBAK) $(WEBLOC)
	$(REPLACE) 'fxt-[0-9]{4}\.[0-9]{2}\.[0-9]{2}\.tgz' "fxt-$(ZBAKDATE).tgz" $(WEBLOC)/fxtpage.html
	:
	$(MAKE) doc2web
	:
	$(MAKE) demo2web
	:
	$(MAKE) data2web
	:
	$(MAKE) bw2web

.PHONY: doc2web ##x called by 2web: put documentation to web
doc2web:
	: '[$@]'
	cp -puv doc/*   $(WEBLOC)/doc/
	diff -q doc/  $(WEBLOC)/doc/  ;  true
	cp -puv fxt.lsm $(WEBLOC)
#	grep -A999 DESCRIPTION 00readme.txt > $(WEBLOC)/description.txt
	cd $(WEBLOC)/doc/ && lshtml > index.html

.PHONY: data2web  ##x called by 2web:  put math data to web
data2web:
	: '[$@]'
	test -d $(WEBDIR)/mathdata/
	cp -uv ./data/* $(WEBDIR)/mathdata/
	$(SCRIPTDIR)/datahtmldoc.zsh > $(WEBDIR)/mathdata/index.html

.PHONY: bw2web  ##x called by 2web:  put bitwizardry stuff to web
bw2web:
	: '[$@]'
	WEBDIR=$(WEBDIR) $(SCRIPTDIR)/bw2web.zsh


#D2WDIR=/tmp/demo2web/
WEBDEMOLOC=$(WEBDIR)/fxt/demo/
## script demo2web.sh uses firsthdrs.pl and make-demo-list.sh
.PHONY: demo2web  ##x called by 2web:  put demos to web (topics from demo/topics.txt)
demo2web: chkdemo
	: '[$@]'
	test -n $(WEBDIR)
	test -d $(WEBDIR)
	test -d $(WEBDEMOLOC)
	rsync --version >/dev/null ## make sure we have rsync
	perl -v > /dev/null ## make sure we have perl
	rsync -avW demo/  $(WEBDEMOLOC)/
	rsync -aW demo/  $(WEBDEMOLOC)/ --delete
	WEBDEMOLOC=$(WEBDEMOLOC) FXTLOC=$$PWD scripts/demo2web.sh


#.PHONY: zbaka  ##x copy archive to a floppy (twice)
#zbaka: #zbak
#	test -n "$(ZBAKDIR)"
#	test -f $(ZBAK)
#	mcopy -o $(ZBAK) a:
#	-mmd -o dito
#	mcopy -o $(ZBAK) a:dito
#	mdir -/

NLAST=50
.PHONY: last ##x list src-files changed most recently
last:
	ls -ltr $$(find . -name \*.cc -o -name \*.h) | tail -n $(NLAST)

.PHONY: elast ##x select a recently modified file to edit
elast:
	select F in $$(ls -tr $$(find . -name \*.cc -o -name \*.h) | tail -n $(NLAST)); do ( $$EDITOR $$F &); break ; done


#TAGDECLFLAGS=--language=c++ --ignore-indentation --declarations --members
#TAGDEFNFLAGS=--language=c++ --ignore-indentation --no-defines
#FTAGDECL=$(TMPDIR)/tagsdeclarations.txt
#FTAGDEF=$(TMPDIR)/tagsdefinitions.txt
CTAGSOUT=$(TMPDIR)/tags-fxt.txt
CTAGSFLAGS=--language-force=c++ --sort=no
.PHONY: tags  ##x etags (under construction)
tags:
#	@echo '$(FXTHDRS)' >  $(SCRIPTDIR)/hh.lst
#	@echo '$(SRC)' >  $(SCRIPTDIR)/cc.lst
#	@echo ' declarations --> $(FTAGDECL)'
#	@etags $(TAGDECLFLAGS) $(FXTHDRS) -o - | cat -v > $(FTAGDECL)
#	@echo ' definitions --> $(FTAGDEF)'
#	@etags $(TAGDEFNFLAGS) $(FXTHDRS) $(SRC) -o - | cat -v > $(FTAGDEF)
	@echo '  --> $(CTAGSOUT)'
	@ctags -x $(CTAGSFLAGS) $(FXTHDRS) $(SRC)  > $(CTAGSOUT)

#.PHONY: ebrowse ##x ebrowse (under construction)
#ebrowse:
#	rm -f ebrowse.txt
#	ebrowse -o ebrowse.txt $(FXTHDRS) $(SRC)


.PHONY: cat ##x cat all src files to /dev/null so their contents are in memory
cat:
	: '[$@]'
	cat $$(find . -name \*.cc) > /dev/null
	cat $$(find . -name \*.h) > /dev/null
	cat $$(find . -name \*-out.txt) > /dev/null


.PHONY: help h  ## help on make targets
h help:
	grep '^\.PHONY' *akefile* | grep -v '##x'

.PHONY: xhelp xh  ## help on all make targets including the weird and dangerous
xh xhelp:
	grep '^\.PHONY' *akefile*


# Emacs:
# Local Variables:
# frame-title-format: "FXT makefile"
# End:

################## end FXT makefile ##########################
