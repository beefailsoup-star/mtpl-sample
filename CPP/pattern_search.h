#ifndef PATTERN_SEARCH_H
#define PATTERN_SEARCH_H

#include <string>
#include <vector>

namespace pattern {

std::vector<int> kmp_search(const std::string& text, const std::string& pattern);
std::vector<int> rabin_karp_search(const std::string& text, const std::string& pattern);
std::vector<int> naive_search(const std::string& text, const std::string& pattern);
std::vector<int> boyer_moore_search(const std::string& text, const std::string& pattern);

} // namespace pattern

#endif
