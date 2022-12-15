#!/bin/bash
set -e

mkdir -p build
rm -f build/minitito

gcc -o build/minitito main.c titomach.c titoinstr.c titostate.c

./build/minitito samples/test.b91