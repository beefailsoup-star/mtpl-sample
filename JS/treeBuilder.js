function buildTree(items, idKey = 'id', parentKey = 'parentId', childrenKey = 'children') {
  const map = new Map();
  const roots = [];

  for (const item of items) {
    map.set(item[idKey], { ...item, [childrenKey]: [] });
  }

  for (const item of items) {
    if (item[parentKey] != null && map.has(item[parentKey])) {
      map.get(item[parentKey])[childrenKey].push(map.get(item[idKey]));
    } else {
      roots.push(map.get(item[idKey]));
    }
  }

  return roots;
}

function flattenTree(tree, childrenKey = 'children') {
  const result = [];
  function walk(nodes) {
    for (const node of nodes) {
      const { [childrenKey]: children, ...rest } = node;
      result.push(rest);
      if (children && children.length) {
        walk(children);
      }
    }
  }
  walk(tree);
  return result;
}

function findInTree(tree, predicate, childrenKey = 'children') {
  for (const node of tree) {
    if (predicate(node)) return node;
    if (node[childrenKey] && node[childrenKey].length) {
      const found = findInTree(node[childrenKey], predicate, childrenKey);
      if (found) return found;
    }
  }
  return null;
}

function treeToArray(tree, childrenKey = 'children') {
  const result = [];
  function walk(nodes, depth = 0) {
    for (const node of nodes) {
      const { [childrenKey]: children, ...rest } = node;
      result.push({ ...rest, depth });
      if (children && children.length) {
        walk(children, depth + 1);
      }
    }
  }
  walk(tree);
  return result;
}

module.exports = { buildTree, flattenTree, findInTree, treeToArray };
