git pull
scons -j8 .
bin/run_tests --report_level=short
doxygen dox/doxy.conf
scons -c .
git checkout gh-pages
find . -maxdepth 1 ! -name 'html' ! -name '.git' | xargs rm -rf
mv html/* .
rm -rf html
git add .
git commit -m "Update gh-pages for `git log master -1 | head -1`"
git push
git checkout master
