################## FXT files.mk ##########################

#-------------------------------------

NONSRCDIRS= \
./data \
./demo \
./doc \
./include \
./scripts \
./simplfft \
./test \

SHFXTSRCDIRS= \
./aux0 \
./aux1 \
./aux2 \
./bits \
./bpol \
./bmat \
./chirpzt \
./comb \
./graph \
./convolution \
./correlation \
./dctdst \
./ds \
./fft \
./fht \
./haar \
./mod \
./ntt \
./perm \
./realfft \
./sort \
./walsh \
./wavelet \
./matrix \

FXTSRCDIRS=$(shell find src -mindepth 1 -maxdepth 1 -type d)
#FXTSRCDIRS=$(shell find src -mindepth 1 -maxdepth 1 -type d -a \! -name 'bucket')
FXTHDRS=$(shell find src -maxdepth 2 -name \[a-zA-Z]\*.h)

#-------------------------------------


AUXOBJS= \
src/bits/revbin-upd.o \
src/bits/revbin-tab.o \
src/bits/lin2hilbert.o \
src/bits/tinyfactors.o \
src/bits/print-bin.o \
src/bits/print-bindiff.o \
src/bits/print-bitset.o \
src/bits/crc32.o \
src/bits/crc64.o \
src/bits/bitcount-v.o \
\
src/bpol/bitpol-print.o \
src/bpol/bitpol2lhca.o \
src/bpol/bitpol-order.o \
\
src/bpol/primpoly-rand.o \
src/bpol/primpoly-lowbit.o \
src/bpol/primpoly-minweight.o \
src/bpol/normal-irredpoly.o \
src/bpol/normal-primpoly.o \
src/bpol/lhcarule-minweight.o \
\
src/bpol/bitpol-irred-ben-or.o \
src/bpol/bitpol-irred-rabin.o \
src/bpol/bitpol-spi.o \
\
src/bpol/normal-mult.o \
src/bpol/bitpol-squarefree.o \
src/bpol/bitpol-normal.o \
src/bpol/num-bitpol.o \
src/bpol/berlekamp.o \
src/bpol/bitpol-factor.o \
src/bpol/bitpolmod-solvequadratic.o \
src/bpol/bitpolmod-minpoly.o \
src/bpol/normalpoly-dual.o \
src/bpol/gf2n.o \
src/bpol/gf2n-trace.o \
src/bpol/gf2n-solvequadratic.o \
src/bpol/gf2n-minpoly.o \
src/bpol/gf2n-order.o \
\
src/bmat/bitmat-mult-mm.o \
src/bmat/bitmat-transpose.o \
src/bmat/bitmat-inverse.o \
src/bmat/bitmat-nullspace.o \
src/bmat/bitmat-hessenberg.o \
src/bmat/bitmat-charpoly.o \
src/bmat/bitmat-kronecker.o \
src/bmat/bitmat-print.o \
\
src/aux0/version.o \
src/aux0/randf.o \
src/aux0/print-fixed.o \
src/aux0/jjassert.o \
src/aux0/tex-line.o \
\
src/aux1/bytescan.o \
src/aux1/num2str.o \
\
src/sort/radixsort.o \
src/ds/bitarray.o \


PERMOBJS= \
src/perm/zip.o \
src/perm/permq.o \
src/perm/printcycles.o \
src/perm/perminvert.o \
src/perm/permcompose.o \
src/perm/perm2ccf.o \


COMBOBJS= \
src/comb/fact2perm.o \
src/comb/big-fact2perm.o \
src/comb/fact2num.o \
src/comb/num2perm.o \
src/comb/fact2perm-rev.o \
src/comb/fact2perm-swp.o \
src/comb/fact2perm-rot.o \
src/comb/fact2cyclic.o \
src/comb/print-perm.o \
\
src/comb/catalan.o \
src/comb/print-catalan-step-rgs-aa.o \
src/comb/print-catalan-path-aa.o \
src/comb/paren-string-to-rgs.o \
src/comb/partition-conj.o \
src/comb/cayley-perm.o \
src/comb/partition.o \
src/comb/partition-gen.o \
src/comb/partition-rgs-lex.o \
src/comb/setpart.o \
src/comb/print-zero-map-rgs.o \
src/comb/setpart-rgs-gray.o \
src/comb/combination-rec.o \
src/comb/delta2gray.o \
src/comb/monotonic-gray.o \
src/comb/acgray.o \
src/comb/test-gray.o \
src/comb/print-gray.o \
src/comb/stringsubst.o \
src/comb/num-necklaces.o \
src/comb/composition-rank.o \
src/comb/composition-nz-rank.o \
src/comb/composition-nz-minc.o \
src/comb/print-composition-aa.o \
src/comb/print-composition-by-sorts.o \
src/comb/print-partition-aa.o \
src/comb/print-partition-conj.o \
src/comb/print-composition-unimodal.o \
src/comb/binary-huffman.o \
src/comb/ksubset-rec.o \
src/comb/print-set.o \
src/comb/print-mset.o \
src/comb/print-setpart.o \
src/comb/print-vec.o \
\
src/comb/print-arrangement-rgs-perm.o \
\
src/comb/print-mixedradix.o \
src/comb/mixedradix2num.o \
src/comb/mixedradix-init.o \
\
src/comb/mset-perm-lex-rec.o \
src/comb/print-young-tab-rgs-aa.o \
\
src/comb/tree-lev-seq-aux.o \
src/comb/ordered-tree-branches.o \
src/comb/ordered-tree-branching-seq.o \
\
src/graph/digraph.o \
src/graph/digraph-paths.o \
src/graph/search-digraph.o \
src/graph/search-digraph-cond.o \
src/graph/search-digraph-trylucky.o \
src/graph/print-path.o \
\
src/graph/mk-complete-digraph.o \
src/graph/mk-debruijn-digraph.o \
src/graph/mk-gray-digraph.o \
src/graph/mk-paren-gray-digraph.o \
src/graph/mk-fibrep-gray-digraph.o \
src/graph/mk-mtl-digraph.o \
src/graph/mk-perm-gray-digraph.o \
src/graph/mk-perm-pref-rev-digraph.o \
src/graph/mk-perm-pref-rot-digraph.o \
src/graph/mk-lyndon-gray-digraph.o \
src/graph/lyndon-cmp.o \



FFTOBJS= \
src/fft/fftdit2.o \
src/fft/fftdif2.o \
src/fft/fftdit4l.o \
src/fft/fftdif4l.o \
src/fft/fftdit4.o \
src/fft/cfftdit4.o \
src/fft/fftdif4.o \
src/fft/cfftdif4.o \
src/fft/fft8ditcore.o \
src/fft/fft8difcore.o \
src/fft/fft9.o \
src/fft/fftsplitradix.o \
src/fft/cfftsplitradix.o \
src/fft/fhtfft.o \
src/fft/fhtcfft.o \
src/fft/fftspect.o \
src/fft/fouriershift.o \
src/fft/skipfft.o \
src/fft/twodimfft.o \
src/fft/cfftwrap.o \
src/fft/slowft.o \
src/fft/recfft2.o \
src/fft/weightedfft.o \
src/fft/columnffts.o \
src/fft/rowffts.o \
src/fft/rowcnvls.o \
src/fft/matrixfft.o \


CONVOBJS= \
src/convolution/fftcnvl.o \
src/convolution/fftcnvla.o \
src/convolution/fftcocnvl.o \
src/convolution/fhtcnvlcore.o \
src/convolution/cfhtcnvlcore.o \
src/convolution/fhtcnvlacore.o \
src/convolution/cfhtcnvlacore.o \
src/convolution/fhtcnvl.o \
src/convolution/cfhtcnvl.o \
src/convolution/fhtcnvla.o \
src/convolution/cfhtcnvla.o \
src/convolution/fhtloccnvl.o \
src/convolution/fhtloccnvla.o \
src/convolution/fhtnegacnvl.o \
src/convolution/twodimfhtcnvl.o \
src/convolution/slowcocnvl.o \
src/convolution/weightedconv.o \
src/convolution/matrixfftcnvl.o \
src/convolution/matrixfftcnvla.o \
src/convolution/matrixfftcocnvla.o \

CORROBJS= \
src/correlation/fftcocorr.o \
src/correlation/fftcorr.o \
src/correlation/fhtcorr.o \
src/correlation/slowcocorr.o \


REALFFTOBJS= \
src/realfft/realfftbyfht.o \
src/realfft/realfftwrap.o \
src/realfft/realffteasyord.o \
src/realfft/realfftsplitradix.o \
src/realfft/skiprealfft.o \

OTHERFFTOBJS= \
src/chirpzt/fftarblen.o \
src/chirpzt/fftfract.o \
src/chirpzt/slowfracft.o \
src/chirpzt/slowzt.o \

FHTOBJS= \
src/fht/fhtdit2.o \
src/fht/fhtdif2.o \
src/fht/fhtdit.o \
src/fht/fhtdif.o \
src/fht/cfhtdit.o \
src/fht/cfhtdif.o \
src/fht/fht0.o \
src/fht/cfht0.o \
src/fht/fhtspect.o \
src/fht/skipfht.o \
src/fht/twodimfht.o \
src/fht/slowht.o \
src/fht/recfht2.o \
#src/fht/fhttable.o \

DCTDSTOBJS= \
src/dctdst/cosrot.o \
src/dctdst/dcth.o \
src/dctdst/dct4.o \
src/dctdst/dct.o \
src/dctdst/dctzapata.o \
src/dctdst/dsth.o \
src/dctdst/dst.o \

WALSHOBJS= \
src/walsh/walsheigen.o \
src/walsh/slant.o \

HAAROBJS= \


WAVELETOBJS= \
src/wavelet/wavelet.o \
src/wavelet/invwavelet.o \
src/wavelet/daubechies.o \
src/wavelet/harmonic-wavelet.o \

MODOBJS= \
src/mod/mod.o \
src/mod/modinit.o \
src/mod/modinfo.o \
src/mod/maxorder.o \
src/mod/primes.o \
src/mod/perfpow.o \
src/mod/eratosthenes.o \
src/mod/order.o \
src/mod/factor.o \
src/mod/factormake.o \
src/mod/cyclic.o \
src/mod/chinese.o \
src/mod/quadresidue.o \
src/mod/sqrtmod.o \
src/mod/kronecker.o \
src/mod/rabinmiller.o \
src/mod/euler-phi.o \
src/mod/mersenne-exponents.o \
src/mod/mersenne-factors.o \
src/mod/chebyshev1.o \
src/mod/chebyshev2.o \

NTTOBJS= \
src/ntt/nttdit2.o \
src/ntt/nttdif2.o \
src/ntt/nttdit4.o \
src/ntt/nttdif4.o \
src/ntt/nttlearn.o \
src/ntt/nttcnvl.o \
src/ntt/slownttcnvl.o \
src/ntt/slowntt.o \

#
OBJS =
OBJS += $(AUXOBJS)
OBJS += $(COMBOBJS)
OBJS += $(PERMOBJS)
OBJS += $(FFTOBJS)
OBJS += $(REALFFTOBJS)
OBJS += $(FHTOBJS)
OBJS += $(OTHERFFTOBJS)
#OBJS += $(MATRIXOBJS)
OBJS += $(DCTDSTOBJS)
OBJS += $(CONVOBJS)
OBJS += $(CORROBJS)
OBJS += $(WALSHOBJS)
OBJS += $(HAAROBJS)
OBJS += $(WAVELETOBJS)
OBJS += $(WEIGHTEDOBJS)
OBJS += $(MODOBJS)
OBJS += $(NTTOBJS)


#
SRC=$(OBJS:.o=.cc)

#-------------------------------------

################## end FXT files.mk ##########################
