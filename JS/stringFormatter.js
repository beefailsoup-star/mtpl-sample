'use strict';

const stringFormatter = {
  capitalize(str) {
    if (!str) return '';
    return str.charAt(0).toUpperCase() + str.slice(1).toLowerCase();
  },

  truncate(str, maxLen = 30, suffix = '...') {
    if (!str || str.length <= maxLen) return str || '';
    return str.slice(0, maxLen - suffix.length) + suffix;
  },

  slugify(str) {
    if (!str) return '';
    return str
      .toLowerCase()
      .trim()
      .replace(/[^\w\s-]/g, '')
      .replace(/[\s_]+/g, '-')
      .replace(/-+/g, '-')
      .replace(/^-|-$/g, '');
  },

  camelCase(str) {
    if (!str) return '';
    return str
      .replace(/[^a-zA-Z0-9]+(.)/g, (_, ch) => ch.toUpperCase())
      .replace(/^[A-Z]/, ch => ch.toLowerCase());
  },

  snakeCase(str) {
    if (!str) return '';
    return str
      .replace(/[A-Z]/g, ch => '_' + ch.toLowerCase())
      .replace(/[^a-zA-Z0-9]+/g, '_')
      .replace(/_+/g, '_')
      .replace(/^_|_$/g, '')
      .toLowerCase();
  },

  kebabCase(str) {
    if (!str) return '';
    return str
      .replace(/[A-Z]/g, ch => '-' + ch.toLowerCase())
      .replace(/[^a-zA-Z0-9]+/g, '-')
      .replace(/-+/g, '-')
      .replace(/^-|-$/g, '')
      .toLowerCase();
  }
};

module.exports = stringFormatter;
