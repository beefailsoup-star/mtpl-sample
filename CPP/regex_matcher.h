#ifndef REGEX_MATCHER_H
#define REGEX_MATCHER_H

#include <string>
#include <vector>
#include <regex>
#include <optional>

class RegexMatcher {
public:
    RegexMatcher() = default;
    explicit RegexMatcher(const std::string& pattern);

    bool set_pattern(const std::string& pattern);
    std::string pattern() const { return pattern_; }

    bool match(const std::string& input) const;
    bool search(const std::string& input) const;
    bool starts_with(const std::string& input) const;
    bool ends_with(const std::string& input) const;

    std::optional<std::string> capture(const std::string& input, int group = 1) const;
    std::vector<std::string> captures(const std::string& input) const;
    std::vector<std::vector<std::string>> find_all(const std::string& input) const;

    std::string replace(const std::string& input, const std::string& replacement) const;
    std::vector<std::string> split(const std::string& input) const;

    bool is_valid() const { return valid_; }
    std::string last_error() const { return last_error_; }

private:
    std::string pattern_;
    std::regex regex_;
    bool valid_ = false;
    std::string last_error_;
};

#endif
