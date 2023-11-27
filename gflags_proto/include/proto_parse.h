#include "google/protobuf/io/zero_copy_stream.h"
#include "google/protobuf/io/zero_copy_stream_impl.h"
#include "google/protobuf/message.h"
#include "google/protobuf/text_format.h"
#include <iostream>
#include <fstream>
#include "google/protobuf/util/json_util.h"
#include "fcntl.h"
#include "unistd.h"

bool ReadConfigToProto(const std::string &file_name,
                       google::protobuf::Message *proto);

bool ReadFileToProto(const std::string &file_name,
                     google::protobuf::Message *proto);
bool ReadJsonFileToProto(const std::string &file_name,
                         google::protobuf::Message *proto);