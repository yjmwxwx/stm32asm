#! /usr/bin/env bash

grep -En '^[ ]+[a-zA-Z]+ +[a-zA-Z0-9]+\[[^0-9]+\]' $FH
grep -En '^[ ]+[a-zA-Z]+ +[a-zA-Z0-9]+\[[^0-9]+\]' demo/*/*.cc


