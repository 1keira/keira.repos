
# 设置环境为arm架构
# source ~/usr/local/oecore-x86_64/environment-setup-aarch64-poky-linux 
rm -rf build
mkdir build
echo "build clean is ok"
cd build
#cmake -DCMAKE_BUILD_TYPE=Debug ..
#cmake --build .
cmake ..
make


cd  CMakeFiles/psd.dir/src
cp *.gcno ../../../../gtest/output/bin
cd ../../../../gtest/output/bin
./psd
cd ../../../build/CMakeFiles/psd.dir/src

cp *.gcda ../../../../gtest/output/bin
lcov -c -d . -t  psd -o psd.info  --rc lcov_branch_coverage=1
#lcov -e psd.info '/home/zhao/Documents/Psd/src/*' -o Filterpsd.info
genhtml -o ../../../../result  psd.info --branch-coverage --rc branch_coverage=1
