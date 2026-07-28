#include "xml_parser.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

XmlNode* XmlNode::find_first(const std::string& tag_name) const {
    for (auto& child : children)
        if (child->name == tag_name) return child.get();
    for (auto& child : children) {
        auto found = child->find_first(tag_name);
        if (found) return found;
    }
    return nullptr;
}

std::vector<XmlNode*> XmlNode::find_all(const std::string& tag_name) const {
    std::vector<XmlNode*> results;
    for (auto& child : children) {
        if (child->name == tag_name) results.push_back(child.get());
        auto nested = child->find_all(tag_name);
        results.insert(results.end(), nested.begin(), nested.end());
    }
    return results;
}

std::string XmlNode::attr(const std::string& key, const std::string& default_val) const {
    auto it = attributes.find(key);
    return it != attributes.end() ? it->second : default_val;
}

std::string XmlNode::serialize(int indent) const {
    std::string pad(indent, ' ');
    std::string s = pad + "<" + name;
    for (auto& [k, v] : attributes) s += " " + k + "=\"" + v + "\"";
    if (children.empty() && content.empty()) return s + "/>\n";
    s += ">";
    if (!children.empty()) {
        s += "\n";
        for (auto& child : children) s += child->serialize(indent + 2);
        s += pad;
    } else {
        s += content;
    }
    return s + "</" + name + ">\n";
}

std::shared_ptr<XmlNode> XmlParser::parse(const std::string& input) {
    XmlParser p(input);
    p.skip_whitespace();
    return p.parse_node();
}

std::shared_ptr<XmlNode> XmlParser::parse_file(const std::string& path) {
    std::ifstream f(path);
    if (!f) throw std::runtime_error("Cannot open file: " + path);
    std::ostringstream ss;
    ss << f.rdbuf();
    return parse(ss.str());
}

char XmlParser::peek() const {
    if (pos_ >= input_.size()) return '\0';
    return input_[pos_];
}

char XmlParser::next() {
    if (pos_ >= input_.size()) throw std::runtime_error("Unexpected end of input");
    return input_[pos_++];
}

void XmlParser::skip_whitespace() {
    while (pos_ < input_.size() && std::isspace(input_[pos_])) ++pos_;
}

void XmlParser::expect(char c) {
    if (next() != c) throw std::runtime_error(std::string("Expected '") + c + "'");
}

std::shared_ptr<XmlNode> XmlParser::parse_node() {
    auto node = std::make_shared<XmlNode>();
    expect('<');
    if (peek() == '/') return nullptr;
    node->name = parse_tag_name();
    node->attributes = parse_attributes();
    skip_whitespace();
    if (peek() == '/') { next(); expect('>'); return node; }
    expect('>');
    while (pos_ < input_.size() && peek() != '<') {
        node->content += next();
    }
    while (peek() == '<') {
        if (input_.substr(pos_, 2) == "</") {
            pos_ += 2;
            std::string closing = parse_tag_name();
            skip_whitespace();
            expect('>');
            return node;
        }
        node->children.push_back(parse_node());
    }
    return node;
}

std::string XmlParser::parse_tag_name() {
    skip_whitespace();
    std::string name;
    while (pos_ < input_.size() && (std::isalnum(input_[pos_]) || input_[pos_] == '_' || input_[pos_] == '-'))
        name += next();
    if (name.empty()) throw std::runtime_error("Expected tag name");
    return name;
}

XmlNode::Attributes XmlParser::parse_attributes() {
    XmlNode::Attributes attrs;
    while (true) {
        skip_whitespace();
        if (peek() == '>' || peek() == '/') break;
        std::string key = parse_tag_name();
        skip_whitespace();
        expect('=');
        std::string val = parse_attribute_value();
        attrs[key] = val;
    }
    return attrs;
}

std::string XmlParser::parse_attribute_value() {
    if (peek() != '"') throw std::runtime_error("Expected '\"'");
    next();
    std::string val;
    while (pos_ < input_.size() && peek() != '"')
        val += next();
    if (peek() == '"') next();
    return val;
}
