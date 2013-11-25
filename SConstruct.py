"""The SCons file for Bites."""

import os 

# Retrieve the debug flag, if set.
debug = bool(int(ARGUMENTS.get('debug', False)))

# Names of .cpp classes.
names = [
    'Averager',
    'Config',
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
if debug: env.Append(CXXFLAGS = ' -g')
env.Library(target=target, source=sources)

# Add header-only classes.
names += [
    'ConcurrentQueue',
    'SortedList',
]

# Build the test program.
libs = [
    'boost_unit_test_framework', 
    'boost_thread', 
    'bites',
]
sources = ['test.cpp'] + ['{}Test.cpp'.format(name) for name in names]
sources = [os.path.join('test', source) for source in sources]
env = Environment(
    CPPPATH='include',
    LIBPATH='lib',
    LIBS=libs,
    CXXFLAGS='-std=c++11',
) 
if debug: env.Append(CXXFLAGS = ' -g')
env.Program(
    target=os.path.join('bin', 'run_tests'), 
    source=sources,
)
