#! /usr/bin/env zsh

x=$(\ls -1tr $(find demo -name \*-out.txt) | tail -1)
print -- $x

y=/tmp/$(basename $x)
print -- $y

diff $x $y

exit;
###########################
