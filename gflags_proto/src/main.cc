#include <iostream>
#include "test_gflags.h"
using namespace std;

void print_argv(int argc, char **argv)
{   
    int iRecycle = 0;
    std::cout<<"argc: "<<argc;
    for(iRecycle = 0; iRecycle < argc; iRecycle++) {
      std::cout<<" "<<argv[iRecycle];
    }
    std::cout<<std::endl; 
}

int main(int argc, char **argv)
{
    /* 1、验证ParseCommandLineFlags函数中第三个入参 true or false 的作用 */
    print_argv(argc, argv);
    /* flags的主要作用，解析命令行中argc和argv参数，并将命令行参数解析结果给我们定义的变量赋值 */
    gflags::ParseCommandLineFlags(&argc, &argv, true);  //用于接受命令行的flag参数并更新默认参数
    print_argv(argc, argv);
    /* 2、验证变量的访问 */
    for(int i=2; i>0;--i)
      std::cout<<"hello world gflags: "<<FLAGS_config_path<<std::endl;
    
    gflags::ShutDownCommandLineFlags();
    return 0;
}
