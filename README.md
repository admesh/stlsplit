stlsplit
========

This tool receives one STL file and split it to several files - one shell a file.

The code originated in [Slic3r](https://github.com/alexrj/Slic3r) and the author of the splitting code is [Alessandro Ranellucci](https://github.com/alexrj).
It's licensed under the _GNU Affero General Public License, version 3_.

Building
--------

You'll need the [ADMesh libraray](https://github.com/admesh/admesh), g++ and [Premake 4](http://premake.github.io/).
On Linux, you would use:

    premake4 gmake
    make

To install stlsplit, put the compiled binary and the shared library into your `$PATH`:

    sudo cp build/stlsplit /usr/local/bin
    sudo cp build/libstlsplit.so.1 /usr/local/lib # or lib64

If you intend to build something with stlsplit as a library, you'll also need the header file and .so symlink:

    sudo cp stlsplit.h /usr/local/include
    sudo ln -s libstlsplit.so.1 /usr/local/lib/libstlsplit.so # or lib64
    sudo ldconfig

Running the command line tool
-----------------------------

    stlsplit file.stl

As a result, you'll get `file.stl.part1.stl`, `file.stl.part2.stl` and so on.
