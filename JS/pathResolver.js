'use strict';

const path = require('path');

const pathResolver = {
  join(...segments) {
    return path.join(...segments);
  },

  resolve(...segments) {
    return path.resolve(...segments);
  },

  normalize(p) {
    return path.normalize(p);
  },

  relative(from, to) {
    return path.relative(from, to);
  },

  basename(p, ext) {
    return path.basename(p, ext);
  },

  dirname(p) {
    return path.dirname(p);
  },

  extname(p) {
    return path.extname(p);
  }
};

module.exports = pathResolver;
