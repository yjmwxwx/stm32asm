#! /bin/sh

# quick hack by Joerg Arndt (arndt (AT) jjj.de)
# version: 2002-July-06 (13:41)

/usr/bin/test -n "$NAME" || exit 1;
/usr/bin/test -n "$CNAME" || exit 1;

echo "  creating $CNAME from $NAME ... "

if [ -f $CNAME ]; then
#    echo "file $CNAME already exists, copying it into /tmp ";
    cp $CNAME /tmp;
fi

#exit 0;

FROM=`basename $NAME`;

echo > $CNAME
echo "// MACHINE GENERATED FILE, DO NOT EDIT !" >> $CNAME
echo "// this file was generated from $FROM" >> $CNAME
echo '#include "complextype.h"' >> $CNAME

PCMD='while(<STDIN>) { /^\/\// || /jjkeep/ || s/double/Complex/g; s/realconvolution.h/complexconvolution.h/g; print;}'
perl -we "$PCMD" < $NAME >> $CNAME

touch --reference=$NAME $CNAME

if [ -f /tmp/$CNAME ]; then
    diff $CNAME /tmp/$CNAME &>/dev/null ||  echo "  *** CHANGE wrt. last version. ***"
fi

echo "  done."
echo

exit 0;
####################################
