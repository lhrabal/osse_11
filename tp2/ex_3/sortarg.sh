#!/bin/bash

rm /tmp/1
for arg in "$@" ; do
    echo "$arg" >> /tmp/1
done

sort /tmp/1 > /tmp/2

while read -r line; do
  echo "$line"
done < /tmp/2