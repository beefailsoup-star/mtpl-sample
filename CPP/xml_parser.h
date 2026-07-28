#ifndef XML_PARSER_H
#define XML_PARSER_H

#include <string>
#include <vector>
#include <map>
#include <memory>

class XmlNode {
public:
    using Attributes = std::map<std::string, std::string>;
    using Children = std::vector<std::shared_ptr<XmlNode>>;

    std::string name;
    Attributes attributes;
    Children children;
    std::string content;

    XmlNode* find_first(const std::string& tag_name) const;
    std::vector<XmlNode*> find_all(const std::string& tag_name) const;
    std::string attr(const std::string& key, const std::string& default_val = {}) const;

    std::string serialize(int indent = 0) const;
};

class XmlParser {
public:
    static std::shared_ptr<XmlNode> parse(const std::string& input);
    static std::shared_ptr<XmlNode> parse_file(const std::string& path);

private:
    XmlParser(const std::string& input) : input_(input), pos_(0) {}
    std::shared_ptr<XmlNode> parse_node();
    std::string parse_tag_name();
    XmlNode::Attributes parse_attributes();
    std::string parse_attribute_value();
    void skip_whitespace();
    char peek() const;
    char next();
    void expect(char c);

    const std::string& input_;
    size_t pos_;
};

#endif
