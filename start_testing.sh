mkdir build 
cd ./build 
cmake .. 
make
./runtests 
cd ..
gcovr  -r ./  --filter  src 
