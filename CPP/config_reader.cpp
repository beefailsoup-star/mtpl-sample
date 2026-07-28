#include "config_reader.h"
#include <fstream>
#include <sstream>
#include "json_parser.h"
#include "ini_parser.h"

bool ConfigReader::load_json(const std::string& path) {
    auto val = JsonParser::parse_file(path);
    if (val.type() != JsonValue::Object_) return false;
    for (auto& [k, v] : val.as_object()) {
        switch (v.type()) {
        case JsonValue::String: data_[k] = v.as_string(); break;
        case JsonValue::Number: data_[k] = v.as_number(); break;
        case JsonValue::Bool: data_[k] = v.as_bool(); break;
        default: break;
        }
    }
    return true;
}

bool ConfigReader::load_ini(const std::string& path) {
    IniParser ini(path);
    for (auto& sec : ini.sections())
        for (auto& key : ini.keys(sec))
            data_[sec + "." + key] = ini.get(sec, key);
    return true;
}

bool ConfigReader::load_env(const std::string& path) {
    std::ifstream f(path);
    if (!f) return false;
    std::string line;
    while (std::getline(f, line)) {
        if (line.empty() || line[0] == '#') continue;
        auto eq = line.find('=');
        if (eq == std::string::npos) continue;
        std::string key = line.substr(0, eq);
        std::string val = line.substr(eq + 1);
        data_[key] = val;
    }
    return true;
}

bool ConfigReader::has(const std::string& key) const {
    return data_.count(key);
}

void ConfigReader::set(const std::string& key, const std::any& value) {
    data_[key] = value;
}

void ConfigReader::remove(const std::string& key) {
    data_.erase(key);
}

void ConfigReader::clear() {
    data_.clear();
}

std::vector<std::string> ConfigReader::keys() const {
    std::vector<std::string> ks;
    for (auto& [k, _] : data_) ks.push_back(k);
    return ks;
}
