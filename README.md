stlsplit
========

This tool receives one STL file and split it to several files - one shell a file.

The code originated in [Slic3r](https://github.com/alexrj/Slic3r) and the author of the splitting code is [Alessandro Ranellucci](https://github.com/alexrj).
It's licensed under the _GNU Affero General Public License, version 3_.

Building
--------

You'll need the [ADMesh libraray](https://github.com/admesh/admesh) and g++:

    g++ -Wall stlsplit.cpp -ladmesh -o stlsplit

To install stlsplit, put the compiled binary into your `$PATH`.

    sudo cp stlsplit /usr/local/bin

Running
-------

    stlsplit file.stl

As a result, you'll get `file.stl.part1.stl`, `file.stl.part2.stl` and so on.
