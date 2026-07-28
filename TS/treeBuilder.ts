export interface TreeNode<T> {
  data: T
  children: TreeNode<T>[]
}

export interface FlatNode<T> {
  id: string | number
  parentId: string | number | null
  data: T
}

export function buildTree<T>(
  flat: FlatNode<T>[],
  options?: { idKey?: string; parentIdKey?: string }
): TreeNode<T>[] {
  const nodeMap = new Map<string | number, TreeNode<T>>()
  const roots: TreeNode<T>[] = []

  for (const item of flat) {
    if (!nodeMap.has(item.id)) {
      nodeMap.set(item.id, { data: item.data, children: [] })
    }
  }

  for (const item of flat) {
    const node = nodeMap.get(item.id)!
    if (item.parentId === null || item.parentId === undefined) {
      roots.push(node)
    } else {
      const parent = nodeMap.get(item.parentId)
      if (parent) parent.children.push(node)
    }
  }

  return roots
}

export function flattenTree<T>(roots: TreeNode<T>[]): FlatNode<T>[] {
  const result: FlatNode<T>[] = []
  let idCounter = 0

  function walk(nodes: TreeNode<T>[], parentId: string | number | null): void {
    for (const node of nodes) {
      const id = ++idCounter
      result.push({ id, parentId, data: node.data })
      walk(node.children, id)
    }
  }

  walk(roots, null)
  return result
}

export function findInTree<T>(roots: TreeNode<T>[], predicate: (data: T) => boolean): TreeNode<T> | null {
  for (const node of roots) {
    if (predicate(node.data)) return node
    const found = findInTree(node.children, predicate)
    if (found) return found
  }
  return null
}

export function mapTree<T, R>(roots: TreeNode<T>[], fn: (data: T) => R): TreeNode<R>[] {
  return roots.map(node => ({
    data: fn(node.data),
    children: mapTree(node.children, fn),
  }))
}
