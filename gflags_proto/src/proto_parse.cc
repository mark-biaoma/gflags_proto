#include "proto_parse.h"

bool ReadConfigToProto(const std::string &file_name,
                       google::protobuf::Message *proto) {
  auto str_endwith = [](const std::string &str,
                        const std::string &endwith_str) -> bool {
    int n1 = str.size();
    int n2 = endwith_str.size();
    if (n2 > n1) {
      return false;
    }

    int r1 = n1 - 1, r2 = n2 - 1;
    while (r1 >= 0 && r2 >= 0) {
      if (str[r1] != endwith_str[r2]) {
        return false;
      }
      --r1, --r2;
    }
    return true;
  };

  bool result = false;
  if (str_endwith(file_name, ".json")) {
    result = ReadJsonFileToProto(file_name, proto);
  } else if (str_endwith(file_name, ".txt")) {
    result = ReadFileToProto(file_name, proto);
  }

  return result;
}

bool ReadFileToProto(const std::string &file_name,
                     google::protobuf::Message *proto) {
  using google::protobuf::TextFormat;
  using google::protobuf::io::FileInputStream;
  using google::protobuf::io::ZeroCopyInputStream;
  int fd = open(file_name.c_str(), O_RDONLY);
  if (fd < 0) {
    printf("Failed to open file %s in text mode.", file_name.c_str());
    return false;
  }
  ZeroCopyInputStream *input = new FileInputStream(fd);
  bool success = google::protobuf::TextFormat::Parse(input, proto);
  if (!success) {
    printf("Failed to parse file %s  as text proto.", file_name.c_str());
  }
  delete input;
  close(fd);
  return success;
}

bool ReadJsonFileToProto(const std::string &file_name,
                         google::protobuf::Message *proto) {
  std::ifstream input(file_name, std::ios_base::in);
  if (!input.is_open()) {
    printf("Failed to open file %s in text mode.", file_name.c_str());
    return false;
  }

  std::string json_data((std::istreambuf_iterator<char>(input)),
                        std::istreambuf_iterator<char>());

  // 配置 JSON 解析选项
  google::protobuf::util::JsonParseOptions json_options;
  json_options.ignore_unknown_fields = true; // 忽略未知字段

  bool success = google::protobuf::util::JsonStringToMessage(json_data, proto,
                                                             json_options)
                     .ok();
  if (!success) {
    printf("Failed to parse file %s  as text proto.", file_name.c_str());
  }
  input.close();
  return success;
}