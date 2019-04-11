#! /usr/bin/env zsh

# from environment:
# ${SRC}

TMPDIR=/tmp
TMP1=${TMPDIR}/tmp-1 # the list from the makefile
TMP2=${TMPDIR}/tmp-2 # all files we find

rm -f ${TMP1} ${TMP2}

for f in ${=SRC}; do  echo $f >> ${TMP1};  done
sort ${TMP1} -o ${TMP1}

#find src -maxdepth 2 -name \*.cc  | sort > ${TMP2}
#find src -maxdepth 2 -type f  | sort > ${TMP2}
find src -maxdepth 2 \! -name \*.h -and -type f | sort > ${TMP2}

echo 'Non source files are (no output is fine):'
diff ${TMP1} ${TMP2}

#rm -f ${TMP1} ${TMP2}

exit 0;
############################
