# Script to build Doxygen documentation.

rm -rf html
scons logo_small.png
doxygen dox/doxy.conf
find html -type f |\
   xargs grep -l "###version###" |\
   xargs sed -i s:'###version###':"`bin/dump_version`":g
find html -type f |\
   xargs grep -l "###updated###" |\
   xargs sed -i s/'###updated###'/"`date`"/g
scons -c logo_small.png
