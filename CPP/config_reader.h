#ifndef CONFIG_READER_H
#define CONFIG_READER_H

#include <string>
#include <unordered_map>
#include <any>
#include <vector>

class ConfigReader {
public:
    ConfigReader() = default;
    ~ConfigReader() = default;

    bool load_json(const std::string& path);
    bool load_ini(const std::string& path);
    bool load_env(const std::string& path);

    template <typename T>
    T get(const std::string& key, const T& default_val = {}) const {
        auto it = data_.find(key);
        if (it == data_.end()) return default_val;
        try {
            return std::any_cast<T>(it->second);
        } catch (...) {
            return default_val;
        }
    }

    bool has(const std::string& key) const;
    void set(const std::string& key, const std::any& value);
    void remove(const std::string& key);
    void clear();

    std::vector<std::string> keys() const;

private:
    std::unordered_map<std::string, std::any> data_;
};

#endif
