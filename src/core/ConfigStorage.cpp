#include "ConfigStorage.h"
#include <fstream>

namespace {
std::string trim(const std::string& s) {
    const char* ws = " \t\r\n";
    auto b = s.find_first_not_of(ws);
    if (b == std::string::npos) return "";
    auto e = s.find_last_not_of(ws);
    return s.substr(b, e - b + 1);
}
}

FileConfigStorage::FileConfigStorage(std::string path) : path_(std::move(path)) {}

bool FileConfigStorage::load(std::map<std::string, std::string>& data) {
    std::ifstream in(path_);
    if (!in.is_open()) return false;
    std::string line;
    while (std::getline(in, line)) {
        line = trim(line);
        if (line.empty() || line[0] == '#') continue;
        auto pos = line.find('=');
        if (pos == std::string::npos) continue;
        data[trim(line.substr(0, pos))] = trim(line.substr(pos + 1));
    }
    return true;
}
