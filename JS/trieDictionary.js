class TrieNode {
  constructor() {
    this.children = new Map();
    this.isEndOfWord = false;
  }
}

class Trie {
  constructor() {
    this.root = new TrieNode();
  }

  insert(word) {
    let node = this.root;
    for (const ch of word) {
      if (!node.children.has(ch)) {
        node.children.set(ch, new TrieNode());
      }
      node = node.children.get(ch);
    }
    node.isEndOfWord = true;
    return this;
  }

  search(word) {
    let node = this.root;
    for (const ch of word) {
      if (!node.children.has(ch)) return false;
      node = node.children.get(ch);
    }
    return node.isEndOfWord;
  }

  startsWith(prefix) {
    let node = this.root;
    for (const ch of prefix) {
      if (!node.children.has(ch)) return false;
      node = node.children.get(ch);
    }
    return true;
  }

  autocomplete(prefix) {
    const results = [];
    let node = this.root;
    for (const ch of prefix) {
      if (!node.children.has(ch)) return results;
      node = node.children.get(ch);
    }
    this._collectWords(node, prefix, results);
    return results;
  }

  _collectWords(node, prefix, results) {
    if (node.isEndOfWord) {
      results.push(prefix);
    }
    for (const [ch, child] of node.children) {
      this._collectWords(child, prefix + ch, results);
    }
  }
}

module.exports = { Trie };
