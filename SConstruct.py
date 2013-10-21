"""The SCons file."""

# Build libraries.
sources = (
    'src/Averager.cpp',
    'src/Config.cpp',
)
env = Environment()
for source in sources:
    target = source[:source.rfind('.')]
    env.Library(target=target, source=source)

# Build programs.
env = Environment(
    LIBPATH='src',
    LIBS=['boost_unit_test_framework', 'Averager',],
)
sources = (
    'src/AveragerTest.cpp',
)
for source in sources:
    target = source[:source.rfind('.')]
    env.Program(target=target, source=source)
