#!/bin/bash
set -e

mkdir -p build
rm -f build/minitito

#gcc -D CLI_MODE -o build/minitito main.c titomach.c titoinstr.c titostate.c
gcc -o build/minitito main.c titomach.c titoinstr.c titostate.c -D VERBOSE -D CLI_MODE

./build/minitito samples/test.b91