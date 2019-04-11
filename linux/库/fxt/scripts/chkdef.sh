#! /usr/bin/env bash


#set -vx

# from environment:
CH="${SRC} ${FXTHDRS}"

function chk
{
    echo "W=[$W]"  "H=[$H]";

    W='\b'"$W"'\b';

    H='\b'"$H"'\b';

    X=$(grep -El $W $CH);

    Z=$(grep -EL $H $X);

    echo $Z;
}

echo

W='BITS_PER_LONG'; H='bits/bitsperlong\.h'; chk;
W='restrict'; H='(restrict)\.h'; chk;
W='ulong'; H='(fxttypes)\.h'; chk;
W='uint'; H='(fxttypes)\.h'; chk;
W='uchar'; H='(fxttypes)\.h'; chk;
W='Complex'; H='(complextype)\.h'; chk;
W='SinCos'; H='(sincos)|(csincos)\.h'; chk;
W='jjassert'; H='(jjassert)\.h'; chk;
W='(sumdiff)|(sumdiff05)|(diffsum)|(sumdiff_r)'; H='(sumdiff)\.h'; chk;
W='(sqrt\()'; H='cmath'; chk;


exit 0;
####################################
