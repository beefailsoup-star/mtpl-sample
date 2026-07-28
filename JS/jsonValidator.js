'use strict';

const jsonValidator = {
  isValidJSON(str) {
    if (typeof str !== 'string') return false;
    try {
      JSON.parse(str);
      return true;
    } catch {
      return false;
    }
  },

  formatJSON(str, spaces = 2) {
    if (typeof str !== 'string') return '';
    try {
      const parsed = JSON.parse(str);
      return JSON.stringify(parsed, null, spaces);
    } catch {
      return '';
    }
  },

  minifyJSON(str) {
    if (typeof str !== 'string') return '';
    try {
      const parsed = JSON.parse(str);
      return JSON.stringify(parsed);
    } catch {
      return '';
    }
  },

  safeParse(str, fallback = null) {
    try {
      return JSON.parse(str);
    } catch {
      return fallback;
    }
  }
};

module.exports = jsonValidator;
