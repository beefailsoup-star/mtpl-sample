#ifndef TRIE_DICTIONARY_H
#define TRIE_DICTIONARY_H

#include <unordered_map>
#include <string>
#include <vector>

class TrieDictionary {
public:
    TrieDictionary() = default;
    ~TrieDictionary();

    TrieDictionary(const TrieDictionary&) = delete;
    TrieDictionary& operator=(const TrieDictionary&) = delete;

    void insert(const std::string& word);
    bool search(const std::string& word) const;
    bool starts_with(const std::string& prefix) const;
    void remove(const std::string& word);
    std::vector<std::string> autocomplete(const std::string& prefix) const;
    size_t word_count() const { return count_; }
    bool empty() const { return count_ == 0; }

private:
    struct Node {
        std::unordered_map<char, Node*> children;
        bool is_end;
        Node() : is_end(false) {}
    };

    Node* root_ = new Node();
    size_t count_ = 0;

    void collect_words(Node* node, std::string& prefix, std::vector<std::string>& results) const;
    bool has_children(Node* node) const;
    void delete_node(Node* node);
};

#endif
