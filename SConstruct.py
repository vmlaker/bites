"""The SCons file."""

import os

# Build libraries.
env = Environment()
libs = (
    ('src/Averager.cpp', env),
)
for source, env in libs:
    target = source[:source.rfind('.')]
    env.Library(target=target, source=source)

# Build programs.
env = Environment(
    LIBPATH='src',
    LIBS=['boost_unit_test_framework', 'Averager',],
)
progs = (
    ('src/AveragerTest.cpp', env),
)
for source, env in progs:
    target = source[:source.rfind('.')]
    env.Program(target=target, source=source)
