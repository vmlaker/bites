"""The SCons file for Bites."""

import os 

# Names of classes.
names = [
    'Averager',
    'Config',
    'SortedList',
    'RateTicker',
]

# Build the library.
sources = ['{}.cpp'.format(name) for name in names]
sources = [os.path.join('src', source) for source in sources]
target = os.path.join('lib', 'libbites')
env = Environment(
    CPPPATH='include',
    CXXFLAGS='-std=c++11',
)
env.Library(target=target, source=sources)

# Build the test program.
libs = ['boost_unit_test_framework', 'bites']
sources = ['test.cpp'] + ['{}Test.cpp'.format(name) for name in names]
sources = [os.path.join('test', source) for source in sources]
env = Environment(
    CPPPATH='include',
    LIBPATH='lib',
    LIBS=libs,
    CXXFLAGS='-std=c++11',
) 
env.Program(target='run_tests', source=sources)
