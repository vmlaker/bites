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
lib = env.Library(target=target, source=sources)
Default(lib)  # Library is part of the default build.

# Add header-only classes.
names += [
    'ConcurrentQueue',
    'SortedList',
    'Thread',
]

# Build auxiliary executable.
env = Environment(
    CPPPATH='include',
    LIBS=['boost_thread'],
    CXXFLAGS='-std=c++11',
) 
progs = env.Program(
    target=os.path.join('bin', 'dump_version'),
    source=os.path.join('test', 'dump_version.cpp'),
)
Default(progs)  # Part of the default build.

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
tests = env.Program(
    target=os.path.join('bin', 'run_tests'), 
    source=sources,
)
Default(tests)  # Tests are part of the default build.

# Custom builder for resizing the logo.
conv = Builder(
    action='convert $SOURCE -resize 75x75 $TARGET',
)
env = Environment(BUILDERS={'Resize' : conv})
env.Resize('logo_small.png', 'logo.png')
env.Clean('logo.png', 'logo_small.png')
