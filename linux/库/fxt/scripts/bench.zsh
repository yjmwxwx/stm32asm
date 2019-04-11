#! /usr/bin/env zsh

export LC_ALL=C ## for sorting
DEMOBIN=./bin

FXT_EXTRA_FLAGS='-Wno-conversion -Wno-unused'

## add options as follows:
#FXT_EXTRA_FLAGS="$FXT_EXTRA_FLAGS -march=amdfam10 -mtune=amdfam10"
#FXT_EXTRA_FLAGS="$FXT_EXTRA_FLAGS -mtune=generic"


## No translations, please:
export LC_ALL=C

## use zsh's built-in time command:
export TIMEFMT='%J %U user %S system %P cpu %E total';
## default is ='%J %U user %S system %P cpu %*E total';
TIMER=time
#
## use /usr/bin/time:
#export TIME='%C %U user %S system %P cpu %e total';
#TIMER=/usr/bin/time


#################################

## system name:
    uname -a
    echo
    if test -n "$CXX"; then
        # warning: will use ccache if, e.g, $CXX='ccache /usr/lib/ccache/g++'
        # unset CXX  # solves this
        $CXX --version | head -1
    else
        c++ --version | head -1
    fi
    echo

if [ -z "$PAT" ]; then
    ## full suite, incl. recompilation of the lib and CPU-info

    PAT='.'; ## this matches all files

    ## CPU info:
    cat /proc/cpuinfo
    echo -e '\n\n\n'

    ## compile the library as a benchmark:
    make clobber  &>/dev/null
    make cat  &>/dev/null
    echo "Compiling the FXT library:"
    ${TIMER} make -s lib FXT_EXTRA_FLAGS=${FXT_EXTRA_FLAGS}
    echo -e '\n\n\n'

else
    ## do not recompile lib when PAT was supplied:
    echo "Benchmark with PAT=[${PAT}]:"
fi


## Run FXT benchmarks (for all files whose filename contain the pattern PAT).
## Consider only files having a 'BENCHARGS' line:
DD=$(grep -l 'BENCHARGS' demo/*/*-demo.cc demo/*/*-bench.cc | sort)

for d in ${=DD}; do  ## loop over files
#    echo " :: d=[$d]"
#    echo " :: d=[${d}] pat=[${PAT}] dpat=[${d/${PAT}/}]";

    if [ "${d}" \!= "${d/${PAT}/}" ]; then  ## pattern matches
        echo '------------------------------------------------------------';
        make -s  1demo DSRC=$d DEMOFLAGS='-DTIMING -DFXT_SILENT_NXARG' FXT_EXTRA_FLAGS=${FXT_EXTRA_FLAGS} RUNDEMO=true
        AA=$(grep 'BENCHARGS' $d | cut -d= -f2- | tr ' ' '@')
        for aa in ${=AA}; do  ## loop over benchmarks in one file
            a=$(echo $aa | tr '@' ' ' );
            echo "----- args=$a"
            eval ${TIMER} ${DEMOBIN} ${=a}
            echo -en '\n'
        done
        echo -en '\n\n'
    fi
done


exit 0;
#################################
