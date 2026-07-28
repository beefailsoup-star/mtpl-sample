#include "regex_matcher.h"
#include <sstream>

RegexMatcher::RegexMatcher(const std::string& pattern) {
    set_pattern(pattern);
}

bool RegexMatcher::set_pattern(const std::string& pattern) {
    pattern_ = pattern;
    try {
        regex_ = std::regex(pattern, std::regex::ECMAScript);
        valid_ = true;
        last_error_.clear();
    } catch (const std::regex_error& e) {
        valid_ = false;
        last_error_ = e.what();
    }
    return valid_;
}

bool RegexMatcher::match(const std::string& input) const {
    if (!valid_) return false;
    return std::regex_match(input, regex_);
}

bool RegexMatcher::search(const std::string& input) const {
    if (!valid_) return false;
    return std::regex_search(input, regex_);
}

bool RegexMatcher::starts_with(const std::string& input) const {
    if (!valid_) return false;
    std::smatch m;
    return std::regex_search(input, m, regex_) && m.position() == 0;
}

bool RegexMatcher::ends_with(const std::string& input) const {
    if (!valid_) return false;
    std::smatch m;
    if (!std::regex_search(input, m, regex_)) return false;
    return m.position() + m.length() == static_cast<int>(input.size());
}

std::optional<std::string> RegexMatcher::capture(const std::string& input, int group) const {
    if (!valid_) return {};
    std::smatch m;
    if (std::regex_search(input, m, regex_) && group < static_cast<int>(m.size()))
        return m[group].str();
    return {};
}

std::vector<std::string> RegexMatcher::captures(const std::string& input) const {
    std::vector<std::string> results;
    if (!valid_) return results;
    std::smatch m;
    if (std::regex_search(input, m, regex_))
        for (size_t i = 1; i < m.size(); ++i)
            results.push_back(m[i].str());
    return results;
}

std::vector<std::vector<std::string>> RegexMatcher::find_all(const std::string& input) const {
    std::vector<std::vector<std::string>> results;
    if (!valid_) return results;
    std::sregex_iterator it(input.begin(), input.end(), regex_);
    std::sregex_iterator end;
    for (; it != end; ++it) {
        std::vector<std::string> groups;
        for (size_t i = 0; i < it->size(); ++i)
            groups.push_back((*it)[i].str());
        results.push_back(groups);
    }
    return results;
}

std::string RegexMatcher::replace(const std::string& input, const std::string& replacement) const {
    if (!valid_) return input;
    return std::regex_replace(input, regex_, replacement);
}

std::vector<std::string> RegexMatcher::split(const std::string& input) const {
    std::vector<std::string> parts;
    if (!valid_) { parts.push_back(input); return parts; }
    std::sregex_token_iterator it(input.begin(), input.end(), regex_, -1);
    std::sregex_token_iterator end;
    for (; it != end; ++it)
        parts.push_back(*it);
    return parts;
}
