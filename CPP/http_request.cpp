#include "http_request.h"
#include <sstream>
#include <algorithm>

HttpRequest::HttpRequest() : method_(GET) {}

void HttpRequest::set_url(const std::string& url) { url_ = url; }

void HttpRequest::set_method(Method method) { method_ = method; }

void HttpRequest::set_header(const std::string& key, const std::string& value) {
    headers_[key] = value;
}

void HttpRequest::set_body(const std::string& body) { body_ = body; }

void HttpRequest::set_param(const std::string& key, const std::string& value) {
    params_[key] = value;
}

std::string HttpRequest::build_query_string() const {
    std::string qs;
    for (auto it = params_.begin(); it != params_.end(); ++it) {
        if (!qs.empty()) qs += "&";
        qs += it->first + "=" + it->second;
    }
    return qs;
}

std::string HttpRequest::build() const {
    std::ostringstream req;
    std::string path = url_;
    auto qs = build_query_string();
    if (!qs.empty()) path += "?" + qs;
    req << method_to_string(method_) << " " << path << " HTTP/1.1\r\n";
    for (auto& [k, v] : headers_)
        req << k << ": " << v << "\r\n";
    if (!body_.empty())
        req << "Content-Length: " << body_.size() << "\r\n";
    req << "\r\n";
    if (!body_.empty())
        req << body_;
    return req.str();
}

HttpRequest::Method HttpRequest::method_from_string(const std::string& s) {
    std::string u = s;
    std::transform(u.begin(), u.end(), u.begin(), ::toupper);
    if (u == "GET") return GET;
    if (u == "POST") return POST;
    if (u == "PUT") return PUT;
    if (u == "DELETE") return DELETE;
    if (u == "PATCH") return PATCH;
    return GET;
}

std::string HttpRequest::method_to_string(Method m) {
    switch (m) {
    case GET: return "GET";
    case POST: return "POST";
    case PUT: return "PUT";
    case DELETE: return "DELETE";
    case PATCH: return "PATCH";
    }
    return "GET";
}
