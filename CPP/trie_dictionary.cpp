#include "trie_dictionary.h"

TrieDictionary::~TrieDictionary() {
    delete_node(root_);
}

void TrieDictionary::delete_node(Node* node) {
    for (auto& [ch, child] : node->children)
        delete_node(child);
    delete node;
}

void TrieDictionary::insert(const std::string& word) {
    Node* node = root_;
    for (char c : word) {
        if (!node->children.count(c))
            node->children[c] = new Node();
        node = node->children[c];
    }
    if (!node->is_end) {
        node->is_end = true;
        ++count_;
    }
}

bool TrieDictionary::search(const std::string& word) const {
    Node* node = root_;
    for (char c : word) {
        auto it = node->children.find(c);
        if (it == node->children.end()) return false;
        node = it->second;
    }
    return node->is_end;
}

bool TrieDictionary::starts_with(const std::string& prefix) const {
    Node* node = root_;
    for (char c : prefix) {
        auto it = node->children.find(c);
        if (it == node->children.end()) return false;
        node = it->second;
    }
    return true;
}

void TrieDictionary::remove(const std::string& word) {
    if (!search(word)) return;
    Node* node = root_;
    for (char c : word)
        node = node->children[c];
    node->is_end = false;
    --count_;
}

std::vector<std::string> TrieDictionary::autocomplete(const std::string& prefix) const {
    Node* node = root_;
    for (char c : prefix) {
        auto it = node->children.find(c);
        if (it == node->children.end()) return {};
        node = it->second;
    }
    std::vector<std::string> results;
    std::string current = prefix;
    collect_words(node, current, results);
    return results;
}

void TrieDictionary::collect_words(Node* node, std::string& prefix, std::vector<std::string>& results) const {
    if (node->is_end) results.push_back(prefix);
    for (auto& [ch, child] : node->children) {
        prefix.push_back(ch);
        collect_words(child, prefix, results);
        prefix.pop_back();
    }
}

bool TrieDictionary::has_children(Node* node) const {
    return !node->children.empty();
}
