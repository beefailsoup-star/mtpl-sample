#ifndef STRING_MANIP_H
#define STRING_MANIP_H

#include <string>
#include <vector>
#include <algorithm>

namespace strutil {

std::string trim(const std::string& s);
std::string to_lower(const std::string& s);
std::string to_upper(const std::string& s);
std::vector<std::string> split(const std::string& s, char delim);
std::string join(const std::vector<std::string>& parts, const std::string& delim);
std::string replace(const std::string& s, const std::string& from, const std::string& to);
bool starts_with(const std::string& s, const std::string& prefix);
bool ends_with(const std::string& s, const std::string& suffix);
std::string reverse(const std::string& s);
bool contains(const std::string& s, const std::string& sub);

} // namespace strutil

#endif
