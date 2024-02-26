#!/bin/bash

n="$1"
m="$2"
word="$3"
i=0

while [ $i -lt "$m" ]; do 
    str="$str $word"
    i=$((i+1))
done

punition1.sh "$n" "$str"