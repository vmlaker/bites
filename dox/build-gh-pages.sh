# Script to build gh-pages.

git pull
scons -c .
scons -j8 .
bin/run_tests --report_level=short
sh dox/build-dox.sh
scons -c .

git checkout gh-pages
find . -maxdepth 1 ! -name 'html' ! -name '.git' | xargs rm -rf
mv html/* .
rm -rf html
git add .

# Sanity check, see errors or recommendations,
# may have to do "git add . --all" afterwards.
git status

git commit -m "Update gh-pages for `git log master -1 | head -1`"
git push
git checkout master
