#ifndef GRAPH_ADJACENCY_H
#define GRAPH_ADJACENCY_H

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <functional>

template <typename T>
class Graph {
public:
    void add_vertex(const T& vertex);
    void add_edge(const T& from, const T& to, bool directed = false);
    void remove_edge(const T& from, const T& to);
    bool has_edge(const T& from, const T& to) const;
    bool has_vertex(const T& vertex) const;

    std::vector<T> bfs(const T& start) const;
    std::vector<T> dfs(const T& start) const;
    std::vector<T> topological_sort() const;

    size_t vertex_count() const { return adj_.size(); }
    size_t edge_count() const;

    void for_each_vertex(std::function<void(const T&)> func) const;
    void for_each_neighbor(const T& vertex, std::function<void(const T&)> func) const;

private:
    std::unordered_map<T, std::unordered_set<T>> adj_;
    bool directed_;
};

template <typename T>
void Graph<T>::add_vertex(const T& vertex) {
    if (!adj_.count(vertex)) adj_[vertex] = {};
}

template <typename T>
void Graph<T>::add_edge(const T& from, const T& to, bool directed) {
    directed_ = directed;
    add_vertex(from);
    add_vertex(to);
    adj_[from].insert(to);
    if (!directed) adj_[to].insert(from);
}

template <typename T>
void Graph<T>::remove_edge(const T& from, const T& to) {
    if (adj_.count(from)) adj_[from].erase(to);
    if (!directed_ && adj_.count(to)) adj_[to].erase(from);
}

template <typename T>
bool Graph<T>::has_edge(const T& from, const T& to) const {
    auto it = adj_.find(from);
    return it != adj_.end() && it->second.count(to);
}

template <typename T>
bool Graph<T>::has_vertex(const T& vertex) const {
    return adj_.count(vertex);
}

template <typename T>
std::vector<T> Graph<T>::bfs(const T& start) const {
    std::vector<T> result;
    if (!adj_.count(start)) return result;
    std::unordered_set<T> visited;
    std::queue<T> q;
    q.push(start);
    visited.insert(start);
    while (!q.empty()) {
        T v = q.front(); q.pop();
        result.push_back(v);
        for (const auto& n : adj_.at(v))
            if (!visited.count(n)) {
                visited.insert(n);
                q.push(n);
            }
    }
    return result;
}

template <typename T>
std::vector<T> Graph<T>::dfs(const T& start) const {
    std::vector<T> result;
    if (!adj_.count(start)) return result;
    std::unordered_set<T> visited;
    std::stack<T> s;
    s.push(start);
    while (!s.empty()) {
        T v = s.top(); s.pop();
        if (!visited.count(v)) {
            visited.insert(v);
            result.push_back(v);
            for (const auto& n : adj_.at(v))
                if (!visited.count(n)) s.push(n);
        }
    }
    return result;
}

template <typename T>
size_t Graph<T>::edge_count() const {
    size_t count = 0;
    for (auto& [_, neighbors] : adj_)
        count += neighbors.size();
    if (!directed_) count /= 2;
    return count;
}

template <typename T>
void Graph<T>::for_each_vertex(std::function<void(const T&)> func) const {
    for (auto& [v, _] : adj_) func(v);
}

template <typename T>
void Graph<T>::for_each_neighbor(const T& vertex, std::function<void(const T&)> func) const {
    auto it = adj_.find(vertex);
    if (it != adj_.end())
        for (const auto& n : it->second) func(n);
}

#endif
