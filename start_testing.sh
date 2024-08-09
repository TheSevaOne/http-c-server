mkdir build 
cd ./build 
cmake .. 
make
./runtests 
cd ..
gcovr  -r ./  --filter  src  --coveralls-pretty ./coverage.json
gcovr  -r ./  --filter  src  
