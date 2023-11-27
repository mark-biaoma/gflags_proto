# 使用方法
cd gflags_proto
mkdir build 
mkdir bin
cd build && cmake .. && make
cd bin
./demo_gflags_proto --flagfile ../config/conf.flags
