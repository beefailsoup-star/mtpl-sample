export interface GraphEdge<T> {
  from: T
  to: T
  weight?: number
}

export class Graph<T> {
  private adjacency = new Map<T, Map<T, number | undefined>>()

  addNode(node: T): void {
    if (!this.adjacency.has(node)) this.adjacency.set(node, new Map())
  }

  addEdge(from: T, to: T, weight?: number): void {
    this.addNode(from)
    this.addNode(to)
    this.adjacency.get(from)!.set(to, weight)
  }

  addUndirectedEdge(a: T, b: T, weight?: number): void {
    this.addEdge(a, b, weight)
    this.addEdge(b, a, weight)
  }

  hasNode(node: T): boolean {
    return this.adjacency.has(node)
  }

  hasEdge(from: T, to: T): boolean {
    return this.adjacency.get(from)?.has(to) ?? false
  }

  getNeighbors(node: T): Map<T, number | undefined> {
    return this.adjacency.get(node) ?? new Map()
  }

  getNodes(): T[] {
    return [...this.adjacency.keys()]
  }

  getEdges(): GraphEdge<T>[] {
    const edges: GraphEdge<T>[] = []
    for (const [from, neighbors] of this.adjacency) {
      for (const [to, weight] of neighbors) edges.push({ from, to, weight })
    }
    return edges
  }

  bfs(start: T, visit: (node: T) => void): void {
    const visited = new Set<T>()
    const queue: T[] = [start]
    visited.add(start)
    while (queue.length > 0) {
      const node = queue.shift()!
      visit(node)
      for (const neighbor of this.adjacency.get(node)?.keys() ?? []) {
        if (!visited.has(neighbor)) { visited.add(neighbor); queue.push(neighbor) }
      }
    }
  }

  dfs(start: T, visit: (node: T) => void): void {
    const visited = new Set<T>()
    const stack: T[] = [start]
    while (stack.length > 0) {
      const node = stack.pop()!
      if (visited.has(node)) continue
      visited.add(node)
      visit(node)
      for (const neighbor of this.adjacency.get(node)?.keys() ?? []) {
        if (!visited.has(neighbor)) stack.push(neighbor)
      }
    }
  }

  removeNode(node: T): void {
    this.adjacency.delete(node)
    for (const neighbors of this.adjacency.values()) neighbors.delete(node)
  }

  removeEdge(from: T, to: T): void {
    this.adjacency.get(from)?.delete(to)
  }
}
