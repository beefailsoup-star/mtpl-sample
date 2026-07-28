using System;
using System.Collections.Generic;
using System.Linq;

namespace MtplSample
{
    public class GraphSearch
    {
        private readonly Dictionary<int, List<int>> _adjacency = new();

        public void AddEdge(int from, int to)
        {
            if (!_adjacency.ContainsKey(from)) _adjacency[from] = new List<int>();
            if (!_adjacency.ContainsKey(to)) _adjacency[to] = new List<int>();
            _adjacency[from].Add(to);
            _adjacency[to].Add(from);
        }

        public List<int> Bfs(int start)
        {
            var visited = new HashSet<int>();
            var queue = new Queue<int>();
            var result = new List<int>();

            visited.Add(start);
            queue.Enqueue(start);

            while (queue.Count > 0)
            {
                var current = queue.Dequeue();
                result.Add(current);

                if (!_adjacency.ContainsKey(current)) continue;
                foreach (var neighbor in _adjacency[current])
                {
                    if (visited.Add(neighbor))
                        queue.Enqueue(neighbor);
                }
            }

            return result;
        }

        public List<int> Dfs(int start)
        {
            var visited = new HashSet<int>();
            var result = new List<int>();
            DfsRecursive(start, visited, result);
            return result;
        }

        private void DfsRecursive(int node, HashSet<int> visited, List<int> result)
        {
            visited.Add(node);
            result.Add(node);

            if (!_adjacency.ContainsKey(node)) return;
            foreach (var neighbor in _adjacency[node])
            {
                if (!visited.Contains(neighbor))
                    DfsRecursive(neighbor, visited, result);
            }
        }

        public bool HasPath(int from, int to)
        {
            var visited = new HashSet<int>();
            var stack = new Stack<int>();
            stack.Push(from);

            while (stack.Count > 0)
            {
                var current = stack.Pop();
                if (current == to) return true;
                if (!visited.Add(current)) continue;
                if (!_adjacency.ContainsKey(current)) continue;
                foreach (var neighbor in _adjacency[current])
                {
                    if (!visited.Contains(neighbor))
                        stack.Push(neighbor);
                }
            }
            return false;
        }

        public Dictionary<int, int> ShortestPaths(int start)
        {
            var distances = new Dictionary<int, int>();
            var visited = new HashSet<int>();
            var queue = new Queue<(int Node, int Dist)>();

            queue.Enqueue((start, 0));
            visited.Add(start);

            while (queue.Count > 0)
            {
                var (node, dist) = queue.Dequeue();
                distances[node] = dist;

                if (!_adjacency.ContainsKey(node)) continue;
                foreach (var neighbor in _adjacency[node])
                {
                    if (visited.Add(neighbor))
                        queue.Enqueue((neighbor, dist + 1));
                }
            }

            return distances;
        }
    }
}
