function isObject(val) {
  return val !== null && typeof val === 'object' && !Array.isArray(val);
}

function deepDiff(obj1, obj2, path = '') {
  const changes = [];

  if (obj1 === obj2) return changes;

  if (typeof obj1 !== typeof obj2) {
    changes.push({ path, oldValue: obj1, newValue: obj2, type: 'changed' });
    return changes;
  }

  if (!isObject(obj1) && !Array.isArray(obj1)) {
    if (obj1 !== obj2) {
      changes.push({ path, oldValue: obj1, newValue: obj2, type: 'changed' });
    }
    return changes;
  }

  if (Array.isArray(obj1) && Array.isArray(obj2)) {
    const maxLen = Math.max(obj1.length, obj2.length);
    for (let i = 0; i < maxLen; i++) {
      const itemPath = path ? `${path}[${i}]` : `[${i}]`;
      if (i >= obj1.length) {
        changes.push({ path: itemPath, oldValue: undefined, newValue: obj2[i], type: 'added' });
      } else if (i >= obj2.length) {
        changes.push({ path: itemPath, oldValue: obj1[i], newValue: undefined, type: 'removed' });
      } else {
        changes.push(...deepDiff(obj1[i], obj2[i], itemPath));
      }
    }
    return changes;
  }

  if (isObject(obj1) && isObject(obj2)) {
    const allKeys = new Set([...Object.keys(obj1), ...Object.keys(obj2)]);
    for (const key of allKeys) {
      const keyPath = path ? `${path}.${key}` : key;
      if (!(key in obj1)) {
        changes.push({ path: keyPath, oldValue: undefined, newValue: obj2[key], type: 'added' });
      } else if (!(key in obj2)) {
        changes.push({ path: keyPath, oldValue: obj1[key], newValue: undefined, type: 'removed' });
      } else {
        changes.push(...deepDiff(obj1[key], obj2[key], keyPath));
      }
    }
    return changes;
  }

  return changes;
}

function diffObjects(obj1, obj2) {
  if (!isObject(obj1) || !isObject(obj2)) {
    throw new Error('Both arguments must be objects');
  }
  return deepDiff(obj1, obj2);
}

function diffArrays(arr1, arr2) {
  if (!Array.isArray(arr1) || !Array.isArray(arr2)) {
    throw new Error('Both arguments must be arrays');
  }
  return deepDiff(arr1, arr2);
}

module.exports = { diffObjects, diffArrays, deepDiff };
