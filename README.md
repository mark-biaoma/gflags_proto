执行流程
1）创建文件夹
mkdir build bin

2）编译
cd build
cmake ..
make

3）执行
cd ../bin
./main --flagfile=../config/conf.flags
