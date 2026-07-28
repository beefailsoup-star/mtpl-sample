'use strict';

class LRUCache {
  constructor(maxSize = 100) {
    this.maxSize = maxSize;
    this._cache = new Map();
  }

  get(key) {
    if (!this._cache.has(key)) return undefined;
    const value = this._cache.get(key);
    this._cache.delete(key);
    this._cache.set(key, value);
    return value;
  }

  set(key, value) {
    if (this._cache.has(key)) {
      this._cache.delete(key);
    } else if (this._cache.size >= this.maxSize) {
      this._cache.delete(this._cache.keys().next().value);
    }
    this._cache.set(key, value);
  }

  has(key) {
    return this._cache.has(key);
  }

  delete(key) {
    return this._cache.delete(key);
  }

  clear() {
    this._cache.clear();
  }

  size() {
    return this._cache.size;
  }
}

function memoize(fn, options = {}) {
  const cache = options.cache || new Map();
  const maxSize = options.maxSize || Infinity;
  const resolver = options.resolver || ((...args) => JSON.stringify(args));

  const memoized = function (...args) {
    const key = resolver(...args);
    if (cache.has(key)) {
      return cache.get(key);
    }
    const result = fn.apply(this, args);
    if (cache.size >= maxSize) {
      const firstKey = cache.keys().next().value;
      cache.delete(firstKey);
    }
    cache.set(key, result);
    return result;
  };

  memoized.cache = cache;
  return memoized;
}

module.exports = { LRUCache, memoize };
