"""The SCons file for Bites."""

# Build libraries.
sources = (
    'src/Averager.cpp',
    'src/Config.cpp',
    'src/SortedList.cpp',
    'src/RateTicker.cpp',
)
env = Environment(
    CXXFLAGS="-std=c++11",
)
for source in sources:
    target = source[:source.rfind('.')]
    env.Library(target=target, source=source)

# Build test programs.
sources_libs = (
    # Each source code links to libraries.
    ('src/AveragerTest.cpp'  , ['Averager']),
    ('src/ConfigTest.cpp'    , ['Config']),
    ('src/SortedListTest.cpp', ['SortedList']),
    ('src/RateTickerTest.cpp', ['RateTicker', 'SortedList']),
)
for source, lib in sources_libs:
    env = Environment(
        LIBPATH='src',
        LIBS=['boost_unit_test_framework'] + lib,
        CXXFLAGS="-std=c++11",
    )
    target = source[:source.rfind('.')]
    env.Program(target=target, source=source)
