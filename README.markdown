The Thue Programming Language
=============================

This is Cat's Eye Technologies' distribution of **Thue**, an esoteric
programming language designed by John Colagioia.  Thue is a non-deterministic
string-rewriting language, based on a formalism called a *semi-Thue system*,
but also including some programming-oriented features, like input and output.

The specification can be found in the file `thue.txt` in the `doc` directory.

John's implementation of the language, in C, is in the file `thue.c` in the
`src` directory, and can, for all intents and purposes, be considered the
reference implementation.

In the `src` directory, there are also two other implementation of Thue:

*   `thue.py`, in Python, written by Frédéric van der Plancke
*   `thue.rb`, in Ruby, written by Chris Pressey

There is an assortment of example Thue programs in the `eg` directory; all
were written by John, except for `add_bin.t`, which was written by Frédéric,
and the `edgcase?.t` ones, which were written by Chris.

More information on Thue can be found on the esolangs.org wiki
[entry for Thue](http://esolangs.org/wiki/Thue).

License
-------

All files in this distribution are "essentially in the public domain".

John's original license text can be found in `doc/license.txt`.  (In it,
the phrase "this file" referred to the archive in which all the Thue files
were distributed.)  He placed the files he wrote (implementation, spec, and
examples) basically into the public domain, with the proviso that he be
contacted by anyone who wanted to do "anything interesting" with the files,
including modifying them.

Unfortunately, the email address he left for this purpose, with the claim
that it would be kept current, is no longer active.  Thus, one can probably
reasonably assume that he is no longer interested in what happens to his
Thue sources, and that they are unconditionally in the public domain;
however, I am not a lawyer, etc. etc.

Frédéric's implementation, and example source, are much less questionably in
the public domain; his only proviso is that he be given credit for what he
wrote (and not be given credit for any changes or additions that he did not
write.)  Actually, as I understand it (but again, I am not a lawyer etc etc),
putting something into the public domain does not take away one's moral
rights to proper credit, so this isn't very much (if at all) different from
just being in the public domain.

I, Chris Pressey, hereby place my implementation in Ruby, my example Thue
programs in `eg`, and the contents of this README, into the public domain,
under the Creative Commons [CC0 1.0 Public Domain Dedication][].

[CC0 1.0 Public Domain Dedication]: http://creativecommons.org/publicdomain/zero/1.0/
