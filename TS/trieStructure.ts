export class TrieNode<V> {
  children = new Map<string, TrieNode<V>>()
  value: V | null = null
  isEnd = false
}

export class Trie<V> {
  private root = new TrieNode<V>()

  insert(key: string, value: V): void {
    let node = this.root
    for (const ch of key) {
      if (!node.children.has(ch)) node.children.set(ch, new TrieNode())
      node = node.children.get(ch)!
    }
    node.isEnd = true
    node.value = value
  }

  search(key: string): V | null {
    const node = this.findNode(key)
    return node?.value ?? null
  }

  delete(key: string): boolean {
    const stack: { node: TrieNode<V>; ch: string }[] = []
    let node = this.root
    for (const ch of key) {
      if (!node.children.has(ch)) return false
      stack.push({ node, ch })
      node = node.children.get(ch)!
    }
    if (!node.isEnd) return false
    node.isEnd = false
    node.value = null

    for (let i = stack.length - 1; i >= 0; i--) {
      const { node: parent, ch } = stack[i]
      const child = parent.children.get(ch)!
      if (!child.isEnd && child.children.size === 0) parent.children.delete(ch)
      else break
    }
    return true
  }

  startsWith(prefix: string): boolean {
    return this.findNode(prefix) !== null
  }

  findKeysWithPrefix(prefix: string): string[] {
    const node = this.findNode(prefix)
    if (!node) return []
    const results: string[] = []
    this.collect(node, prefix, results)
    return results
  }

  private findNode(key: string): TrieNode<V> | null {
    let node = this.root
    for (const ch of key) {
      if (!node.children.has(ch)) return null
      node = node.children.get(ch)!
    }
    return node
  }

  private collect(node: TrieNode<V>, prefix: string, results: string[]): void {
    if (node.isEnd) results.push(prefix)
    for (const [ch, child] of node.children) this.collect(child, prefix + ch, results)
  }
}
