

rm -rf build
mkdir build
cd build
#cmake -DCMAKE_BUILD_TYPE=Debug ..
#cmake --build .
cmake ..
make


cd  CMakeFiles/PsdModule.dir/src
cp *.gcno ../../../../gtest/output/bin
cd ../../../../gtest/output/bin
./PsdModule
cd ../../../build/CMakeFiles/PsdModule.dir/src

cp *.gcda ../../../../gtest/output/bin
lcov -c -d . -t  PsdModule -o PsdModule.info  --rc lcov_branch_coverage=1
#lcov -e PsdModule.info '/home/zhao/Documents/Psd/src/*' -o FilterPsdModule.info
genhtml -o ../../../../result  PsdModule.info --branch-coverage --rc branch_coverage=1
