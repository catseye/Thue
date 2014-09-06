#!/bin/sh -x

# build script for thue.c, written by Chris Pressey & in the public domain
mkdir -p bin
gcc src/thue.c -o bin/thue
