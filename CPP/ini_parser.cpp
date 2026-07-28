#include "ini_parser.h"
#include <fstream>
#include <sstream>
#include <algorithm>

IniParser::IniParser(const std::string& path) {
    load(path);
}

bool IniParser::load(const std::string& path) {
    std::ifstream f(path);
    if (!f) return false;
    std::ostringstream ss;
    ss << f.rdbuf();
    return parse(ss.str());
}

bool IniParser::parse(const std::string& content) {
    data_.clear();
    std::string current_section;
    std::istringstream ss(content);
    std::string line;
    while (std::getline(ss, line)) {
        line = trim(line);
        if (line.empty() || line[0] == ';' || line[0] == '#') continue;
        if (line[0] == '[') {
            auto pos = line.find(']');
            if (pos == std::string::npos) return false;
            current_section = trim(line.substr(1, pos - 1));
        } else {
            auto eq = line.find('=');
            if (eq == std::string::npos) return false;
            std::string key = trim(line.substr(0, eq));
            std::string val = trim(line.substr(eq + 1));
            data_[current_section][key] = val;
        }
    }
    return true;
}

std::string IniParser::serialize() const {
    std::ostringstream ss;
    for (auto& [section, keys] : data_) {
        ss << "[" << section << "]\n";
        for (auto& [key, val] : keys)
            ss << key << " = " << val << "\n";
        ss << "\n";
    }
    return ss.str();
}

bool IniParser::has_section(const std::string& section) const {
    return data_.count(section);
}

bool IniParser::has_key(const std::string& section, const std::string& key) const {
    auto it = data_.find(section);
    return it != data_.end() && it->second.count(key);
}

std::string IniParser::get(const std::string& section, const std::string& key,
                           const std::string& default_val) const {
    auto sit = data_.find(section);
    if (sit == data_.end()) return default_val;
    auto kit = sit->second.find(key);
    if (kit == sit->second.end()) return default_val;
    return kit->second;
}

int IniParser::get_int(const std::string& section, const std::string& key,
                       int default_val) const {
    auto s = get(section, key);
    return s.empty() ? default_val : std::stoi(s);
}

double IniParser::get_double(const std::string& section, const std::string& key,
                             double default_val) const {
    auto s = get(section, key);
    return s.empty() ? default_val : std::stod(s);
}

bool IniParser::get_bool(const std::string& section, const std::string& key,
                         bool default_val) const {
    auto s = get(section, key);
    if (s.empty()) return default_val;
    std::transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s == "true" || s == "yes" || s == "1" || s == "on";
}

void IniParser::set(const std::string& section, const std::string& key,
                    const std::string& value) {
    data_[section][key] = value;
}

void IniParser::remove_section(const std::string& section) {
    data_.erase(section);
}

void IniParser::remove_key(const std::string& section, const std::string& key) {
    auto it = data_.find(section);
    if (it != data_.end()) it->second.erase(key);
}

std::vector<std::string> IniParser::sections() const {
    std::vector<std::string> secs;
    for (auto& [s, _] : data_) secs.push_back(s);
    return secs;
}

std::vector<std::string> IniParser::keys(const std::string& section) const {
    std::vector<std::string> ks;
    auto it = data_.find(section);
    if (it != data_.end())
        for (auto& [k, _] : it->second) ks.push_back(k);
    return ks;
}

std::string IniParser::trim(const std::string& s) const {
    auto start = s.find_first_not_of(" \t\r\n");
    if (start == std::string::npos) return {};
    auto end = s.find_last_not_of(" \t\r\n");
    return s.substr(start, end - start + 1);
}
