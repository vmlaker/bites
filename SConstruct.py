"""The SCons file for Bites."""

# Build libraries.
sources = (
    'src/Averager.cpp',
    'src/Config.cpp',
    'src/SortedList.cpp',
    'src/RateTicker.cpp',
)
env = Environment(
    CXXFLAGS='-std=c++11',
)
for source in sources:
    target = source[:source.rfind('.')]
    env.Library(target=target, source=source)

# Build the test program.
sources = (
    'src/AveragerTest.cpp',
    'src/ConfigTest.cpp',
    'src/SortedListTest.cpp',
    'src/RateTickerTest.cpp',
    'src/test.cpp',
)
libs = (
    'boost_unit_test_framework',
    'Averager',
    'Config',
    'SortedList',
    'RateTicker',
)
env = Environment(
    LIBPATH='src',
    LIBS=libs,
    CXXFLAGS='-std=c++11',
) 
env.Program(target='src/test', source=sources)

