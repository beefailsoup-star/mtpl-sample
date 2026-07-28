export class BSTNode<T> {
  value: T
  left: BSTNode<T> | null = null
  right: BSTNode<T> | null = null

  constructor(value: T) {
    this.value = value
  }
}

export class BinarySearchTree<T> {
  private root: BSTNode<T> | null = null
  private compareFn: (a: T, b: T) => number

  constructor(compareFn?: (a: T, b: T) => number) {
    this.compareFn = compareFn ?? ((a: T, b: T) => a < b ? -1 : a > b ? 1 : 0)
  }

  insert(value: T): void {
    this.root = this.insertNode(this.root, value)
  }

  private insertNode(node: BSTNode<T> | null, value: T): BSTNode<T> {
    if (!node) return new BSTNode(value)
    const cmp = this.compareFn(value, node.value)
    if (cmp < 0) node.left = this.insertNode(node.left, value)
    else if (cmp > 0) node.right = this.insertNode(node.right, value)
    return node
  }

  search(value: T): boolean {
    let current = this.root
    while (current) {
      const cmp = this.compareFn(value, current.value)
      if (cmp === 0) return true
      current = cmp < 0 ? current.left : current.right
    }
    return false
  }

  delete(value: T): void {
    this.root = this.deleteNode(this.root, value)
  }

  private deleteNode(node: BSTNode<T> | null, value: T): BSTNode<T> | null {
    if (!node) return null
    const cmp = this.compareFn(value, node.value)
    if (cmp < 0) { node.left = this.deleteNode(node.left, value); return node }
    if (cmp > 0) { node.right = this.deleteNode(node.right, value); return node }

    if (!node.left) return node.right
    if (!node.right) return node.left

    const minNode = this.findMin(node.right)
    node.value = minNode.value
    node.right = this.deleteNode(node.right, minNode.value)
    return node
  }

  private findMin(node: BSTNode<T>): BSTNode<T> {
    while (node.left) node = node.left
    return node
  }

  inOrder(): T[] {
    const result: T[] = []
    this.inOrderTraverse(this.root, result)
    return result
  }

  private inOrderTraverse(node: BSTNode<T> | null, result: T[]): void {
    if (!node) return
    this.inOrderTraverse(node.left, result)
    result.push(node.value)
    this.inOrderTraverse(node.right, result)
  }

  preOrder(): T[] {
    const result: T[] = []
    this.preOrderTraverse(this.root, result)
    return result
  }

  private preOrderTraverse(node: BSTNode<T> | null, result: T[]): void {
    if (!node) return
    result.push(node.value)
    this.preOrderTraverse(node.left, result)
    this.preOrderTraverse(node.right, result)
  }

  postOrder(): T[] {
    const result: T[] = []
    this.postOrderTraverse(this.root, result)
    return result
  }

  private postOrderTraverse(node: BSTNode<T> | null, result: T[]): void {
    if (!node) return
    this.postOrderTraverse(node.left, result)
    this.postOrderTraverse(node.right, result)
    result.push(node.value)
  }

  min(): T | null {
    if (!this.root) return null
    let current = this.root
    while (current.left) current = current.left
    return current.value
  }

  max(): T | null {
    if (!this.root) return null
    let current = this.root
    while (current.right) current = current.right
    return current.value
  }
}
