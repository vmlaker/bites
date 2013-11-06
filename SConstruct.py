"""The SCons file."""

# Build libraries.
sources = (
    'src/Averager.cpp',
    'src/Config.cpp',
    'src/SortedList.cpp',
)
env = Environment()
for source in sources:
    target = source[:source.rfind('.')]
    env.Library(target=target, source=source)

# Build test programs.
sources_libs = (
    # Each source code links to the library.
    ('src/AveragerTest.cpp', 'Averager'),
    ('src/ConfigTest.cpp', 'Config'),
    ('src/SortedListTest.cpp', 'SortedList'),
)
for source, lib in sources_libs:
    env = Environment(
        LIBPATH='src',
        LIBS=['boost_unit_test_framework', lib],
    )
    target = source[:source.rfind('.')]
    env.Program(target=target, source=source)
