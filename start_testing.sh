mkdir build 
cd ./build 
cmake .. 
make
./runtests 
cd ..
lcov --base-directory . --directory ./build/ -c -o ./lcov.info  --ignore-errors mismatch  
