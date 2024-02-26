#!/bin/bash

export LD_LIBRARY_PATH=/pub/FISE_OSSE11/shell/iacmp/lib
export IacmpDir=/pub/FISE_OSSE11/shell/iacmp

exec ./iacmp "$@"