Mitsukeru
=========

Abstract
--------

This is an experiment in full-text indexing. I hope to use it to learn more
about what makes a good search engine tick. If at all possible, one day I'd like
this to be a usable piece of software.

Right now it builds a very simple term index and allows you to search it using
boolean OR queries.

Usage
-----

Build the application like so:

    $ g++ -o app mitsukeru.cpp

Run it like this:

    $ ./app

Enter text to search for!

Todo
----

This is what I want to do with this, roughly in order:

1) Refactoring
2) Persistent indexes (Kyoto Cabinet?)
3) More flexible indexes (think MongoDB for searching and not written in Java)
4) Network server mode (REST, probably)

Thanks
------

I'm reading http://nlp.stanford.edu/IR-book/html/htmledition/irbook.html right
now and it's really, really good. I'd like to thank the authors of it for such
a great reference and would highly suggest it to anyone wanting to learn about
search engines and IR in general!

Also I'm using https://github.com/kazuho/picojson for the JSON parsing part of
this, so props to Cybozu for that.

Licensing
---------

All original work is licensed under the standard 3-clause BSD license, a copy of
which is available with this code.

picojson uses the 2-clause BSD license.

Contact
-------

Probably easiest to hit me up on one of:

* GitHub (http://github.com/deoxxa)
* Twitter (http://twitter.com/deoxxa)
* Email (deoxxa@fknsrs.biz)
