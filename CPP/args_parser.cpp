#include "args_parser.h"
#include <iostream>
#include <algorithm>

void ArgsParser::add_option(const std::string& long_name, char short_name,
                            const std::string& description, bool required, bool has_value) {
    options_.push_back({long_name, short_name, description, required, has_value, false});
}

void ArgsParser::add_flag(const std::string& long_name, char short_name,
                          const std::string& description) {
    options_.push_back({long_name, short_name, description, false, false, true});
}

bool ArgsParser::parse(int argc, char* argv[]) {
    std::vector<std::string> args;
    if (argc > 0) {
        program_name_ = argv[0];
        for (int i = 1; i < argc; ++i) args.push_back(argv[i]);
    }
    return parse(args);
}

bool ArgsParser::parse(const std::vector<std::string>& args) {
    for (size_t i = 0; i < args.size(); ++i) {
        const auto& arg = args[i];
        if (arg.substr(0, 2) == "--") {
            auto eq = arg.find('=');
            std::string name = (eq != std::string::npos) ? arg.substr(2, eq - 2) : arg.substr(2);
            auto* opt = find_option(name);
            if (!opt) { std::cerr << "Unknown option: " << arg << "\n"; return false; }
            if (opt->is_flag) {
                flags_[opt->long_name] = true;
            } else {
                if (eq != std::string::npos) {
                    values_[opt->long_name] = arg.substr(eq + 1);
                } else if (i + 1 < args.size()) {
                    values_[opt->long_name] = args[++i];
                } else {
                    std::cerr << "Option " << arg << " requires a value\n";
                    return false;
                }
            }
        } else if (arg[0] == '-') {
            char sn = arg[1];
            auto* opt = find_option(std::string(1, sn));
            if (!opt) { std::cerr << "Unknown short option: -" << sn << "\n"; return false; }
            if (opt->is_flag)
                flags_[opt->long_name] = true;
            else if (i + 1 < args.size())
                values_[opt->long_name] = args[++i];
            else {
                std::cerr << "Option -" << sn << " requires a value\n";
                return false;
            }
        } else {
            positional_.push_back(arg);
        }
    }

    for (auto& opt : options_)
        if (opt.required && !has(opt.long_name))
            return false;

    return true;
}

bool ArgsParser::has(const std::string& name) const {
    return values_.count(name) || flags_.count(name);
}

std::string ArgsParser::get(const std::string& name, const std::string& default_val) const {
    auto it = values_.find(name);
    return it != values_.end() ? it->second : default_val;
}

int ArgsParser::get_int(const std::string& name, int default_val) const {
    auto s = get(name);
    return s.empty() ? default_val : std::stoi(s);
}

double ArgsParser::get_double(const std::string& name, double default_val) const {
    auto s = get(name);
    return s.empty() ? default_val : std::stod(s);
}

bool ArgsParser::is_set(const std::string& name) const {
    return flags_.count(name);
}

const ArgsParser::Option* ArgsParser::find_option(const std::string& name) const {
    if (name.size() == 1) {
        for (auto& opt : options_)
            if (opt.short_name == name[0]) return &opt;
    }
    for (auto& opt : options_)
        if (opt.long_name == name) return &opt;
    return nullptr;
}

std::string ArgsParser::usage() const {
    std::string u = "Usage: " + program_name_;
    for (auto& opt : options_) {
        u += " [";
        if (opt.short_name) u += "-" + std::string(1, opt.short_name) + "|";
        u += "--" + opt.long_name;
        if (opt.has_value) u += " <value>";
        u += "]";
    }
    u += "\n\nOptions:\n";
    for (auto& opt : options_) {
        u += "  ";
        if (opt.short_name) u += std::string("-") + opt.short_name + ", ";
        else u += "    ";
        u += "--" + opt.long_name;
        if (opt.has_value) u += " <val>";
        u += "\t" + opt.description;
        if (opt.required) u += " (required)";
        u += "\n";
    }
    return u;
}
