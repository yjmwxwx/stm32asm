src/bits/revbin-upd.o: src/bits/revbin-upd.cc src/bits/bitsperlong.h \
 src/fxttypes.h
src/bits/revbin-tab.o: src/bits/revbin-tab.cc src/array-len.h \
 src/fxttypes.h
src/bits/lin2hilbert.o: src/bits/lin2hilbert.cc src/fxttypes.h \
 src/bits/bitsperlong.h src/bits/bitzip.h src/bits/bitbutterfly.h \
 src/bits/graycode.h
src/bits/tinyfactors.o: src/bits/tinyfactors.cc src/array-len.h \
 src/fxttypes.h src/bits/bitsperlong.h
src/bits/print-bin.o: src/bits/print-bin.cc src/bits/bitsperlong.h \
 src/comb/comb-print.h src/fxttypes.h src/fxtio.h src/fxtalloca.h
src/bits/print-bindiff.o: src/bits/print-bindiff.cc src/bits/revbin.h \
 src/bits/bitswap.h src/fxttypes.h src/bits/bitsperlong.h \
 src/bits/bitasm.h src/bits/bitasm-amd64.h src/bits/bitasm-sse.h \
 src/fxtio.h
src/bits/print-bitset.o: src/bits/print-bitset.cc src/bits/revbin.h \
 src/bits/bitswap.h src/fxttypes.h src/bits/bitsperlong.h \
 src/bits/bitasm.h src/bits/bitasm-amd64.h src/bits/bitasm-sse.h \
 src/fxtio.h
src/bits/crc32.o: src/bits/crc32.cc src/bits/crc32.h src/fxttypes.h
src/bits/crc64.o: src/bits/crc64.cc src/bits/crc64.h src/fxttypes.h
src/bits/bitcount-v.o: src/bits/bitcount-v.cc src/bits/bitcount.h \
 src/fxttypes.h src/bits/bitsperlong.h src/bits/bitasm.h \
 src/bits/bitasm-amd64.h src/bits/bitasm-sse.h
src/bpol/bitpol-print.o: src/bpol/bitpol-print.cc src/fxtio.h \
 src/bits/bithigh.h src/bits/bithigh-edge.h src/fxttypes.h \
 src/bits/bitsperlong.h src/bits/bitasm.h src/bits/bitasm-amd64.h \
 src/bits/bitasm-sse.h src/bits/bitldeq.h src/bits/print-bin.h
src/bpol/bitpol2lhca.o: src/bpol/bitpol2lhca.cc \
 src/bpol/bitpolmod-solvequadratic.h src/fxttypes.h \
 src/bpol/bitpol-degree.h src/bits/bithigh.h src/bits/bithigh-edge.h \
 src/bits/bitsperlong.h src/bits/bitasm.h src/bits/bitasm-amd64.h \
 src/bits/bitasm-sse.h src/bits/bitldeq.h src/bpol/bitpol-deriv.h \
 src/bpol/bitpolmod-arith.h src/bpol/bitpol-gcd.h src/bpol/bitpol-arith.h \
 src/bits/bitlow.h src/bits/revbin.h src/bits/bitswap.h
src/bpol/bitpol-order.o: src/bpol/bitpol-order.cc src/fxttypes.h \
 src/bpol/bitpolmod-arith.h src/bpol/bitpol-gcd.h src/bpol/bitpol-arith.h \
 src/bits/bithigh.h src/bits/bithigh-edge.h src/bits/bitsperlong.h \
 src/bits/bitasm.h src/bits/bitasm-amd64.h src/bits/bitasm-sse.h \
 src/bits/bitldeq.h src/bits/bitlow.h src/mod/factor.h src/mod/mtypes.h \
 src/fxtio.h
src/bpol/primpoly-rand.o: src/bpol/primpoly-rand.cc src/array-len.h \
 src/fxttypes.h src/bits/bitsperlong.h
src/bpol/primpoly-lowbit.o: src/bpol/primpoly-lowbit.cc src/array-len.h \
 src/fxttypes.h src/bits/bitsperlong.h
src/bpol/primpoly-minweight.o: src/bpol/primpoly-minweight.cc \
 src/array-len.h src/fxttypes.h src/bits/bitsperlong.h
src/bpol/normal-irredpoly.o: src/bpol/normal-irredpoly.cc src/array-len.h \
 src/fxttypes.h src/bits/bitsperlong.h
src/bpol/normal-primpoly.o: src/bpol/normal-primpoly.cc src/array-len.h \
 src/fxttypes.h src/bits/bitsperlong.h
src/bpol/lhcarule-minweight.o: src/bpol/lhcarule-minweight.cc \
 src/array-len.h src/fxttypes.h src/bits/bitsperlong.h
src/bpol/bitpol-irred-ben-or.o: src/bpol/bitpol-irred-ben-or.cc \
 src/bits/bitsperlong.h src/bpol/bitpol-gcd.h src/bpol/bitpol-arith.h \
 src/bits/bithigh.h src/bits/bithigh-edge.h src/fxttypes.h \
 src/bits/bitasm.h src/bits/bitasm-amd64.h src/bits/bitasm-sse.h \
 src/bits/bitldeq.h src/bits/bitlow.h src/bpol/bitpolmod-arith.h
src/bpol/bitpol-irred-rabin.o: src/bpol/bitpol-irred-rabin.cc \
 src/bpol/bitpol-gcd.h src/bpol/bitpol-arith.h src/bits/bithigh.h \
 src/bits/bithigh-edge.h src/fxttypes.h src/bits/bitsperlong.h \
 src/bits/bitasm.h src/bits/bitasm-amd64.h src/bits/bitasm-sse.h \
 src/bits/bitldeq.h src/bits/bitlow.h src/bpol/bitpolmod-arith.h
src/bpol/bitpol-spi.o: src/bpol/bitpol-spi.cc src/bpol/bitpolmod-arith.h \
 src/bpol/bitpol-gcd.h src/bpol/bitpol-arith.h src/bits/bithigh.h \
 src/bits/bithigh-edge.h src/fxttypes.h src/bits/bitsperlong.h \
 src/bits/bitasm.h src/bits/bitasm-amd64.h src/bits/bitasm-sse.h \
 src/bits/bitldeq.h src/bits/bitlow.h src/bits/parity.h \
 src/bits/graycode.h
src/bpol/normal-mult.o: src/bpol/normal-mult.cc src/bits/bitrotate.h \
 src/fxttypes.h src/bits/bitsperlong.h src/bits/bitasm.h \
 src/bits/bitasm-amd64.h src/bits/bitasm-sse.h src/bits/parity.h \
 src/bits/graycode.h src/bmat/bitmat-inline.h
src/bpol/bitpol-squarefree.o: src/bpol/bitpol-squarefree.cc \
 src/bpol/bitpol-arith.h src/bits/bithigh.h src/bits/bithigh-edge.h \
 src/fxttypes.h src/bits/bitsperlong.h src/bits/bitasm.h \
 src/bits/bitasm-amd64.h src/bits/bitasm-sse.h src/bits/bitldeq.h \
 src/bpol/bitpol-gcd.h src/bits/bitlow.h src/bpol/bitpol-squarefree.h \
 src/bpol/bitpol-deriv.h src/bits/bitzip.h src/bits/bitbutterfly.h
src/bpol/bitpol-normal.o: src/bpol/bitpol-normal.cc \
 src/bmat/bitmat-funcs.h src/fxttypes.h src/restrict.h \
 src/bmat/bitmat-inline.h src/bits/parity.h src/bits/bitsperlong.h \
 src/bits/graycode.h src/bits/bitasm.h src/bits/bitasm-amd64.h \
 src/bits/bitasm-sse.h src/bits/bitrotate.h src/bpol/bitpolmod-arith.h \
 src/bpol/bitpol-gcd.h src/bpol/bitpol-arith.h src/bits/bithigh.h \
 src/bits/bithigh-edge.h src/bits/bitldeq.h src/bits/bitlow.h \
 src/bpol/bitpol-irred.h src/bits/bittransforms.h \
 src/bpol/normalpoly-dual.h src/fxtalloca.h
src/bpol/num-bitpol.o: src/bpol/num-bitpol.cc src/array-len.h \
 src/fxttypes.h src/bits/bitsperlong.h src/comb/num-necklaces.h
src/bpol/berlekamp.o: src/bpol/berlekamp.cc src/bpol/bitpol-arith.h \
 src/bits/bithigh.h src/bits/bithigh-edge.h src/fxttypes.h \
 src/bits/bitsperlong.h src/bits/bitasm.h src/bits/bitasm-amd64.h \
 src/bits/bitasm-sse.h src/bits/bitldeq.h src/bpol/bitpol-gcd.h \
 src/bits/bitlow.h src/bpol/bitpol-degree.h src/bpol/bitpolmod-arith.h \
 src/bmat/bitmat-funcs.h src/restrict.h src/bmat/bitmat-inline.h \
 src/bits/parity.h src/bits/graycode.h src/bits/bitrotate.h \
 src/fxtalloca.h
src/bpol/bitpol-factor.o: src/bpol/bitpol-factor.cc \
 src/bpol/bitpol-factor.h src/fxttypes.h src/bpol/bitpol-irred.h \
 src/bits/bittransforms.h src/bits/bitsperlong.h \
 src/bpol/bitpol-squarefree.h src/bpol/bitpol-deriv.h \
 src/bpol/bitpol-gcd.h src/bpol/bitpol-arith.h src/bits/bithigh.h \
 src/bits/bithigh-edge.h src/bits/bitasm.h src/bits/bitasm-amd64.h \
 src/bits/bitasm-sse.h src/bits/bitldeq.h src/bits/bitlow.h \
 src/bits/bitzip.h src/bits/bitbutterfly.h src/bpol/bitpol-degree.h \
 src/aux0/swap.h
src/bpol/bitpolmod-solvequadratic.o: src/bpol/bitpolmod-solvequadratic.cc \
 src/bpol/bitpol-degree.h src/bits/bithigh.h src/bits/bithigh-edge.h \
 src/fxttypes.h src/bits/bitsperlong.h src/bits/bitasm.h \
 src/bits/bitasm-amd64.h src/bits/bitasm-sse.h src/bits/bitldeq.h \
 src/bpol/bitpolmod-arith.h src/bpol/bitpol-gcd.h src/bpol/bitpol-arith.h \
 src/bits/bitlow.h src/bpol/gf2n-trace.h src/bits/parity.h \
 src/bits/graycode.h
src/bpol/bitpolmod-minpoly.o: src/bpol/bitpolmod-minpoly.cc \
 src/bpol/bitpolmod-arith.h src/bpol/bitpol-gcd.h src/bpol/bitpol-arith.h \
 src/bits/bithigh.h src/bits/bithigh-edge.h src/fxttypes.h \
 src/bits/bitsperlong.h src/bits/bitasm.h src/bits/bitasm-amd64.h \
 src/bits/bitasm-sse.h src/bits/bitldeq.h src/bits/bitlow.h
src/bpol/normalpoly-dual.o: src/bpol/normalpoly-dual.cc \
 src/bpol/gf2n-trace.h src/fxttypes.h src/bits/parity.h \
 src/bits/bitsperlong.h src/bits/graycode.h src/bits/bitasm.h \
 src/bits/bitasm-amd64.h src/bits/bitasm-sse.h src/bpol/bitpolmod-arith.h \
 src/bpol/bitpol-gcd.h src/bpol/bitpol-arith.h src/bits/bithigh.h \
 src/bits/bithigh-edge.h src/bits/bitldeq.h src/bits/bitlow.h \
 src/bpol/bitpolmod-minpoly.h
src/bpol/gf2n.o: src/bpol/gf2n.cc src/fxttypes.h src/bits/bitsperlong.h \
 src/bpol/poly-tab.h src/bmat/bitmat-inline.h src/bits/parity.h \
 src/bits/graycode.h src/bits/bitasm.h src/bits/bitasm-amd64.h \
 src/bits/bitasm-sse.h src/bits/bitrotate.h src/bmat/bitmat-funcs.h \
 src/restrict.h src/bits/bitlow.h src/bits/print-bin.h \
 src/bpol/bitpol-irred.h src/bits/bittransforms.h src/bpol/bitpol-order.h \
 src/bpol/normalbasis.h src/bpol/normal-solvequadratic.h \
 src/bits/revgraycode.h src/bpol/gf2n.h src/bpol/bitpolmod-arith.h \
 src/bpol/bitpol-gcd.h src/bpol/bitpol-arith.h src/bits/bithigh.h \
 src/bits/bithigh-edge.h src/bits/bitldeq.h src/bpol/gf2n-trace.h \
 src/fxtio.h src/mod/factor.h src/mod/mtypes.h src/mod/mersenne.h \
 src/sort/bsearch.h src/jjassert.h
src/bpol/gf2n-trace.o: src/bpol/gf2n-trace.cc src/bpol/bitpolmod-arith.h \
 src/bpol/bitpol-gcd.h src/bpol/bitpol-arith.h src/bits/bithigh.h \
 src/bits/bithigh-edge.h src/fxttypes.h src/bits/bitsperlong.h \
 src/bits/bitasm.h src/bits/bitasm-amd64.h src/bits/bitasm-sse.h \
 src/bits/bitldeq.h src/bits/bitlow.h src/bits/parity.h \
 src/bits/graycode.h
src/bpol/gf2n-solvequadratic.o: src/bpol/gf2n-solvequadratic.cc \
 src/bpol/gf2n.h src/fxttypes.h src/bits/bitsperlong.h \
 src/bpol/bitpolmod-arith.h src/bpol/bitpol-gcd.h src/bpol/bitpol-arith.h \
 src/bits/bithigh.h src/bits/bithigh-edge.h src/bits/bitasm.h \
 src/bits/bitasm-amd64.h src/bits/bitasm-sse.h src/bits/bitldeq.h \
 src/bits/bitlow.h src/bpol/gf2n-trace.h src/bits/parity.h \
 src/bits/graycode.h src/fxtio.h
src/bpol/gf2n-minpoly.o: src/bpol/gf2n-minpoly.cc src/bpol/gf2n.h \
 src/fxttypes.h src/bits/bitsperlong.h src/bpol/bitpolmod-arith.h \
 src/bpol/bitpol-gcd.h src/bpol/bitpol-arith.h src/bits/bithigh.h \
 src/bits/bithigh-edge.h src/bits/bitasm.h src/bits/bitasm-amd64.h \
 src/bits/bitasm-sse.h src/bits/bitldeq.h src/bits/bitlow.h \
 src/bpol/gf2n-trace.h src/bits/parity.h src/bits/graycode.h src/fxtio.h
src/bpol/gf2n-order.o: src/bpol/gf2n-order.cc src/fxttypes.h \
 src/bpol/bitpolmod-arith.h src/bpol/bitpol-gcd.h src/bpol/bitpol-arith.h \
 src/bits/bithigh.h src/bits/bithigh-edge.h src/bits/bitsperlong.h \
 src/bits/bitasm.h src/bits/bitasm-amd64.h src/bits/bitasm-sse.h \
 src/bits/bitldeq.h src/bits/bitlow.h src/mod/factor.h src/mod/mtypes.h \
 src/fxtio.h
src/bmat/bitmat-mult-mm.o: src/bmat/bitmat-mult-mm.cc src/bits/parity.h \
 src/fxttypes.h src/bits/bitsperlong.h src/bits/graycode.h \
 src/bits/bitasm.h src/bits/bitasm-amd64.h src/bits/bitasm-sse.h \
 src/bmat/bitmat-funcs.h src/restrict.h src/fxtalloca.h
src/bmat/bitmat-transpose.o: src/bmat/bitmat-transpose.cc src/fxtalloca.h \
 src/fxttypes.h
src/bmat/bitmat-inverse.o: src/bmat/bitmat-inverse.cc \
 src/bmat/bitmat-inline.h src/fxttypes.h src/bits/parity.h \
 src/bits/bitsperlong.h src/bits/graycode.h src/bits/bitasm.h \
 src/bits/bitasm-amd64.h src/bits/bitasm-sse.h src/bits/bitrotate.h \
 src/bmat/bitmat-funcs.h src/restrict.h src/bits/bitlow.h src/aux0/swap.h \
 src/fxtalloca.h
src/bmat/bitmat-nullspace.o: src/bmat/bitmat-nullspace.cc \
 src/bmat/bitmat-inline.h src/fxttypes.h src/bits/parity.h \
 src/bits/bitsperlong.h src/bits/graycode.h src/bits/bitasm.h \
 src/bits/bitasm-amd64.h src/bits/bitasm-sse.h src/bits/bitrotate.h \
 src/fxtalloca.h
src/bmat/bitmat-hessenberg.o: src/bmat/bitmat-hessenberg.cc \
 src/bmat/bitmat-inline.h src/fxttypes.h src/bits/parity.h \
 src/bits/bitsperlong.h src/bits/graycode.h src/bits/bitasm.h \
 src/bits/bitasm-amd64.h src/bits/bitasm-sse.h src/bits/bitrotate.h \
 src/bits/bitswap.h src/aux0/swap.h
src/bmat/bitmat-charpoly.o: src/bmat/bitmat-charpoly.cc \
 src/bmat/bitmat-inline.h src/fxttypes.h src/bits/parity.h \
 src/bits/bitsperlong.h src/bits/graycode.h src/bits/bitasm.h \
 src/bits/bitasm-amd64.h src/bits/bitasm-sse.h src/bits/bitrotate.h \
 src/bmat/bitmat-funcs.h src/restrict.h src/fxtalloca.h
src/bmat/bitmat-kronecker.o: src/bmat/bitmat-kronecker.cc \
 src/bmat/bitmat-inline.h src/fxttypes.h src/bits/parity.h \
 src/bits/bitsperlong.h src/bits/graycode.h src/bits/bitasm.h \
 src/bits/bitasm-amd64.h src/bits/bitasm-sse.h src/bits/bitrotate.h \
 src/restrict.h
src/bmat/bitmat-print.o: src/bmat/bitmat-print.cc src/bits/print-bin.h \
 src/fxttypes.h src/fxtio.h
src/aux0/version.o: src/aux0/version.cc src/fxtio.h
src/aux0/randf.o: src/aux0/randf.cc src/fxttypes.h src/aux0/sincos.h
src/aux0/print-fixed.o: src/aux0/print-fixed.cc src/fxtio.h
src/aux0/jjassert.o: src/aux0/jjassert.cc src/jjassert.h src/fxtio.h
src/aux0/tex-line.o: src/aux0/tex-line.cc src/aux0/tex-line.h \
 src/fxttypes.h src/fxtio.h src/jjassert.h
src/aux1/bytescan.o: src/aux1/bytescan.cc src/bits/bitsperlong.h \
 src/fxttypes.h src/bits/zerobyte.h
src/aux1/num2str.o: src/aux1/num2str.cc src/aux0/swap.h src/fxttypes.h
src/sort/radixsort.o: src/sort/radixsort.cc src/aux0/swap.h \
 src/bits/bitsperlong.h src/fxttypes.h src/fxtalloca.h src/restrict.h
src/ds/bitarray.o: src/ds/bitarray.cc src/ds/bitarray.h \
 src/bits/bitcount.h src/fxttypes.h src/bits/bitsperlong.h \
 src/bits/bitasm.h src/bits/bitasm-amd64.h src/bits/bitasm-sse.h \
 src/bits/print-bin.h src/fxtio.h
src/comb/fact2perm.o: src/comb/fact2perm.cc src/perm/rotate.h \
 src/fxttypes.h src/perm/reverse.h src/aux0/swap.h
src/comb/big-fact2perm.o: src/comb/big-fact2perm.cc \
 src/ds/left-right-array.h src/fxttypes.h
src/comb/fact2num.o: src/comb/fact2num.cc src/fxttypes.h
src/comb/num2perm.o: src/comb/num2perm.cc src/comb/fact2perm.h \
 src/fxttypes.h src/comb/fact2num.h src/fxtalloca.h
src/comb/fact2perm-rev.o: src/comb/fact2perm-rev.cc src/fxtalloca.h \
 src/aux0/swap.h src/perm/reverse.h src/fxttypes.h
src/comb/fact2perm-swp.o: src/comb/fact2perm-swp.cc src/fxtalloca.h \
 src/aux0/swap.h src/fxttypes.h
src/comb/fact2perm-rot.o: src/comb/fact2perm-rot.cc src/fxtalloca.h \
 src/perm/rotate.h src/fxttypes.h src/perm/reverse.h src/aux0/swap.h
src/comb/fact2cyclic.o: src/comb/fact2cyclic.cc src/aux0/swap.h \
 src/fxttypes.h
src/comb/print-perm.o: src/comb/print-perm.cc src/fxttypes.h src/fxtio.h
src/comb/catalan.o: src/comb/catalan.cc src/comb/catalan.h src/fxttypes.h \
 src/fxtio.h
src/comb/print-catalan-step-rgs-aa.o: \
 src/comb/print-catalan-step-rgs-aa.cc src/fxtio.h src/fxttypes.h
src/comb/print-catalan-path-aa.o: src/comb/print-catalan-path-aa.cc \
 src/comb/catalan-path-lex.h src/comb/is-catalan-path.h src/fxttypes.h \
 src/comb/print-catalan-path-aa.h src/comb/comb-print.h src/fxtio.h
src/comb/paren-string-to-rgs.o: src/comb/paren-string-to-rgs.cc \
 src/comb/reverse-paren-string.h src/fxttypes.h
src/comb/partition-conj.o: src/comb/partition-conj.cc src/fxttypes.h
src/comb/cayley-perm.o: src/comb/cayley-perm.cc src/comb/cayley-perm.h \
 src/comb/comb-print.h src/fxttypes.h src/aux0/swap.h src/fxtio.h
src/comb/partition.o: src/comb/partition.cc src/comb/partition.h \
 src/fxttypes.h src/fxtio.h
src/comb/partition-gen.o: src/comb/partition-gen.cc \
 src/comb/partition-gen.h src/fxttypes.h src/fxtio.h
src/comb/partition-rgs-lex.o: src/comb/partition-rgs-lex.cc \
 src/comb/partition-rgs-lex.h src/comb/comb-print.h src/fxttypes.h \
 src/comb/is-partition-rgs.h src/fxtio.h
src/comb/setpart.o: src/comb/setpart.cc src/comb/setpart.h \
 src/comb/is-setpart-rgs.h src/fxttypes.h src/aux0/sign.h src/fxtio.h
src/comb/print-zero-map-rgs.o: src/comb/print-zero-map-rgs.cc \
 src/fxttypes.h src/fxtio.h
src/comb/setpart-rgs-gray.o: src/comb/setpart-rgs-gray.cc \
 src/comb/setpart-rgs-gray.h src/comb/is-setpart-rgs.h src/fxttypes.h \
 src/comb/comb-print.h src/sort/minmaxmed23.h src/fxtio.h
src/comb/combination-rec.o: src/comb/combination-rec.cc \
 src/comb/combination-rec.h src/fxttypes.h src/comb/comb-print.h
src/comb/delta2gray.o: src/comb/delta2gray.cc src/bits/bitlow.h \
 src/fxttypes.h src/bits/bitsperlong.h src/bits/bitasm.h \
 src/bits/bitasm-amd64.h src/bits/bitasm-sse.h
src/comb/monotonic-gray.o: src/comb/monotonic-gray.cc \
 src/comb/delta2gray.h src/fxttypes.h src/fxtalloca.h
src/comb/acgray.o: src/comb/acgray.cc src/comb/delta2gray.h \
 src/fxttypes.h src/perm/reverse.h src/aux0/swap.h src/fxtalloca.h
src/comb/test-gray.o: src/comb/test-gray.cc src/bits/bit2pow.h \
 src/fxttypes.h src/bits/bitsperlong.h src/bits/bithigh.h \
 src/bits/bithigh-edge.h src/bits/bitasm.h src/bits/bitasm-amd64.h \
 src/bits/bitasm-sse.h src/bits/bitldeq.h src/bits/bitcount.h
src/comb/print-gray.o: src/comb/print-gray.cc src/bits/print-bin.h \
 src/fxttypes.h src/bits/bitlow.h src/bits/bitsperlong.h \
 src/bits/bitasm.h src/bits/bitasm-amd64.h src/bits/bitasm-sse.h \
 src/bits/bit2pow.h src/bits/bithigh.h src/bits/bithigh-edge.h \
 src/bits/bitldeq.h src/bits/bitcount.h src/fxtio.h
src/comb/stringsubst.o: src/comb/stringsubst.cc src/comb/stringsubst.h \
 src/fxttypes.h src/fxtio.h
src/comb/num-necklaces.o: src/comb/num-necklaces.cc src/array-len.h \
 src/fxttypes.h src/bits/bitsperlong.h
src/comb/composition-rank.o: src/comb/composition-rank.cc \
 src/comb/composition-rank.h src/comb/num-compositions.h src/fxttypes.h \
 src/fxtio.h
src/comb/composition-nz-rank.o: src/comb/composition-nz-rank.cc \
 src/bits/graycode.h src/fxttypes.h src/bits/bitsperlong.h \
 src/bits/bitlex.h src/bits/bitcount.h src/bits/bitasm.h \
 src/bits/bitasm-amd64.h src/bits/bitasm-sse.h src/bits/bithigh.h \
 src/bits/bithigh-edge.h src/bits/bitldeq.h \
 src/comb/composition-nz-rank.h
src/comb/composition-nz-minc.o: src/comb/composition-nz-minc.cc \
 src/comb/composition-nz-minc.h src/comb/is-composition-nz.h \
 src/fxttypes.h src/comb/comb-print.h src/comb/print-composition-aa.h \
 src/fxtio.h
src/comb/print-composition-aa.o: src/comb/print-composition-aa.cc \
 src/fxtio.h src/fxttypes.h src/jjassert.h
src/comb/print-composition-by-sorts.o: \
 src/comb/print-composition-by-sorts.cc src/fxtio.h src/fxttypes.h
src/comb/print-partition-aa.o: src/comb/print-partition-aa.cc src/fxtio.h \
 src/fxttypes.h
src/comb/print-partition-conj.o: src/comb/print-partition-conj.cc \
 src/fxtio.h src/fxttypes.h
src/comb/print-composition-unimodal.o: \
 src/comb/print-composition-unimodal.cc src/fxtio.h src/fxttypes.h
src/comb/binary-huffman.o: src/comb/binary-huffman.cc \
 src/comb/binary-huffman.h src/comb/comb-print.h src/fxttypes.h \
 src/fxtio.h
src/comb/ksubset-rec.o: src/comb/ksubset-rec.cc src/comb/ksubset-rec.h \
 src/aux0/swap.h src/fxttypes.h src/sort/minmaxmed23.h
src/comb/print-set.o: src/comb/print-set.cc src/fxtio.h src/fxttypes.h \
 src/jjassert.h
src/comb/print-mset.o: src/comb/print-mset.cc src/fxtio.h src/fxttypes.h \
 src/jjassert.h
src/comb/print-setpart.o: src/comb/print-setpart.cc src/fxttypes.h \
 src/fxtio.h
src/comb/print-vec.o: src/comb/print-vec.cc src/fxtio.h src/array-len.h \
 src/fxttypes.h
src/comb/print-arrangement-rgs-perm.o: \
 src/comb/print-arrangement-rgs-perm.cc src/comb/fact2perm.h \
 src/fxttypes.h src/comb/comb-print.h src/fxtio.h
src/comb/print-mixedradix.o: src/comb/print-mixedradix.cc src/fxttypes.h \
 src/fxtio.h
src/comb/mixedradix2num.o: src/comb/mixedradix2num.cc src/fxttypes.h
src/comb/mixedradix-init.o: src/comb/mixedradix-init.cc src/fxttypes.h
src/comb/mset-perm-lex-rec.o: src/comb/mset-perm-lex-rec.cc \
 src/comb/mset-perm-lex-rec.h src/fxttypes.h
src/comb/print-young-tab-rgs-aa.o: src/comb/print-young-tab-rgs-aa.cc \
 src/fxtio.h src/fxttypes.h
src/comb/tree-lev-seq-aux.o: src/comb/tree-lev-seq-aux.cc \
 src/comb/tree-lev-seq-aux.h src/fxttypes.h src/fxtio.h src/fxtalloca.h \
 src/jjassert.h
src/comb/ordered-tree-branches.o: src/comb/ordered-tree-branches.cc \
 src/comb/ordered-tree-branches.h src/comb/is-composition-nz.h \
 src/fxttypes.h src/comb/comb-print.h src/fxtio.h
src/comb/ordered-tree-branching-seq.o: \
 src/comb/ordered-tree-branching-seq.cc \
 src/comb/ordered-tree-branching-seq.h src/comb/comb-print.h \
 src/fxttypes.h src/fxtio.h src/fxtalloca.h src/jjassert.h
src/graph/digraph.o: src/graph/digraph.cc src/graph/digraph.h \
 src/fxttypes.h src/sort/sortfunc.h src/sort/minmaxmed23func.h \
 src/aux0/swap.h src/sort/sortidxfunc.h src/perm/reverse.h \
 src/perm/permq.h src/perm/permrand.h src/aux0/rand-idx.h src/fxtio.h \
 src/jjassert.h
src/graph/digraph-paths.o: src/graph/digraph-paths.cc \
 src/graph/digraph-paths.h src/graph/digraph.h src/fxttypes.h \
 src/graph/print-path.h src/bits/bit2pow.h src/bits/bitsperlong.h \
 src/bits/bithigh.h src/bits/bithigh-edge.h src/bits/bitasm.h \
 src/bits/bitasm-amd64.h src/bits/bitasm-sse.h src/bits/bitldeq.h \
 src/fxtio.h
src/graph/search-digraph.o: src/graph/search-digraph.cc \
 src/graph/digraph-paths.h src/graph/digraph.h src/fxttypes.h \
 src/graph/print-path.h src/fxtio.h
src/graph/search-digraph-cond.o: src/graph/search-digraph-cond.cc \
 src/graph/digraph-paths.h src/graph/digraph.h src/fxttypes.h \
 src/graph/print-path.h src/fxtio.h
src/graph/search-digraph-trylucky.o: src/graph/search-digraph-trylucky.cc \
 src/graph/digraph-paths.h src/graph/digraph.h src/fxttypes.h \
 src/graph/print-path.h src/fxtio.h
src/graph/print-path.o: src/graph/print-path.cc src/bits/print-bin.h \
 src/fxttypes.h src/fxtio.h
src/graph/mk-complete-digraph.o: src/graph/mk-complete-digraph.cc \
 src/graph/digraph.h src/fxttypes.h
src/graph/mk-debruijn-digraph.o: src/graph/mk-debruijn-digraph.cc \
 src/graph/digraph.h src/fxttypes.h src/aux0/swap.h
src/graph/mk-gray-digraph.o: src/graph/mk-gray-digraph.cc \
 src/graph/digraph-paths.h src/graph/digraph.h src/fxttypes.h \
 src/graph/print-path.h src/bits/bitlow.h src/bits/bitsperlong.h \
 src/bits/bitasm.h src/bits/bitasm-amd64.h src/bits/bitasm-sse.h \
 src/bits/bitrotate.h src/jjassert.h
src/graph/mk-paren-gray-digraph.o: src/graph/mk-paren-gray-digraph.cc \
 src/graph/digraph.h src/fxttypes.h src/bits/parenwords.h \
 src/bits/bitsperlong.h src/bits/bitcombcolex.h src/bits/bitlow.h \
 src/bits/bitasm.h src/bits/bitasm-amd64.h src/bits/bitasm-sse.h \
 src/bits/bitcount.h src/bits/bitrotate.h src/perm/reverse.h \
 src/aux0/swap.h src/aux1/copy.h src/complextype.h src/jjassert.h
src/graph/mk-fibrep-gray-digraph.o: src/graph/mk-fibrep-gray-digraph.cc \
 src/graph/digraph.h src/fxttypes.h src/bits/fibrep.h \
 src/bits/bitsperlong.h src/bits/bit2pow.h src/bits/bithigh.h \
 src/bits/bithigh-edge.h src/bits/bitasm.h src/bits/bitasm-amd64.h \
 src/bits/bitasm-sse.h src/bits/bitldeq.h src/aux1/copy.h \
 src/complextype.h
src/graph/mk-mtl-digraph.o: src/graph/mk-mtl-digraph.cc \
 src/graph/digraph.h src/fxttypes.h src/sort/sort.h \
 src/sort/minmaxmed23.h src/aux0/swap.h src/sort/bsearch.h \
 src/bits/bitcombcolex.h src/bits/bitsperlong.h src/aux0/binomial.h \
 src/jjassert.h
src/graph/mk-perm-gray-digraph.o: src/graph/mk-perm-gray-digraph.cc \
 src/graph/digraph-paths.h src/graph/digraph.h src/fxttypes.h \
 src/graph/print-path.h src/aux0/swap.h src/aux0/factorial.h \
 src/comb/num2perm.h src/perm/perminvert.h src/sort/minmaxmed23.h \
 src/sort/sort.h
src/graph/mk-perm-pref-rev-digraph.o: \
 src/graph/mk-perm-pref-rev-digraph.cc src/graph/digraph-paths.h \
 src/graph/digraph.h src/fxttypes.h src/graph/print-path.h \
 src/aux0/factorial.h src/comb/num2perm.h src/perm/reverse.h \
 src/aux0/swap.h
src/graph/mk-perm-pref-rot-digraph.o: \
 src/graph/mk-perm-pref-rot-digraph.cc src/graph/digraph-paths.h \
 src/graph/digraph.h src/fxttypes.h src/graph/print-path.h \
 src/aux0/factorial.h src/comb/num2perm.h src/perm/rotate.h \
 src/perm/reverse.h src/aux0/swap.h
src/graph/mk-lyndon-gray-digraph.o: src/graph/mk-lyndon-gray-digraph.cc \
 src/graph/mk-special-digraphs.h src/graph/digraph-paths.h \
 src/graph/digraph.h src/fxttypes.h src/graph/print-path.h \
 src/sort/sort.h src/sort/minmaxmed23.h src/aux0/swap.h \
 src/sort/bsearch.h src/sort/unique.h src/sort/sortfunc.h \
 src/sort/minmaxmed23func.h src/comb/num-necklaces.h \
 src/bits/bitsperlong.h src/mod/primes.h src/mod/mtypes.h \
 src/bits/bit-necklace.h src/bits/bitperiodic.h src/bits/bithigh.h \
 src/bits/bithigh-edge.h src/bits/bitasm.h src/bits/bitasm-amd64.h \
 src/bits/bitasm-sse.h src/bits/bitldeq.h src/bits/tinyfactors.h \
 src/bits/bit2pow.h src/bits/bitcyclic-minmax.h src/bits/bitrotate.h \
 src/bits/bitcyclic-period.h src/bits/bitcyclic-match.h \
 src/bits/print-bin.h src/bits/bitlow.h src/fxtio.h src/fxtalloca.h \
 src/jjassert.h
src/graph/lyndon-cmp.o: src/graph/lyndon-cmp.cc src/bits/bitcount.h \
 src/fxttypes.h src/bits/bitsperlong.h src/bits/bitasm.h \
 src/bits/bitasm-amd64.h src/bits/bitasm-sse.h src/bits/graycode.h \
 src/bits/bitlex.h src/bits/bithigh.h src/bits/bithigh-edge.h \
 src/bits/bitldeq.h src/bits/revbin.h src/bits/bitswap.h \
 src/bits/bitlow.h src/bits/bitsequency.h src/bits/bitcombcolex.h \
 src/bits/bittransforms.h
src/perm/zip.o: src/perm/zip.cc src/fxttypes.h src/complextype.h \
 src/perm/revbinpermute.h src/perm/shortrevbinpermute.h src/aux0/swap.h \
 src/bits/revbin-upd.h src/bits/bitsperlong.h src/bits/bitlow.h \
 src/bits/bitasm.h src/bits/bitasm-amd64.h src/bits/bitasm-sse.h \
 src/bits/revbin.h src/bits/bitswap.h src/bits/bit2pow.h \
 src/bits/bithigh.h src/bits/bithigh-edge.h src/bits/bitldeq.h
src/perm/permq.o: src/perm/permq.cc src/perm/permq.h src/fxttypes.h \
 src/ds/bitarray.h src/bits/bitcount.h src/bits/bitsperlong.h \
 src/bits/bitasm.h src/bits/bitasm-amd64.h src/bits/bitasm-sse.h \
 src/ds/left-right-array.h
src/perm/printcycles.o: src/perm/printcycles.cc src/ds/bitarray.h \
 src/bits/bitcount.h src/fxttypes.h src/bits/bitsperlong.h \
 src/bits/bitasm.h src/bits/bitasm-amd64.h src/bits/bitasm-sse.h \
 src/fxtio.h
src/perm/perminvert.o: src/perm/perminvert.cc src/ds/bitarray.h \
 src/bits/bitcount.h src/fxttypes.h src/bits/bitsperlong.h \
 src/bits/bitasm.h src/bits/bitasm-amd64.h src/bits/bitasm-sse.h \
 src/bits/bit2pow.h src/bits/bithigh.h src/bits/bithigh-edge.h \
 src/bits/bitldeq.h src/restrict.h
src/perm/permcompose.o: src/perm/permcompose.cc src/perm/perminvert.h \
 src/fxttypes.h src/perm/permcompose.h src/aux1/copy.h src/complextype.h \
 src/bits/bit2pow.h src/bits/bitsperlong.h src/bits/bithigh.h \
 src/bits/bithigh-edge.h src/bits/bitasm.h src/bits/bitasm-amd64.h \
 src/bits/bitasm-sse.h src/bits/bitldeq.h src/ds/bitarray.h \
 src/bits/bitcount.h src/restrict.h
src/perm/perm2ccf.o: src/perm/perm2ccf.cc src/ds/bitarray.h \
 src/bits/bitcount.h src/fxttypes.h src/bits/bitsperlong.h \
 src/bits/bitasm.h src/bits/bitasm-amd64.h src/bits/bitasm-sse.h \
 src/fxtio.h
src/fft/fftdit2.o: src/fft/fftdit2.cc src/fxttypes.h src/complextype.h \
 src/aux0/csincos.h src/aux0/sincos.h src/perm/revbinpermute.h \
 src/perm/shortrevbinpermute.h src/aux0/swap.h src/bits/revbin-upd.h \
 src/bits/bitsperlong.h src/bits/bitlow.h src/bits/bitasm.h \
 src/bits/bitasm-amd64.h src/bits/bitasm-sse.h src/bits/revbin.h \
 src/bits/bitswap.h src/bits/bit2pow.h src/bits/bithigh.h \
 src/bits/bithigh-edge.h src/bits/bitldeq.h
src/fft/fftdif2.o: src/fft/fftdif2.cc src/fxttypes.h src/complextype.h \
 src/aux0/csincos.h src/aux0/sincos.h src/perm/revbinpermute.h \
 src/perm/shortrevbinpermute.h src/aux0/swap.h src/bits/revbin-upd.h \
 src/bits/bitsperlong.h src/bits/bitlow.h src/bits/bitasm.h \
 src/bits/bitasm-amd64.h src/bits/bitasm-sse.h src/bits/revbin.h \
 src/bits/bitswap.h src/bits/bit2pow.h src/bits/bithigh.h \
 src/bits/bithigh-edge.h src/bits/bitldeq.h
src/fft/fftdit4l.o: src/fft/fftdit4l.cc src/fxttypes.h src/complextype.h \
 src/aux0/csincos.h src/aux0/sincos.h src/perm/revbinpermute.h \
 src/perm/shortrevbinpermute.h src/aux0/swap.h src/bits/revbin-upd.h \
 src/bits/bitsperlong.h src/bits/bitlow.h src/bits/bitasm.h \
 src/bits/bitasm-amd64.h src/bits/bitasm-sse.h src/bits/revbin.h \
 src/bits/bitswap.h src/bits/bit2pow.h src/bits/bithigh.h \
 src/bits/bithigh-edge.h src/bits/bitldeq.h
src/fft/fftdif4l.o: src/fft/fftdif4l.cc src/fxttypes.h src/complextype.h \
 src/aux0/csincos.h src/aux0/sincos.h src/perm/revbinpermute.h \
 src/perm/shortrevbinpermute.h src/aux0/swap.h src/bits/revbin-upd.h \
 src/bits/bitsperlong.h src/bits/bitlow.h src/bits/bitasm.h \
 src/bits/bitasm-amd64.h src/bits/bitasm-sse.h src/bits/revbin.h \
 src/bits/bitswap.h src/bits/bit2pow.h src/bits/bithigh.h \
 src/bits/bithigh-edge.h src/bits/bitldeq.h
src/fft/fftdit4.o: src/fft/fftdit4.cc src/fft/shortfft.h \
 src/complextype.h src/aux0/cmult.h src/aux0/sumdiff.h \
 src/perm/revbinpermute.h src/perm/shortrevbinpermute.h src/aux0/swap.h \
 src/fxttypes.h src/bits/revbin-upd.h src/bits/bitsperlong.h \
 src/bits/bitlow.h src/bits/bitasm.h src/bits/bitasm-amd64.h \
 src/bits/bitasm-sse.h src/bits/revbin.h src/bits/bitswap.h \
 src/bits/bit2pow.h src/bits/bithigh.h src/bits/bithigh-edge.h \
 src/bits/bitldeq.h src/aux0/sincos.h
src/fft/cfftdit4.o: src/fft/cfftdit4.cc src/fft/shortfft.h \
 src/complextype.h src/aux0/cmult.h src/aux0/sumdiff.h \
 src/perm/revbinpermute.h src/perm/shortrevbinpermute.h src/aux0/swap.h \
 src/fxttypes.h src/bits/revbin-upd.h src/bits/bitsperlong.h \
 src/bits/bitlow.h src/bits/bitasm.h src/bits/bitasm-amd64.h \
 src/bits/bitasm-sse.h src/bits/revbin.h src/bits/bitswap.h \
 src/bits/bit2pow.h src/bits/bithigh.h src/bits/bithigh-edge.h \
 src/bits/bitldeq.h src/aux0/csincos.h src/aux0/sincos.h
src/fft/fftdif4.o: src/fft/fftdif4.cc src/fft/shortfft.h \
 src/complextype.h src/aux0/cmult.h src/aux0/sumdiff.h \
 src/perm/revbinpermute.h src/perm/shortrevbinpermute.h src/aux0/swap.h \
 src/fxttypes.h src/bits/revbin-upd.h src/bits/bitsperlong.h \
 src/bits/bitlow.h src/bits/bitasm.h src/bits/bitasm-amd64.h \
 src/bits/bitasm-sse.h src/bits/revbin.h src/bits/bitswap.h \
 src/bits/bit2pow.h src/bits/bithigh.h src/bits/bithigh-edge.h \
 src/bits/bitldeq.h src/aux0/sincos.h
src/fft/cfftdif4.o: src/fft/cfftdif4.cc src/fft/shortfft.h \
 src/complextype.h src/aux0/cmult.h src/aux0/sumdiff.h \
 src/perm/revbinpermute.h src/perm/shortrevbinpermute.h src/aux0/swap.h \
 src/fxttypes.h src/bits/revbin-upd.h src/bits/bitsperlong.h \
 src/bits/bitlow.h src/bits/bitasm.h src/bits/bitasm-amd64.h \
 src/bits/bitasm-sse.h src/bits/revbin.h src/bits/bitswap.h \
 src/bits/bit2pow.h src/bits/bithigh.h src/bits/bithigh-edge.h \
 src/bits/bitldeq.h src/aux0/csincos.h src/aux0/sincos.h
src/fft/fft8ditcore.o: src/fft/fft8ditcore.cc src/complextype.h
src/fft/fft8difcore.o: src/fft/fft8difcore.cc src/complextype.h
src/fft/fft9.o: src/fft/fft9.cc src/aux0/cmult.h src/complextype.h \
 src/aux0/sumdiff.h
src/fft/fftsplitradix.o: src/fft/fftsplitradix.cc src/fxttypes.h \
 src/aux0/sincos.h src/aux0/cmult.h src/complextype.h src/aux0/sumdiff.h \
 src/perm/revbinpermute.h src/perm/shortrevbinpermute.h src/aux0/swap.h \
 src/bits/revbin-upd.h src/bits/bitsperlong.h src/bits/bitlow.h \
 src/bits/bitasm.h src/bits/bitasm-amd64.h src/bits/bitasm-sse.h \
 src/bits/revbin.h src/bits/bitswap.h src/bits/bit2pow.h \
 src/bits/bithigh.h src/bits/bithigh-edge.h src/bits/bitldeq.h
src/fft/cfftsplitradix.o: src/fft/cfftsplitradix.cc src/fxttypes.h \
 src/complextype.h src/aux0/sumdiff.h src/perm/revbinpermute.h \
 src/perm/shortrevbinpermute.h src/aux0/swap.h src/bits/revbin-upd.h \
 src/bits/bitsperlong.h src/bits/bitlow.h src/bits/bitasm.h \
 src/bits/bitasm-amd64.h src/bits/bitasm-sse.h src/bits/revbin.h \
 src/bits/bitswap.h src/bits/bit2pow.h src/bits/bithigh.h \
 src/bits/bithigh-edge.h src/bits/bitldeq.h src/aux0/sincos.h
src/fft/fhtfft.o: src/fft/fhtfft.cc src/fht/fht-default.h \
 src/fht/fhtloc2.h src/fht/fht.h src/fxttypes.h src/complextype.h \
 src/fht/hartleyshift.h src/aux0/sincos.h src/aux0/sumdiff.h \
 src/aux0/constants.h src/perm/revbinpermute.h \
 src/perm/shortrevbinpermute.h src/aux0/swap.h src/bits/revbin-upd.h \
 src/bits/bitsperlong.h src/bits/bitlow.h src/bits/bitasm.h \
 src/bits/bitasm-amd64.h src/bits/bitasm-sse.h src/bits/revbin.h \
 src/bits/bitswap.h src/bits/bit2pow.h src/bits/bithigh.h \
 src/bits/bithigh-edge.h src/bits/bitldeq.h src/fht/shortfhtdifcore.h \
 src/aux0/cmult.h src/fht/shortfhtditcore.h src/fft/fft.h
src/fft/fhtcfft.o: src/fft/fhtcfft.cc src/fht/fht-default.h \
 src/fht/fhtloc2.h src/fht/fht.h src/fxttypes.h src/complextype.h \
 src/fht/hartleyshift.h src/aux0/sincos.h src/aux0/sumdiff.h \
 src/aux0/constants.h src/perm/revbinpermute.h \
 src/perm/shortrevbinpermute.h src/aux0/swap.h src/bits/revbin-upd.h \
 src/bits/bitsperlong.h src/bits/bitlow.h src/bits/bitasm.h \
 src/bits/bitasm-amd64.h src/bits/bitasm-sse.h src/bits/revbin.h \
 src/bits/bitswap.h src/bits/bit2pow.h src/bits/bithigh.h \
 src/bits/bithigh-edge.h src/bits/bitldeq.h src/fht/shortfhtdifcore.h \
 src/aux0/cmult.h src/fht/shortfhtditcore.h src/fft/fft.h
src/fft/fftspect.o: src/fft/fftspect.cc src/realfft/realfft.h \
 src/fxttypes.h
src/fft/fouriershift.o: src/fft/fouriershift.cc src/fxttypes.h \
 src/complextype.h src/aux0/sincos.h
src/fft/skipfft.o: src/fft/skipfft.cc src/fft/fft.h src/fxttypes.h \
 src/complextype.h src/bits/bit2pow.h src/bits/bitsperlong.h \
 src/bits/bithigh.h src/bits/bithigh-edge.h src/bits/bitasm.h \
 src/bits/bitasm-amd64.h src/bits/bitasm-sse.h src/bits/bitldeq.h \
 src/aux1/copy.h
src/fft/twodimfft.o: src/fft/twodimfft.cc src/bits/bit2pow.h \
 src/fxttypes.h src/bits/bitsperlong.h src/bits/bithigh.h \
 src/bits/bithigh-edge.h src/bits/bitasm.h src/bits/bitasm-amd64.h \
 src/bits/bitasm-sse.h src/bits/bitldeq.h src/fft/fft-default.h \
 src/fft/fft.h src/complextype.h
src/fft/cfftwrap.o: src/fft/cfftwrap.cc src/fft/fft.h src/fxttypes.h \
 src/complextype.h src/perm/zip.h src/perm/revbinpermute.h \
 src/perm/shortrevbinpermute.h src/aux0/swap.h src/bits/revbin-upd.h \
 src/bits/bitsperlong.h src/bits/bitlow.h src/bits/bitasm.h \
 src/bits/bitasm-amd64.h src/bits/bitasm-sse.h src/bits/revbin.h \
 src/bits/bitswap.h src/bits/bit2pow.h src/bits/bithigh.h \
 src/bits/bithigh-edge.h src/bits/bitldeq.h src/bits/bitrotate.h \
 src/restrict.h
src/fft/slowft.o: src/fft/slowft.cc src/fxttypes.h src/complextype.h \
 src/aux0/csincos.h src/aux0/sincos.h src/aux0/cmult.h src/aux1/copy.h \
 src/fxtalloca.h
src/fft/recfft2.o: src/fft/recfft2.cc src/fft/fft.h src/fxttypes.h \
 src/complextype.h src/aux1/copy.h src/fxtalloca.h
src/fft/weightedfft.o: src/fft/weightedfft.cc src/fft/fft-default.h \
 src/fft/fft.h src/fxttypes.h src/complextype.h
src/fft/columnffts.o: src/fft/columnffts.cc src/realfft/realfft.h \
 src/fxttypes.h src/fft/fft.h src/complextype.h src/bits/bit2pow.h \
 src/bits/bitsperlong.h src/bits/bithigh.h src/bits/bithigh-edge.h \
 src/bits/bitasm.h src/bits/bitasm-amd64.h src/bits/bitasm-sse.h \
 src/bits/bitldeq.h src/aux1/copy.h
src/fft/rowffts.o: src/fft/rowffts.cc src/fft/fft-default.h src/fft/fft.h \
 src/fxttypes.h src/complextype.h src/bits/bit2pow.h \
 src/bits/bitsperlong.h src/bits/bithigh.h src/bits/bithigh-edge.h \
 src/bits/bitasm.h src/bits/bitasm-amd64.h src/bits/bitasm-sse.h \
 src/bits/bitldeq.h
src/fft/rowcnvls.o: src/fft/rowcnvls.cc \
 src/convolution/weightedconvolution.h src/fxttypes.h src/complextype.h \
 src/restrict.h src/bits/bit2pow.h src/bits/bitsperlong.h \
 src/bits/bithigh.h src/bits/bithigh-edge.h src/bits/bitasm.h \
 src/bits/bitasm-amd64.h src/bits/bitasm-sse.h src/bits/bitldeq.h
src/fft/matrixfft.o: src/fft/matrixfft.cc src/fft/matrixfft.h \
 src/fxttypes.h src/complextype.h src/aux0/ldn2rc.h src/aux2/transpose2.h \
 src/ds/bitarray.h src/bits/bitcount.h src/bits/bitsperlong.h \
 src/bits/bitasm.h src/bits/bitasm-amd64.h src/bits/bitasm-sse.h \
 src/aux2/transpose.h src/restrict.h src/bits/bitrotate.h \
 src/bits/bit2pow.h src/bits/bithigh.h src/bits/bithigh-edge.h \
 src/bits/bitldeq.h
src/realfft/realfftbyfht.o: src/realfft/realfftbyfht.cc \
 src/fht/fht-default.h src/fht/fhtloc2.h src/fht/fht.h src/fxttypes.h \
 src/complextype.h src/fht/hartleyshift.h src/aux0/sincos.h \
 src/aux0/sumdiff.h src/aux0/constants.h src/perm/revbinpermute.h \
 src/perm/shortrevbinpermute.h src/aux0/swap.h src/bits/revbin-upd.h \
 src/bits/bitsperlong.h src/bits/bitlow.h src/bits/bitasm.h \
 src/bits/bitasm-amd64.h src/bits/bitasm-sse.h src/bits/revbin.h \
 src/bits/bitswap.h src/bits/bit2pow.h src/bits/bithigh.h \
 src/bits/bithigh-edge.h src/bits/bitldeq.h src/fht/shortfhtdifcore.h \
 src/aux0/cmult.h src/fht/shortfhtditcore.h
src/realfft/realfftwrap.o: src/realfft/realfftwrap.cc src/fft/fft.h \
 src/fxttypes.h src/complextype.h src/aux0/cmult.h src/aux0/sumdiff.h \
 src/perm/zip.h src/perm/revbinpermute.h src/perm/shortrevbinpermute.h \
 src/aux0/swap.h src/bits/revbin-upd.h src/bits/bitsperlong.h \
 src/bits/bitlow.h src/bits/bitasm.h src/bits/bitasm-amd64.h \
 src/bits/bitasm-sse.h src/bits/revbin.h src/bits/bitswap.h \
 src/bits/bit2pow.h src/bits/bithigh.h src/bits/bithigh-edge.h \
 src/bits/bitldeq.h src/bits/bitrotate.h src/restrict.h src/aux0/sincos.h \
 src/perm/reverse.h
src/realfft/realffteasyord.o: src/realfft/realffteasyord.cc \
 src/realfft/realfft.h src/fxttypes.h src/aux0/sumdiff.h \
 src/perm/reverse.h src/aux0/swap.h
src/realfft/realfftsplitradix.o: src/realfft/realfftsplitradix.cc \
 src/realfft/realfft.h src/fxttypes.h src/aux0/cmult.h src/complextype.h \
 src/aux0/sumdiff.h src/aux0/constants.h src/aux1/arith1.h \
 src/perm/revbinpermute.h src/perm/shortrevbinpermute.h src/aux0/swap.h \
 src/bits/revbin-upd.h src/bits/bitsperlong.h src/bits/bitlow.h \
 src/bits/bitasm.h src/bits/bitasm-amd64.h src/bits/bitasm-sse.h \
 src/bits/revbin.h src/bits/bitswap.h src/bits/bit2pow.h \
 src/bits/bithigh.h src/bits/bithigh-edge.h src/bits/bitldeq.h \
 src/perm/revbinpermute0.h src/perm/shortrevbinpermute0.h \
 src/aux0/sincos.h
src/realfft/skiprealfft.o: src/realfft/skiprealfft.cc \
 src/realfft/realfft.h src/fxttypes.h src/bits/bit2pow.h \
 src/bits/bitsperlong.h src/bits/bithigh.h src/bits/bithigh-edge.h \
 src/bits/bitasm.h src/bits/bitasm-amd64.h src/bits/bitasm-sse.h \
 src/bits/bitldeq.h src/aux1/copy.h src/complextype.h
src/fht/fhtdit2.o: src/fht/fhtdit2.cc src/fxttypes.h src/complextype.h \
 src/aux0/sincos.h src/perm/revbinpermute.h src/perm/shortrevbinpermute.h \
 src/aux0/swap.h src/bits/revbin-upd.h src/bits/bitsperlong.h \
 src/bits/bitlow.h src/bits/bitasm.h src/bits/bitasm-amd64.h \
 src/bits/bitasm-sse.h src/bits/revbin.h src/bits/bitswap.h \
 src/bits/bit2pow.h src/bits/bithigh.h src/bits/bithigh-edge.h \
 src/bits/bitldeq.h src/aux0/sumdiff.h
src/fht/fhtdif2.o: src/fht/fhtdif2.cc src/fxttypes.h src/aux0/sincos.h \
 src/perm/revbinpermute.h src/perm/shortrevbinpermute.h src/aux0/swap.h \
 src/bits/revbin-upd.h src/bits/bitsperlong.h src/bits/bitlow.h \
 src/bits/bitasm.h src/bits/bitasm-amd64.h src/bits/bitasm-sse.h \
 src/bits/revbin.h src/bits/bitswap.h src/bits/bit2pow.h \
 src/bits/bithigh.h src/bits/bithigh-edge.h src/bits/bitldeq.h \
 src/aux0/sumdiff.h
src/fht/fhtdit.o: src/fht/fhtdit.cc src/fxttypes.h src/aux0/cmult.h \
 src/complextype.h src/aux0/sumdiff.h src/aux0/constants.h \
 src/aux0/sincos.h src/perm/revbinpermute.h src/perm/shortrevbinpermute.h \
 src/aux0/swap.h src/bits/revbin-upd.h src/bits/bitsperlong.h \
 src/bits/bitlow.h src/bits/bitasm.h src/bits/bitasm-amd64.h \
 src/bits/bitasm-sse.h src/bits/revbin.h src/bits/bitswap.h \
 src/bits/bit2pow.h src/bits/bithigh.h src/bits/bithigh-edge.h \
 src/bits/bitldeq.h
src/fht/fhtdif.o: src/fht/fhtdif.cc src/aux0/cmult.h src/complextype.h \
 src/aux0/sumdiff.h src/aux0/constants.h src/aux0/sincos.h \
 src/perm/revbinpermute.h src/perm/shortrevbinpermute.h src/aux0/swap.h \
 src/fxttypes.h src/bits/revbin-upd.h src/bits/bitsperlong.h \
 src/bits/bitlow.h src/bits/bitasm.h src/bits/bitasm-amd64.h \
 src/bits/bitasm-sse.h src/bits/revbin.h src/bits/bitswap.h \
 src/bits/bit2pow.h src/bits/bithigh.h src/bits/bithigh-edge.h \
 src/bits/bitldeq.h
src/fht/cfhtdit.o: src/fht/cfhtdit.cc src/complextype.h src/fxttypes.h \
 src/aux0/cmult.h src/aux0/sumdiff.h src/aux0/constants.h \
 src/aux0/sincos.h src/perm/revbinpermute.h src/perm/shortrevbinpermute.h \
 src/aux0/swap.h src/bits/revbin-upd.h src/bits/bitsperlong.h \
 src/bits/bitlow.h src/bits/bitasm.h src/bits/bitasm-amd64.h \
 src/bits/bitasm-sse.h src/bits/revbin.h src/bits/bitswap.h \
 src/bits/bit2pow.h src/bits/bithigh.h src/bits/bithigh-edge.h \
 src/bits/bitldeq.h
src/fht/cfhtdif.o: src/fht/cfhtdif.cc src/complextype.h src/aux0/cmult.h \
 src/aux0/sumdiff.h src/aux0/constants.h src/aux0/sincos.h \
 src/perm/revbinpermute.h src/perm/shortrevbinpermute.h src/aux0/swap.h \
 src/fxttypes.h src/bits/revbin-upd.h src/bits/bitsperlong.h \
 src/bits/bitlow.h src/bits/bitasm.h src/bits/bitasm-amd64.h \
 src/bits/bitasm-sse.h src/bits/revbin.h src/bits/bitswap.h \
 src/bits/bit2pow.h src/bits/bithigh.h src/bits/bithigh-edge.h \
 src/bits/bitldeq.h
src/fht/fht0.o: src/fht/fht0.cc src/fxttypes.h src/aux0/cmult.h \
 src/complextype.h src/aux0/sumdiff.h src/aux0/sincos.h \
 src/aux0/constants.h src/perm/revbinpermute.h \
 src/perm/shortrevbinpermute.h src/aux0/swap.h src/bits/revbin-upd.h \
 src/bits/bitsperlong.h src/bits/bitlow.h src/bits/bitasm.h \
 src/bits/bitasm-amd64.h src/bits/bitasm-sse.h src/bits/revbin.h \
 src/bits/bitswap.h src/bits/bit2pow.h src/bits/bithigh.h \
 src/bits/bithigh-edge.h src/bits/bitldeq.h src/perm/revbinpermute0.h \
 src/perm/shortrevbinpermute0.h
src/fht/cfht0.o: src/fht/cfht0.cc src/complextype.h src/fxttypes.h \
 src/aux0/cmult.h src/aux0/sumdiff.h src/aux0/sincos.h \
 src/aux0/constants.h src/perm/revbinpermute.h \
 src/perm/shortrevbinpermute.h src/aux0/swap.h src/bits/revbin-upd.h \
 src/bits/bitsperlong.h src/bits/bitlow.h src/bits/bitasm.h \
 src/bits/bitasm-amd64.h src/bits/bitasm-sse.h src/bits/revbin.h \
 src/bits/bitswap.h src/bits/bit2pow.h src/bits/bithigh.h \
 src/bits/bithigh-edge.h src/bits/bitldeq.h src/perm/revbinpermute0.h \
 src/perm/shortrevbinpermute0.h
src/fht/fhtspect.o: src/fht/fhtspect.cc src/fht/fht-default.h \
 src/fht/fhtloc2.h src/fht/fht.h src/fxttypes.h src/complextype.h \
 src/fht/hartleyshift.h src/aux0/sincos.h src/aux0/sumdiff.h \
 src/aux0/constants.h src/perm/revbinpermute.h \
 src/perm/shortrevbinpermute.h src/aux0/swap.h src/bits/revbin-upd.h \
 src/bits/bitsperlong.h src/bits/bitlow.h src/bits/bitasm.h \
 src/bits/bitasm-amd64.h src/bits/bitasm-sse.h src/bits/revbin.h \
 src/bits/bitswap.h src/bits/bit2pow.h src/bits/bithigh.h \
 src/bits/bithigh-edge.h src/bits/bitldeq.h src/fht/shortfhtdifcore.h \
 src/aux0/cmult.h src/fht/shortfhtditcore.h
src/fht/skipfht.o: src/fht/skipfht.cc src/fht/fht-default.h \
 src/fht/fhtloc2.h src/fht/fht.h src/fxttypes.h src/complextype.h \
 src/fht/hartleyshift.h src/aux0/sincos.h src/aux0/sumdiff.h \
 src/aux0/constants.h src/perm/revbinpermute.h \
 src/perm/shortrevbinpermute.h src/aux0/swap.h src/bits/revbin-upd.h \
 src/bits/bitsperlong.h src/bits/bitlow.h src/bits/bitasm.h \
 src/bits/bitasm-amd64.h src/bits/bitasm-sse.h src/bits/revbin.h \
 src/bits/bitswap.h src/bits/bit2pow.h src/bits/bithigh.h \
 src/bits/bithigh-edge.h src/bits/bitldeq.h src/fht/shortfhtdifcore.h \
 src/aux0/cmult.h src/fht/shortfhtditcore.h src/aux1/copy.h
src/fht/twodimfht.o: src/fht/twodimfht.cc src/fht/fht-default.h \
 src/fht/fhtloc2.h src/fht/fht.h src/fxttypes.h src/complextype.h \
 src/fht/hartleyshift.h src/aux0/sincos.h src/aux0/sumdiff.h \
 src/aux0/constants.h src/perm/revbinpermute.h \
 src/perm/shortrevbinpermute.h src/aux0/swap.h src/bits/revbin-upd.h \
 src/bits/bitsperlong.h src/bits/bitlow.h src/bits/bitasm.h \
 src/bits/bitasm-amd64.h src/bits/bitasm-sse.h src/bits/revbin.h \
 src/bits/bitswap.h src/bits/bit2pow.h src/bits/bithigh.h \
 src/bits/bithigh-edge.h src/bits/bitldeq.h src/fht/shortfhtdifcore.h \
 src/aux0/cmult.h src/fht/shortfhtditcore.h src/fht/fht2d.h
src/fht/slowht.o: src/fht/slowht.cc src/fht/fht.h src/fxttypes.h \
 src/complextype.h src/aux0/sincos.h src/aux1/copy.h src/fxtalloca.h
src/fht/recfht2.o: src/fht/recfht2.cc src/fht/hartleyshift.h \
 src/aux0/sincos.h src/aux0/sumdiff.h src/aux0/constants.h src/fxttypes.h \
 src/aux1/copy.h src/complextype.h src/fxtalloca.h
src/chirpzt/fftarblen.o: src/chirpzt/fftarblen.cc \
 src/convolution/complexconvolution.h src/fxttypes.h src/complextype.h \
 src/chirpzt/chirpzt.h src/aux1/arith1.h src/bits/bit2pow.h \
 src/bits/bitsperlong.h src/bits/bithigh.h src/bits/bithigh-edge.h \
 src/bits/bitasm.h src/bits/bitasm-amd64.h src/bits/bitasm-sse.h \
 src/bits/bitldeq.h src/aux0/csincos.h src/aux0/sincos.h src/aux1/copy.h
src/chirpzt/fftfract.o: src/chirpzt/fftfract.cc src/chirpzt/chirpzt.h \
 src/fxttypes.h src/complextype.h src/convolution/complexconvolution.h \
 src/bits/bit2pow.h src/bits/bitsperlong.h src/bits/bithigh.h \
 src/bits/bithigh-edge.h src/bits/bitasm.h src/bits/bitasm-amd64.h \
 src/bits/bitasm-sse.h src/bits/bitldeq.h src/aux1/arith1.h \
 src/aux0/cmult.h src/aux0/sincos.h src/aux0/csincos.h src/aux1/copy.h
src/chirpzt/slowfracft.o: src/chirpzt/slowfracft.cc src/aux0/cmult.h \
 src/complextype.h src/aux0/sincos.h src/aux1/copy.h src/fxttypes.h \
 src/fxtalloca.h
src/chirpzt/slowzt.o: src/chirpzt/slowzt.cc src/fxtalloca.h \
 src/fxttypes.h src/complextype.h src/aux1/copy.h
src/dctdst/cosrot.o: src/dctdst/cosrot.cc src/fxttypes.h \
 src/aux0/sincos.h
src/dctdst/dcth.o: src/dctdst/dcth.cc src/dctdst/dctdst.h src/fxttypes.h \
 src/fht/fht-default.h src/fht/fhtloc2.h src/fht/fht.h src/complextype.h \
 src/fht/hartleyshift.h src/aux0/sincos.h src/aux0/sumdiff.h \
 src/aux0/constants.h src/perm/revbinpermute.h \
 src/perm/shortrevbinpermute.h src/aux0/swap.h src/bits/revbin-upd.h \
 src/bits/bitsperlong.h src/bits/bitlow.h src/bits/bitasm.h \
 src/bits/bitasm-amd64.h src/bits/bitasm-sse.h src/bits/revbin.h \
 src/bits/bitswap.h src/bits/bit2pow.h src/bits/bithigh.h \
 src/bits/bithigh-edge.h src/bits/bitldeq.h src/fht/shortfhtdifcore.h \
 src/aux0/cmult.h src/fht/shortfhtditcore.h src/perm/ziprev.h \
 src/perm/reverse.h src/restrict.h
src/dctdst/dct4.o: src/dctdst/dct4.cc src/dctdst/dctdst.h src/fxttypes.h \
 src/fht/fht-default.h src/fht/fhtloc2.h src/fht/fht.h src/complextype.h \
 src/fht/hartleyshift.h src/aux0/sincos.h src/aux0/sumdiff.h \
 src/aux0/constants.h src/perm/revbinpermute.h \
 src/perm/shortrevbinpermute.h src/aux0/swap.h src/bits/revbin-upd.h \
 src/bits/bitsperlong.h src/bits/bitlow.h src/bits/bitasm.h \
 src/bits/bitasm-amd64.h src/bits/bitasm-sse.h src/bits/revbin.h \
 src/bits/bitswap.h src/bits/bit2pow.h src/bits/bithigh.h \
 src/bits/bithigh-edge.h src/bits/bitldeq.h src/fht/shortfhtdifcore.h \
 src/aux0/cmult.h src/fht/shortfhtditcore.h
src/dctdst/dct.o: src/dctdst/dct.cc src/dctdst/dctdst.h src/fxttypes.h
src/dctdst/dctzapata.o: src/dctdst/dctzapata.cc src/dctdst/dctdst.h \
 src/fxttypes.h src/aux1/arith1.h src/perm/ziprev.h src/perm/reverse.h \
 src/aux0/swap.h src/perm/revbinpermute.h src/perm/shortrevbinpermute.h \
 src/bits/revbin-upd.h src/bits/bitsperlong.h src/bits/bitlow.h \
 src/bits/bitasm.h src/bits/bitasm-amd64.h src/bits/bitasm-sse.h \
 src/bits/revbin.h src/bits/bitswap.h src/bits/bit2pow.h \
 src/bits/bithigh.h src/bits/bithigh-edge.h src/bits/bitldeq.h \
 src/restrict.h
src/dctdst/dsth.o: src/dctdst/dsth.cc src/dctdst/dctdst.h src/fxttypes.h \
 src/perm/reverse.h src/aux0/swap.h
src/dctdst/dst.o: src/dctdst/dst.cc src/dctdst/dctdst.h src/fxttypes.h \
 src/fht/fht-default.h src/fht/fhtloc2.h src/fht/fht.h src/complextype.h \
 src/fht/hartleyshift.h src/aux0/sincos.h src/aux0/sumdiff.h \
 src/aux0/constants.h src/perm/revbinpermute.h \
 src/perm/shortrevbinpermute.h src/aux0/swap.h src/bits/revbin-upd.h \
 src/bits/bitsperlong.h src/bits/bitlow.h src/bits/bitasm.h \
 src/bits/bitasm-amd64.h src/bits/bitasm-sse.h src/bits/revbin.h \
 src/bits/bitswap.h src/bits/bit2pow.h src/bits/bithigh.h \
 src/bits/bithigh-edge.h src/bits/bitldeq.h src/fht/shortfhtdifcore.h \
 src/aux0/cmult.h src/fht/shortfhtditcore.h src/perm/ziprev.h \
 src/perm/reverse.h src/restrict.h
src/convolution/fftcnvl.o: src/convolution/fftcnvl.cc \
 src/realfft/realfft.h src/fxttypes.h src/convolution/realconvolution.h \
 src/aux0/cmult.h src/complextype.h src/aux0/sumdiff.h src/restrict.h
src/convolution/fftcnvla.o: src/convolution/fftcnvla.cc \
 src/convolution/realconvolution.h src/fxttypes.h src/realfft/realfft.h \
 src/aux0/cmult.h src/complextype.h
src/convolution/fftcocnvl.o: src/convolution/fftcocnvl.cc \
 src/fft/fft-default.h src/fft/fft.h src/fxttypes.h src/complextype.h \
 src/aux0/cmult.h src/aux0/sumdiff.h src/restrict.h
src/convolution/fhtcnvlcore.o: src/convolution/fhtcnvlcore.cc \
 src/convolution/fhtmulsqr.h src/restrict.h src/fxttypes.h
src/convolution/cfhtcnvlcore.o: src/convolution/cfhtcnvlcore.cc \
 src/complextype.h src/convolution/fhtmulsqr.h src/restrict.h \
 src/fxttypes.h
src/convolution/fhtcnvlacore.o: src/convolution/fhtcnvlacore.cc \
 src/convolution/fhtmulsqr.h src/restrict.h src/fxttypes.h
src/convolution/cfhtcnvlacore.o: src/convolution/cfhtcnvlacore.cc \
 src/complextype.h src/convolution/fhtmulsqr.h src/restrict.h \
 src/fxttypes.h
src/convolution/fhtcnvl.o: src/convolution/fhtcnvl.cc \
 src/convolution/realconvolution.h src/fxttypes.h src/fht/fht.h \
 src/complextype.h src/restrict.h
src/convolution/cfhtcnvl.o: src/convolution/cfhtcnvl.cc src/complextype.h \
 src/convolution/complexconvolution.h src/fxttypes.h src/fht/fht.h \
 src/restrict.h
src/convolution/fhtcnvla.o: src/convolution/fhtcnvla.cc \
 src/convolution/realconvolution.h src/fxttypes.h src/fht/fht-default.h \
 src/fht/fhtloc2.h src/fht/fht.h src/complextype.h src/fht/hartleyshift.h \
 src/aux0/sincos.h src/aux0/sumdiff.h src/aux0/constants.h \
 src/perm/revbinpermute.h src/perm/shortrevbinpermute.h src/aux0/swap.h \
 src/bits/revbin-upd.h src/bits/bitsperlong.h src/bits/bitlow.h \
 src/bits/bitasm.h src/bits/bitasm-amd64.h src/bits/bitasm-sse.h \
 src/bits/revbin.h src/bits/bitswap.h src/bits/bit2pow.h \
 src/bits/bithigh.h src/bits/bithigh-edge.h src/bits/bitldeq.h \
 src/fht/shortfhtdifcore.h src/aux0/cmult.h src/fht/shortfhtditcore.h
src/convolution/cfhtcnvla.o: src/convolution/cfhtcnvla.cc \
 src/complextype.h src/convolution/complexconvolution.h src/fxttypes.h \
 src/fht/fht-default.h src/fht/fhtloc2.h src/fht/fht.h \
 src/fht/hartleyshift.h src/aux0/sincos.h src/aux0/sumdiff.h \
 src/aux0/constants.h src/perm/revbinpermute.h \
 src/perm/shortrevbinpermute.h src/aux0/swap.h src/bits/revbin-upd.h \
 src/bits/bitsperlong.h src/bits/bitlow.h src/bits/bitasm.h \
 src/bits/bitasm-amd64.h src/bits/bitasm-sse.h src/bits/revbin.h \
 src/bits/bitswap.h src/bits/bit2pow.h src/bits/bithigh.h \
 src/bits/bithigh-edge.h src/bits/bitldeq.h src/fht/shortfhtdifcore.h \
 src/aux0/cmult.h src/fht/shortfhtditcore.h
src/convolution/fhtloccnvl.o: src/convolution/fhtloccnvl.cc \
 src/convolution/realconvolution.h src/fxttypes.h src/fht/fht.h \
 src/complextype.h src/fht/fhtloc2.h src/fht/hartleyshift.h \
 src/aux0/sincos.h src/aux0/sumdiff.h src/aux0/constants.h \
 src/perm/revbinpermute.h src/perm/shortrevbinpermute.h src/aux0/swap.h \
 src/bits/revbin-upd.h src/bits/bitsperlong.h src/bits/bitlow.h \
 src/bits/bitasm.h src/bits/bitasm-amd64.h src/bits/bitasm-sse.h \
 src/bits/revbin.h src/bits/bitswap.h src/bits/bit2pow.h \
 src/bits/bithigh.h src/bits/bithigh-edge.h src/bits/bitldeq.h \
 src/fht/shortfhtdifcore.h src/aux0/cmult.h src/fht/shortfhtditcore.h \
 src/restrict.h
src/convolution/fhtloccnvla.o: src/convolution/fhtloccnvla.cc \
 src/convolution/realconvolution.h src/fxttypes.h src/fht/fhtloc2.h \
 src/fht/fht.h src/complextype.h src/fht/hartleyshift.h src/aux0/sincos.h \
 src/aux0/sumdiff.h src/aux0/constants.h src/perm/revbinpermute.h \
 src/perm/shortrevbinpermute.h src/aux0/swap.h src/bits/revbin-upd.h \
 src/bits/bitsperlong.h src/bits/bitlow.h src/bits/bitasm.h \
 src/bits/bitasm-amd64.h src/bits/bitasm-sse.h src/bits/revbin.h \
 src/bits/bitswap.h src/bits/bit2pow.h src/bits/bithigh.h \
 src/bits/bithigh-edge.h src/bits/bitldeq.h src/fht/shortfhtdifcore.h \
 src/aux0/cmult.h src/fht/shortfhtditcore.h
src/convolution/fhtnegacnvl.o: src/convolution/fhtnegacnvl.cc \
 src/convolution/weightedconvolution.h src/fxttypes.h src/complextype.h \
 src/restrict.h src/fht/fht-default.h src/fht/fhtloc2.h src/fht/fht.h \
 src/fht/hartleyshift.h src/aux0/sincos.h src/aux0/sumdiff.h \
 src/aux0/constants.h src/perm/revbinpermute.h \
 src/perm/shortrevbinpermute.h src/aux0/swap.h src/bits/revbin-upd.h \
 src/bits/bitsperlong.h src/bits/bitlow.h src/bits/bitasm.h \
 src/bits/bitasm-amd64.h src/bits/bitasm-sse.h src/bits/revbin.h \
 src/bits/bitswap.h src/bits/bit2pow.h src/bits/bithigh.h \
 src/bits/bithigh-edge.h src/bits/bitldeq.h src/fht/shortfhtdifcore.h \
 src/aux0/cmult.h src/fht/shortfhtditcore.h src/convolution/fhtmulsqr.h
src/convolution/twodimfhtcnvl.o: src/convolution/twodimfhtcnvl.cc \
 src/fxttypes.h src/aux0/sumdiff.h src/aux1/arith1.h
src/convolution/slowcocnvl.o: src/convolution/slowcocnvl.cc \
 src/aux0/cmult.h src/complextype.h src/fxtalloca.h src/fxttypes.h \
 src/aux1/copy.h
src/convolution/weightedconv.o: src/convolution/weightedconv.cc \
 src/convolution/weightedconvolution.h src/fxttypes.h src/complextype.h \
 src/restrict.h src/fft/fft.h src/aux0/cmult.h
src/convolution/matrixfftcnvl.o: src/convolution/matrixfftcnvl.cc \
 src/convolution/weightedconvolution.h src/fxttypes.h src/complextype.h \
 src/restrict.h src/convolution/realconvolution.h src/fft/matrixfft.h \
 src/aux0/ldn2rc.h src/bits/bit2pow.h src/bits/bitsperlong.h \
 src/bits/bithigh.h src/bits/bithigh-edge.h src/bits/bitasm.h \
 src/bits/bitasm-amd64.h src/bits/bitasm-sse.h src/bits/bitldeq.h \
 src/aux1/copy.h
src/convolution/matrixfftcnvla.o: src/convolution/matrixfftcnvla.cc \
 src/convolution/realconvolution.h src/fxttypes.h \
 src/convolution/weightedconvolution.h src/complextype.h src/restrict.h \
 src/fft/matrixfft.h src/fht/fht-default.h src/fht/fhtloc2.h \
 src/fht/fht.h src/fht/hartleyshift.h src/aux0/sincos.h \
 src/aux0/sumdiff.h src/aux0/constants.h src/perm/revbinpermute.h \
 src/perm/shortrevbinpermute.h src/aux0/swap.h src/bits/revbin-upd.h \
 src/bits/bitsperlong.h src/bits/bitlow.h src/bits/bitasm.h \
 src/bits/bitasm-amd64.h src/bits/bitasm-sse.h src/bits/revbin.h \
 src/bits/bitswap.h src/bits/bit2pow.h src/bits/bithigh.h \
 src/bits/bithigh-edge.h src/bits/bitldeq.h src/fht/shortfhtdifcore.h \
 src/aux0/cmult.h src/fht/shortfhtditcore.h src/aux0/ldn2rc.h \
 src/aux1/copy.h
src/convolution/matrixfftcocnvla.o: src/convolution/matrixfftcocnvla.cc \
 src/convolution/complexconvolution.h src/fxttypes.h src/complextype.h \
 src/fft/matrixfft.h src/fft/fft.h src/fht/fht.h src/aux0/ldn2rc.h \
 src/bits/bit2pow.h src/bits/bitsperlong.h src/bits/bithigh.h \
 src/bits/bithigh-edge.h src/bits/bitasm.h src/bits/bitasm-amd64.h \
 src/bits/bitasm-sse.h src/bits/bitldeq.h src/perm/revbinpermute.h \
 src/perm/shortrevbinpermute.h src/aux0/swap.h src/bits/revbin-upd.h \
 src/bits/bitlow.h src/bits/revbin.h src/bits/bitswap.h \
 src/perm/revbinpermute0.h src/perm/shortrevbinpermute0.h
src/correlation/fftcocorr.o: src/correlation/fftcocorr.cc \
 src/fft/fft-default.h src/fft/fft.h src/fxttypes.h src/complextype.h \
 src/aux0/cmult.h src/aux0/sumdiff.h src/restrict.h
src/correlation/fftcorr.o: src/correlation/fftcorr.cc \
 src/realfft/realfft.h src/fxttypes.h src/aux0/cmult.h src/complextype.h \
 src/aux0/sumdiff.h
src/correlation/fhtcorr.o: src/correlation/fhtcorr.cc \
 src/correlation/correlation.h src/fxttypes.h \
 src/convolution/realconvolution.h src/fht/fht-default.h \
 src/fht/fhtloc2.h src/fht/fht.h src/complextype.h src/fht/hartleyshift.h \
 src/aux0/sincos.h src/aux0/sumdiff.h src/aux0/constants.h \
 src/perm/revbinpermute.h src/perm/shortrevbinpermute.h src/aux0/swap.h \
 src/bits/revbin-upd.h src/bits/bitsperlong.h src/bits/bitlow.h \
 src/bits/bitasm.h src/bits/bitasm-amd64.h src/bits/bitasm-sse.h \
 src/bits/revbin.h src/bits/bitswap.h src/bits/bit2pow.h \
 src/bits/bithigh.h src/bits/bithigh-edge.h src/bits/bitldeq.h \
 src/fht/shortfhtdifcore.h src/aux0/cmult.h src/fht/shortfhtditcore.h \
 src/restrict.h src/aux1/arith1.h src/perm/reverse.h
src/correlation/slowcocorr.o: src/correlation/slowcocorr.cc \
 src/aux0/cmult.h src/complextype.h src/aux1/copy.h src/fxttypes.h \
 src/fxtalloca.h
src/walsh/walsheigen.o: src/walsh/walsheigen.cc src/walsh/walsh-basis.h \
 src/bits/parity.h src/fxttypes.h src/bits/bitsperlong.h \
 src/bits/graycode.h src/bits/bitasm.h src/bits/bitasm-amd64.h \
 src/bits/bitasm-sse.h src/bits/grsnegative.h src/bits/revbin.h \
 src/bits/bitswap.h src/bits/bit2pow.h src/bits/bithigh.h \
 src/bits/bithigh-edge.h src/bits/bitldeq.h
src/walsh/slant.o: src/walsh/slant.cc src/fxttypes.h \
 src/perm/graypermute.h src/bits/graycode.h src/bits/bitsperlong.h \
 src/bits/bit2pow.h src/bits/bithigh.h src/bits/bithigh-edge.h \
 src/bits/bitasm.h src/bits/bitasm-amd64.h src/bits/bitasm-sse.h \
 src/bits/bitldeq.h src/bits/bitsubset.h src/restrict.h src/perm/ziprev.h \
 src/perm/reverse.h src/aux0/swap.h src/perm/revbinpermute.h \
 src/perm/shortrevbinpermute.h src/bits/revbin-upd.h src/bits/bitlow.h \
 src/bits/revbin.h src/bits/bitswap.h src/walsh/walshwak.h \
 src/walsh/walshwak2.h src/walsh/walshwak4.h src/walsh/shortwalshwakdif.h \
 src/aux0/sumdiff.h src/walsh/shortwalshwakdit.h src/walsh/walshwak8.h \
 src/walsh/walshwakloc2.h
src/wavelet/wavelet.o: src/wavelet/wavelet.cc src/wavelet/wavelet.h \
 src/fxttypes.h src/wavelet/waveletfilter.h src/aux1/copy.h \
 src/complextype.h src/fxtalloca.h
src/wavelet/invwavelet.o: src/wavelet/invwavelet.cc src/wavelet/wavelet.h \
 src/fxttypes.h src/wavelet/waveletfilter.h src/aux1/copy.h \
 src/complextype.h src/fxtalloca.h
src/wavelet/daubechies.o: src/wavelet/daubechies.cc src/fxttypes.h \
 src/array-len.h
src/wavelet/harmonic-wavelet.o: src/wavelet/harmonic-wavelet.cc \
 src/fft/fft-default.h src/fft/fft.h src/fxttypes.h src/complextype.h \
 src/aux1/arith1.h
src/mod/mod.o: src/mod/mod.cc src/aux0/sign.h src/mod/mod.h \
 src/fxttypes.h src/mod/mtypes.h src/mod/numtheory.h src/mod/modarith.h \
 src/aux0/ipow.h src/aux0/gcd.h src/aux0/swap.h src/mod/factor.h \
 src/bits/bitsperlong.h src/fxtio.h
src/mod/modinit.o: src/mod/modinit.cc src/fxttypes.h src/mod/mod.h \
 src/mod/mtypes.h src/mod/numtheory.h src/mod/modarith.h src/aux0/ipow.h \
 src/aux0/gcd.h src/aux0/swap.h src/mod/factor.h src/bits/bitsperlong.h \
 src/fxtio.h
src/mod/modinfo.o: src/mod/modinfo.cc src/fxttypes.h src/mod/mod.h \
 src/mod/mtypes.h src/mod/numtheory.h src/mod/modarith.h src/aux0/ipow.h \
 src/aux0/gcd.h src/aux0/swap.h src/mod/factor.h src/bits/bitsperlong.h \
 src/fxtio.h src/bits/bit2pow.h src/bits/bithigh.h \
 src/bits/bithigh-edge.h src/bits/bitasm.h src/bits/bitasm-amd64.h \
 src/bits/bitasm-sse.h src/bits/bitldeq.h src/aux0/sign.h
src/mod/maxorder.o: src/mod/maxorder.cc src/mod/factor.h src/mod/mtypes.h \
 src/fxttypes.h src/bits/bitsperlong.h src/fxtio.h src/mod/primes.h \
 src/mod/numtheory.h src/aux0/gcd.h src/aux0/swap.h
src/mod/primes.o: src/mod/primes.cc src/mod/mtypes.h src/fxttypes.h \
 src/mod/isqrt.h src/mod/primes.h src/ds/bitarray.h src/bits/bitcount.h \
 src/bits/bitsperlong.h src/bits/bitasm.h src/bits/bitasm-amd64.h \
 src/bits/bitasm-sse.h
src/mod/perfpow.o: src/mod/perfpow.cc src/bits/bitsperlong.h \
 src/mod/isqrt.h src/bits/tinyfactors.h src/fxttypes.h src/ds/bitarray.h \
 src/bits/bitcount.h src/bits/bitasm.h src/bits/bitasm-amd64.h \
 src/bits/bitasm-sse.h
src/mod/eratosthenes.o: src/mod/eratosthenes.cc src/ds/bitarray.h \
 src/bits/bitcount.h src/fxttypes.h src/bits/bitsperlong.h \
 src/bits/bitasm.h src/bits/bitasm-amd64.h src/bits/bitasm-sse.h \
 src/mod/isqrt.h
src/mod/order.o: src/mod/order.cc src/fxttypes.h src/mod/modarith.h \
 src/aux0/ipow.h src/aux0/gcd.h src/aux0/swap.h src/mod/mtypes.h \
 src/mod/factor.h src/bits/bitsperlong.h src/fxtio.h
src/mod/factor.o: src/mod/factor.cc src/mod/mtypes.h src/fxttypes.h \
 src/mod/factor.h src/bits/bitsperlong.h src/fxtio.h src/mod/primes.h \
 src/mod/modarith.h src/aux0/ipow.h src/aux0/gcd.h src/aux0/swap.h \
 src/fxtalloca.h src/jjassert.h
src/mod/factormake.o: src/mod/factormake.cc src/mod/factor.h \
 src/mod/mtypes.h src/fxttypes.h src/bits/bitsperlong.h src/fxtio.h \
 src/mod/primes.h src/mod/isqrt.h src/aux0/ipow.h
src/mod/cyclic.o: src/mod/cyclic.cc src/mod/factor.h src/mod/mtypes.h \
 src/fxttypes.h src/bits/bitsperlong.h src/fxtio.h
src/mod/chinese.o: src/mod/chinese.cc src/mod/modarith.h src/fxttypes.h \
 src/aux0/ipow.h src/aux0/gcd.h src/aux0/swap.h src/mod/mtypes.h \
 src/mod/factor.h src/bits/bitsperlong.h src/fxtio.h
src/mod/quadresidue.o: src/mod/quadresidue.cc src/mod/factor.h \
 src/mod/mtypes.h src/fxttypes.h src/bits/bitsperlong.h src/fxtio.h \
 src/mod/numtheory.h
src/mod/sqrtmod.o: src/mod/sqrtmod.cc src/mod/modarith.h src/fxttypes.h \
 src/aux0/ipow.h src/aux0/gcd.h src/aux0/swap.h src/mod/mtypes.h \
 src/mod/factor.h src/bits/bitsperlong.h src/fxtio.h src/mod/numtheory.h \
 src/mod/primes.h src/fxtalloca.h
src/mod/kronecker.o: src/mod/kronecker.cc src/mod/mtypes.h src/fxttypes.h
src/mod/rabinmiller.o: src/mod/rabinmiller.cc src/mod/primes.h \
 src/fxttypes.h src/mod/mtypes.h src/mod/modarith.h src/aux0/ipow.h \
 src/aux0/gcd.h src/aux0/swap.h src/mod/factor.h src/bits/bitsperlong.h \
 src/fxtio.h
src/mod/euler-phi.o: src/mod/euler-phi.cc src/mod/numtheory.h \
 src/fxttypes.h src/mod/mtypes.h src/mod/factor.h src/bits/bitsperlong.h \
 src/fxtio.h src/aux0/ipow.h
src/mod/mersenne-exponents.o: src/mod/mersenne-exponents.cc \
 src/fxttypes.h src/array-len.h
src/mod/mersenne-factors.o: src/mod/mersenne-factors.cc src/mod/mtypes.h \
 src/fxttypes.h
src/mod/chebyshev1.o: src/mod/chebyshev1.cc src/mod/modarith.h \
 src/fxttypes.h src/aux0/ipow.h src/aux0/gcd.h src/aux0/swap.h \
 src/mod/mtypes.h src/mod/factor.h src/bits/bitsperlong.h src/fxtio.h
src/mod/chebyshev2.o: src/mod/chebyshev2.cc src/mod/modarith.h \
 src/fxttypes.h src/aux0/ipow.h src/aux0/gcd.h src/aux0/swap.h \
 src/mod/mtypes.h src/mod/factor.h src/bits/bitsperlong.h src/fxtio.h
src/ntt/nttdit2.o: src/ntt/nttdit2.cc src/fxttypes.h src/ntt/ntt.h \
 src/mod/mod.h src/mod/mtypes.h src/mod/numtheory.h src/mod/modarith.h \
 src/aux0/ipow.h src/aux0/gcd.h src/aux0/swap.h src/mod/factor.h \
 src/bits/bitsperlong.h src/fxtio.h src/restrict.h \
 src/perm/revbinpermute.h src/perm/shortrevbinpermute.h \
 src/bits/revbin-upd.h src/bits/bitlow.h src/bits/bitasm.h \
 src/bits/bitasm-amd64.h src/bits/bitasm-sse.h src/bits/revbin.h \
 src/bits/bitswap.h src/bits/bit2pow.h src/bits/bithigh.h \
 src/bits/bithigh-edge.h src/bits/bitldeq.h src/aux0/sumdiff.h
src/ntt/nttdif2.o: src/ntt/nttdif2.cc src/fxttypes.h src/ntt/ntt.h \
 src/mod/mod.h src/mod/mtypes.h src/mod/numtheory.h src/mod/modarith.h \
 src/aux0/ipow.h src/aux0/gcd.h src/aux0/swap.h src/mod/factor.h \
 src/bits/bitsperlong.h src/fxtio.h src/restrict.h \
 src/perm/revbinpermute.h src/perm/shortrevbinpermute.h \
 src/bits/revbin-upd.h src/bits/bitlow.h src/bits/bitasm.h \
 src/bits/bitasm-amd64.h src/bits/bitasm-sse.h src/bits/revbin.h \
 src/bits/bitswap.h src/bits/bit2pow.h src/bits/bithigh.h \
 src/bits/bithigh-edge.h src/bits/bitldeq.h src/aux0/sumdiff.h
src/ntt/nttdit4.o: src/ntt/nttdit4.cc src/fxttypes.h src/ntt/ntt.h \
 src/mod/mod.h src/mod/mtypes.h src/mod/numtheory.h src/mod/modarith.h \
 src/aux0/ipow.h src/aux0/gcd.h src/aux0/swap.h src/mod/factor.h \
 src/bits/bitsperlong.h src/fxtio.h src/restrict.h \
 src/perm/revbinpermute.h src/perm/shortrevbinpermute.h \
 src/bits/revbin-upd.h src/bits/bitlow.h src/bits/bitasm.h \
 src/bits/bitasm-amd64.h src/bits/bitasm-sse.h src/bits/revbin.h \
 src/bits/bitswap.h src/bits/bit2pow.h src/bits/bithigh.h \
 src/bits/bithigh-edge.h src/bits/bitldeq.h src/aux0/sumdiff.h
src/ntt/nttdif4.o: src/ntt/nttdif4.cc src/fxttypes.h src/ntt/ntt.h \
 src/mod/mod.h src/mod/mtypes.h src/mod/numtheory.h src/mod/modarith.h \
 src/aux0/ipow.h src/aux0/gcd.h src/aux0/swap.h src/mod/factor.h \
 src/bits/bitsperlong.h src/fxtio.h src/restrict.h \
 src/perm/revbinpermute.h src/perm/shortrevbinpermute.h \
 src/bits/revbin-upd.h src/bits/bitlow.h src/bits/bitasm.h \
 src/bits/bitasm-amd64.h src/bits/bitasm-sse.h src/bits/revbin.h \
 src/bits/bitswap.h src/bits/bit2pow.h src/bits/bithigh.h \
 src/bits/bithigh-edge.h src/bits/bitldeq.h src/aux0/sumdiff.h
src/ntt/nttlearn.o: src/ntt/nttlearn.cc src/fxttypes.h src/mod/mod.h \
 src/mod/mtypes.h src/mod/numtheory.h src/mod/modarith.h src/aux0/ipow.h \
 src/aux0/gcd.h src/aux0/swap.h src/mod/factor.h src/bits/bitsperlong.h \
 src/fxtio.h src/perm/revbinpermute.h src/perm/shortrevbinpermute.h \
 src/bits/revbin-upd.h src/bits/bitlow.h src/bits/bitasm.h \
 src/bits/bitasm-amd64.h src/bits/bitasm-sse.h src/bits/revbin.h \
 src/bits/bitswap.h src/bits/bit2pow.h src/bits/bithigh.h \
 src/bits/bithigh-edge.h src/bits/bitldeq.h
src/ntt/nttcnvl.o: src/ntt/nttcnvl.cc src/fxttypes.h src/restrict.h \
 src/aux1/arith1.h src/ntt/ntt.h src/mod/mod.h src/mod/mtypes.h \
 src/mod/numtheory.h src/mod/modarith.h src/aux0/ipow.h src/aux0/gcd.h \
 src/aux0/swap.h src/mod/factor.h src/bits/bitsperlong.h src/fxtio.h \
 src/jjassert.h
src/ntt/slownttcnvl.o: src/ntt/slownttcnvl.cc src/mod/mod.h \
 src/fxttypes.h src/mod/mtypes.h src/mod/numtheory.h src/mod/modarith.h \
 src/aux0/ipow.h src/aux0/gcd.h src/aux0/swap.h src/mod/factor.h \
 src/bits/bitsperlong.h src/fxtio.h src/ntt/ntt.h src/restrict.h \
 src/fxtalloca.h src/aux1/copy.h src/complextype.h
src/ntt/slowntt.o: src/ntt/slowntt.cc src/mod/mod.h src/fxttypes.h \
 src/mod/mtypes.h src/mod/numtheory.h src/mod/modarith.h src/aux0/ipow.h \
 src/aux0/gcd.h src/aux0/swap.h src/mod/factor.h src/bits/bitsperlong.h \
 src/fxtio.h src/bits/bit2pow.h src/bits/bithigh.h \
 src/bits/bithigh-edge.h src/bits/bitasm.h src/bits/bitasm-amd64.h \
 src/bits/bitasm-sse.h src/bits/bitldeq.h src/fxtalloca.h
