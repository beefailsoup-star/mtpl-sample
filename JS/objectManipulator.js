'use strict';

const objectManipulator = {
  deepClone(obj) {
    if (obj === null || typeof obj !== 'object') return obj;
    if (obj instanceof Date) return new Date(obj);
    if (obj instanceof Array) return obj.map(item => this.deepClone(item));
    const cloned = {};
    for (const key of Object.keys(obj)) {
      cloned[key] = this.deepClone(obj[key]);
    }
    return cloned;
  },

  deepMerge(target, ...sources) {
    const result = this.deepClone(target);
    for (const source of sources) {
      if (!source || typeof source !== 'object') continue;
      for (const key of Object.keys(source)) {
        const srcVal = source[key];
        const resVal = result[key];
        if (srcVal && typeof srcVal === 'object' && !Array.isArray(srcVal) &&
            resVal && typeof resVal === 'object' && !Array.isArray(resVal)) {
          result[key] = this.deepMerge(resVal, srcVal);
        } else {
          result[key] = this.deepClone(srcVal);
        }
      }
    }
    return result;
  },

  pick(obj, ...keys) {
    if (!obj) return {};
    const keyArr = Array.isArray(keys[0]) ? keys[0] : keys;
    const result = {};
    for (const key of keyArr) {
      if (Object.prototype.hasOwnProperty.call(obj, key)) {
        result[key] = obj[key];
      }
    }
    return result;
  },

  omit(obj, ...keys) {
    if (!obj) return {};
    const keyArr = Array.isArray(keys[0]) ? keys[0] : keys;
    const result = {};
    for (const key of Object.keys(obj)) {
      if (!keyArr.includes(key)) {
        result[key] = obj[key];
      }
    }
    return result;
  },

  isEmpty(obj) {
    if (obj == null) return true;
    return Object.keys(obj).length === 0;
  },

  get(obj, path, defaultValue) {
    if (!obj || !path) return defaultValue;
    const keys = Array.isArray(path) ? path : path.split('.');
    let current = obj;
    for (const key of keys) {
      if (current == null || !Object.prototype.hasOwnProperty.call(current, key)) {
        return defaultValue;
      }
      current = current[key];
    }
    return current;
  },

  set(obj, path, value) {
    if (!obj || !path) return obj;
    const keys = Array.isArray(path) ? path : path.split('.');
    let current = obj;
    for (let i = 0; i < keys.length - 1; i++) {
      if (!Object.prototype.hasOwnProperty.call(current, keys[i]) ||
          typeof current[keys[i]] !== 'object') {
        current[keys[i]] = {};
      }
      current = current[keys[i]];
    }
    current[keys[keys.length - 1]] = value;
    return obj;
  }
};

module.exports = objectManipulator;
