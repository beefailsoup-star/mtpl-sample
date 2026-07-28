class Graph {
  constructor() {
    this.adjList = new Map();
  }

  addVertex(vertex) {
    if (!this.adjList.has(vertex)) {
      this.adjList.set(vertex, []);
    }
    return this;
  }

  addEdge(v1, v2, weight = 1) {
    if (!this.adjList.has(v1)) this.addVertex(v1);
    if (!this.adjList.has(v2)) this.addVertex(v2);
    this.adjList.get(v1).push({ node: v2, weight });
    this.adjList.get(v2).push({ node: v1, weight });
    return this;
  }

  bfs(start) {
    const visited = new Set();
    const queue = [start];
    const result = [];
    visited.add(start);

    while (queue.length) {
      const vertex = queue.shift();
      result.push(vertex);
      for (const neighbor of this.adjList.get(vertex) || []) {
        if (!visited.has(neighbor.node)) {
          visited.add(neighbor.node);
          queue.push(neighbor.node);
        }
      }
    }
    return result;
  }

  dfs(start) {
    const visited = new Set();
    const result = [];

    const traverse = (vertex) => {
      if (!vertex || visited.has(vertex)) return;
      visited.add(vertex);
      result.push(vertex);
      for (const neighbor of this.adjList.get(vertex) || []) {
        traverse(neighbor.node);
      }
    };

    traverse(start);
    return result;
  }

  hasPath(v1, v2) {
    if (v1 === v2) return true;
    const visited = new Set();
    const queue = [v1];
    visited.add(v1);

    while (queue.length) {
      const vertex = queue.shift();
      for (const neighbor of this.adjList.get(vertex) || []) {
        if (neighbor.node === v2) return true;
        if (!visited.has(neighbor.node)) {
          visited.add(neighbor.node);
          queue.push(neighbor.node);
        }
      }
    }
    return false;
  }

  shortestPath(v1, v2) {
    if (v1 === v2) return [v1];
    const visited = new Set([v1]);
    const queue = [[v1]];

    while (queue.length) {
      const path = queue.shift();
      const vertex = path[path.length - 1];
      for (const neighbor of this.adjList.get(vertex) || []) {
        if (!visited.has(neighbor.node)) {
          const newPath = [...path, neighbor.node];
          if (neighbor.node === v2) return newPath;
          visited.add(neighbor.node);
          queue.push(newPath);
        }
      }
    }
    return null;
  }
}

module.exports = { Graph };
