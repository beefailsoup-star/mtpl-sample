#ifndef INI_PARSER_H
#define INI_PARSER_H

#include <string>
#include <unordered_map>
#include <vector>
#include <optional>

class IniParser {
public:
    IniParser() = default;
    explicit IniParser(const std::string& path);
    ~IniParser() = default;

    bool load(const std::string& path);
    bool parse(const std::string& content);
    std::string serialize() const;

    bool has_section(const std::string& section) const;
    bool has_key(const std::string& section, const std::string& key) const;

    std::string get(const std::string& section, const std::string& key,
                    const std::string& default_val = {}) const;
    int get_int(const std::string& section, const std::string& key,
                int default_val = 0) const;
    double get_double(const std::string& section, const std::string& key,
                      double default_val = 0.0) const;
    bool get_bool(const std::string& section, const std::string& key,
                  bool default_val = false) const;

    void set(const std::string& section, const std::string& key,
             const std::string& value);
    void remove_section(const std::string& section);
    void remove_key(const std::string& section, const std::string& key);

    std::vector<std::string> sections() const;
    std::vector<std::string> keys(const std::string& section) const;

private:
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> data_;
    std::string trim(const std::string& s) const;
};

#endif
