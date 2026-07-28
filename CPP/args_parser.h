#ifndef ARGS_PARSER_H
#define ARGS_PARSER_H

#include <string>
#include <vector>
#include <map>
#include <optional>

class ArgsParser {
public:
    ArgsParser() = default;

    void add_option(const std::string& long_name, char short_name = '\0',
                    const std::string& description = {},
                    bool required = false, bool has_value = true);
    void add_flag(const std::string& long_name, char short_name = '\0',
                  const std::string& description = {});

    bool parse(int argc, char* argv[]);
    bool parse(const std::vector<std::string>& args);

    bool has(const std::string& name) const;
    std::string get(const std::string& name, const std::string& default_val = {}) const;
    int get_int(const std::string& name, int default_val = 0) const;
    double get_double(const std::string& name, double default_val = 0.0) const;
    bool is_set(const std::string& name) const;

    std::vector<std::string> positional_args() const { return positional_; }
    std::string usage() const;

    void set_program_name(const std::string& name) { program_name_ = name; }

private:
    struct Option {
        std::string long_name;
        char short_name;
        std::string description;
        bool required;
        bool has_value;
        bool is_flag;
    };

    std::vector<Option> options_;
    std::map<std::string, std::string> values_;
    std::map<std::string, bool> flags_;
    std::vector<std::string> positional_;
    std::string program_name_;

    const Option* find_option(const std::string& name) const;
};

#endif
