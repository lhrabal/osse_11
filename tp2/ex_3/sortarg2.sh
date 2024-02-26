#!/bin/bash

for arg in "$@" ; do
    echo "$arg"
done | sort | tr '\n' ' '

echo # just to add a new line