"""The SCons file for Bites."""

import os

names = [
    'Averager',
    'Config',
    'SortedList',
    'RateTicker',
]

# Build the libraries.
env = Environment(
    CPPPATH='include',
    CXXFLAGS='-std=c++11',
)
for name in names:
    target = os.path.join('lib', name)
    source = os.path.join('src', '{}.cpp'.format(name))
    env.Library(target=target, source=source)

# Build the test program.
libs = names + ['boost_unit_test_framework']
sources = ['test.cpp'] + ['{}Test.cpp'.format(name) for name in names]
sources = [os.path.join('test', source) for source in sources]
env = Environment(
    CPPPATH='include',
    LIBPATH='lib',
    LIBS=libs,
    CXXFLAGS='-std=c++11',
) 
env.Program(target='run_tests', source=sources)
