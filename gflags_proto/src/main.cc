#include <iostream>
#include <memory>
#include "test_gflags.h"
#include "proto_parse.h"
#include "test_proto.pb.h"
#include <deque>
#include <string>
#include <algorithm>
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

    std::shared_ptr<tutorial::Persons> proto_conf = std::make_shared<tutorial::Persons>();
    if (ReadConfigToProto(FLAGS_config_path, proto_conf.get())){
      printf("proto_config:[%s]", proto_conf->Utf8DebugString().c_str());
    }
    
    gflags::ShutDownCommandLineFlags();

    std::deque<int> que;
    que.push_front(1);
    que.push_back(3);
    que.push_back(6);
    que.push_back(2);
    que.pop_front();
    que.push_back(4);
    
    std::deque<int>::iterator
    result = std::max_element(que.begin(), que.end());
    std::cout << "max element at: " << que[std::distance(que.begin(), result)] << '\n';



    return 0;
}
