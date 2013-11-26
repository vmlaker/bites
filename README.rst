.. image:: https://api.travis-ci.org/vmlaker/bites.png?branch=master
  :alt: Build Result Image
  :target: https://travis-ci.org/vmlaker/bites

Bites
=====

Bite-sized C++ codes, a C++ version of `Coils <http://vmlaker.github.com/coils>`_.

Requirements
------------

The codes use `Boost C++ libraries <http://www.boost.org>`_
for implementation and test harness.
The build environment is configured with 
`SCons <http://www.scons.org>`_, 
the powerful Python-based software construction tool.

If using YUM, get these with:
::
   
   yum install boost-devel
   yum install scons

Or, with Aptitude, run:
::

   aptitude install libboost-all-dev
   aptitude install scons

Usage
-----

Build the codes by running SCons:
::
   
   scons -j8

Run the tests:
::

   bin/run_tests --report_level=short
   bin/run_tests --report_level=detailed

Clean up after the build:
::

   scons -c

Docs
----

Generate the documentation:
::

   doxygen doxy.conf
