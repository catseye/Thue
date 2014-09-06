The Thue Programming Language
=============================

This is Cat's Eye Technologies' distribution of **Thue**, an esoteric
programming language designed by John Colagioia.  Thue is a non-deterministic
string-rewriting language, based on a formalism called a *semi-Thue system*,
but also including some programming-oriented features, like input and output.

The specification can be found in the file `thue.txt` in the `doc` directory.

John's implementation of the language, in C, is in the file `thue.c` in the
`src` directory, and can, for all intents and purposes, be considered the
reference implementation.  There is no `Makefile` but an executable can be
built by running the included `build.sh` script, which is trivial.

In the `src` directory, there are also two other implementation of Thue:

*   `thue.py`, in Python, written by Frédéric van der Plancke
*   `thue.rb`, in Ruby, written by Chris Pressey

There is an assortment of example Thue programs in the `eg` directory.  The
credits for these are as follows:

*   `add_bin.t`: Frédéric van der Plancke
*   `edgcase?.t`: Chris Pressey
*   `truth-machine.t`: Keymaker
*   all others: John Colagioia

More information on Thue can be found on the esolangs.org wiki
[entry for Thue](http://esolangs.org/wiki/Thue).

Contents in this distribution are "essentially in the public domain" (scare
quotes intentional.)  See the file LICENSE for more information.
