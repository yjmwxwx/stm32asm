#!/usr/bin/env bash

exit 1 ## OBSOLETE

#
# check directory lists from makefile
#

# supplied from environment:
# FXTSRCDIRS
# NONSRCDIRS

#set -vx

TMPI=/tmp/incl-tmpi
TMPA=/tmp/incl-tmpa
TMPT=/tmp/incl-tmpt

ALLDIRS=$(find .  -maxdepth 9 -mindepth 1 -type d | sort)
FXTSRCDIRS=$(echo ${FXTSRCDIRS} | sort)
NONSRCDIRS=$(echo ${NONSRCDIRS} | sort)

rm -f  ${TMPI}
for f in  ${ALLDIRS}; do  echo $f >> ${TMPI}; done
sort ${TMPI} > ${TMPA}
#U=$(uniq -d  ${TMPA})
#test -z "$U" || { echo " *** duplicate 1: [$U]"; exit 1; }

rm -f  ${TMPI}
for f in   ${FXTSRCDIRS} ${NONSRCDIRS}; do  echo $f >> ${TMPI}; done
sort ${TMPI} > ${TMPT}
U=$(uniq -d  ${TMPT})
test -z "$U" || { echo " *** duplicate: [$U]"; exit 1; }

D=$(diff -u ${TMPA} ${TMPT})
test -z "$D" || { echo " *** difference:"; echo "[[$D]]"; exit 1; }

rm -f ${TMPI} ${TMPA} ${TMPT}

echo 'OK.'


exit 0;
##########################################
