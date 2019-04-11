#! /usr/bin/env zsh


# from environment: FXTSRCDIRS AUTODOCLOG

#set -vx
LC_ALL=C
rm -f ${AUTODOCLOG}
for d in ${=FXTSRCDIRS}; do
    echo " [$d]";
    test -d $d || { echo " *** Not a directory: [$d]"; exit 1; }
    x=${d#src/}
    scripts/autodoc.zsh $d/*h > doc/$x-doc.txt 2>> ${AUTODOCLOG}  || exit 1;
#    scripts/autodoc.zsh $d/*h $d/*.cc > doc/$x-doc.txt 2>> ${AUTODOCLOG}
done

exit 0;
