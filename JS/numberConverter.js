'use strict';

const numberConverter = {
  toBinary(num) {
    if (num === undefined || num === null) return '';
    return (num >>> 0).toString(2);
  },

  toOctal(num) {
    if (num === undefined || num === null) return '';
    return (num >>> 0).toString(8);
  },

  toHex(num) {
    if (num === undefined || num === null) return '';
    return (num >>> 0).toString(16);
  },

  fromBinary(str) {
    if (!str) return NaN;
    return parseInt(str.replace(/[^01]/g, ''), 2);
  },

  formatCurrency(amount, locale = 'en-US', currency = 'USD') {
    if (amount === null || amount === undefined || isNaN(amount)) return '';
    return new Intl.NumberFormat(locale, { style: 'currency', currency }).format(amount);
  },

  toOrdinal(n) {
    if (typeof n !== 'number' || !Number.isInteger(n)) return '';
    const s = ['th', 'st', 'nd', 'rd'];
    const v = n % 100;
    return n + (s[(v - 20) % 10] || s[v] || s[0]);
  },

  clamp(value, min, max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
  }
};

module.exports = numberConverter;
