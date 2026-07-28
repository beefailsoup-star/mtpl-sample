#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

#include <string>
#include <map>
#include <vector>

class HttpRequest {
public:
    enum Method { GET, POST, PUT, DELETE, PATCH };

    HttpRequest();
    ~HttpRequest() = default;

    void set_url(const std::string& url);
    void set_method(Method method);
    void set_header(const std::string& key, const std::string& value);
    void set_body(const std::string& body);
    void set_param(const std::string& key, const std::string& value);

    std::string build() const;
    std::string url() const { return url_; }
    Method method() const { return method_; }

    static Method method_from_string(const std::string& s);
    static std::string method_to_string(Method m);

private:
    std::string url_;
    Method method_;
    std::map<std::string, std::string> headers_;
    std::string body_;
    std::map<std::string, std::string> params_;

    std::string build_query_string() const;
};

#endif
