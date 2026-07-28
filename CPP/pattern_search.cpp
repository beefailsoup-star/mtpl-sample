#include "pattern_search.h"
#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>

namespace pattern {

std::vector<int> kmp_search(const std::string& text, const std::string& pattern) {
    std::vector<int> matches;
    if (pattern.empty()) return matches;

    std::vector<int> lps(pattern.size());
    for (int i = 1, len = 0; i < static_cast<int>(pattern.size()); ) {
        if (pattern[i] == pattern[len]) lps[i++] = ++len;
        else if (len) len = lps[len - 1];
        else lps[i++] = 0;
    }

    for (int i = 0, j = 0; i < static_cast<int>(text.size()); ) {
        if (text[i] == pattern[j]) { ++i; ++j; }
        if (j == static_cast<int>(pattern.size())) {
            matches.push_back(i - j);
            j = lps[j - 1];
        } else if (i < static_cast<int>(text.size()) && text[i] != pattern[j]) {
            if (j) j = lps[j - 1];
            else ++i;
        }
    }
    return matches;
}

std::vector<int> rabin_karp_search(const std::string& text, const std::string& pattern) {
    std::vector<int> matches;
    int n = static_cast<int>(text.size());
    int m = static_cast<int>(pattern.size());
    if (m > n || m == 0) return matches;

    const int d = 256;
    const int q = 101;

    int h = 1;
    for (int i = 0; i < m - 1; ++i) h = (h * d) % q;

    int p_hash = 0, t_hash = 0;
    for (int i = 0; i < m; ++i) {
        p_hash = (d * p_hash + pattern[i]) % q;
        t_hash = (d * t_hash + text[i]) % q;
    }

    for (int i = 0; i <= n - m; ++i) {
        if (p_hash == t_hash) {
            int j = 0;
            while (j < m && text[i + j] == pattern[j]) ++j;
            if (j == m) matches.push_back(i);
        }
        if (i < n - m) {
            t_hash = (d * (t_hash - text[i] * h) + text[i + m]) % q;
            if (t_hash < 0) t_hash += q;
        }
    }
    return matches;
}

std::vector<int> naive_search(const std::string& text, const std::string& pattern) {
    std::vector<int> matches;
    if (pattern.empty()) return matches;
    for (size_t i = 0; i <= text.size() - pattern.size(); ++i) {
        size_t j = 0;
        while (j < pattern.size() && text[i + j] == pattern[j]) ++j;
        if (j == pattern.size()) matches.push_back(static_cast<int>(i));
    }
    return matches;
}

std::vector<int> boyer_moore_search(const std::string& text, const std::string& pattern) {
    std::vector<int> matches;
    int n = static_cast<int>(text.size());
    int m = static_cast<int>(pattern.size());
    if (m == 0 || m > n) return matches;

    std::vector<int> bad_char(256, -1);
    for (int i = 0; i < m; ++i)
        bad_char[static_cast<unsigned char>(pattern[i])] = i;

    int shift = 0;
    while (shift <= n - m) {
        int j = m - 1;
        while (j >= 0 && pattern[j] == text[shift + j]) --j;
        if (j < 0) {
            matches.push_back(shift);
            shift += (shift + m < n) ? m - bad_char[static_cast<unsigned char>(text[shift + m])] : 1;
        } else {
            shift += std::max(1, j - bad_char[static_cast<unsigned char>(text[shift + j])]);
        }
    }
    return matches;
}

} // namespace pattern
