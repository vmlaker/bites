bites
=====

Bite sized C/C++ codes, a C/C++ version of `Coils <http://vmlaker.github.com/coils>`_.

Requirements
------------

The build environment uses `SCons <http://www.scons.org>`_.
For unit testing, we use the `Boost Test Library <http://www.boost.org/doc/libs/1_53_0/libs/test/doc/html/index.html>`_.
::
   
   yum install scons
   yum install boost

Usage
-----

Build the codes by running SCons:
::
   
   scons -j8

Run the tests:
::

   ./run_tests --report_level=short
   ./run_tests --report_level=detailed

Clean up after the build:
::

   scons -c
