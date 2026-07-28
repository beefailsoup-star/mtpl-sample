'use strict';

const validator = {
  isEmail(str) {
    if (typeof str !== 'string') return false;
    return /^[^\s@]+@[^\s@]+\.[^\s@]+$/.test(str);
  },

  isPhone(str) {
    if (typeof str !== 'string') return false;
    const cleaned = str.replace(/[\s\-\+\(\)\.]/g, '');
    return /^\d{7,15}$/.test(cleaned);
  },

  isURL(str) {
    if (typeof str !== 'string') return false;
    try {
      new URL(str);
      return true;
    } catch {
      return false;
    }
  },

  isIP(str) {
    if (typeof str !== 'string') return false;
    const ipv4 = /^(\d{1,3})\.(\d{1,3})\.(\d{1,3})\.(\d{1,3})$/;
    const match = str.match(ipv4);
    if (match) {
      return match.slice(1).every(octet => parseInt(octet, 10) >= 0 && parseInt(octet, 10) <= 255);
    }
    const ipv6 = /^([0-9a-fA-F]{1,4}:){7}[0-9a-fA-F]{1,4}$/;
    return ipv6.test(str);
  },

  isUUID(str) {
    if (typeof str !== 'string') return false;
    return /^[0-9a-f]{8}-[0-9a-f]{4}-[1-5][0-9a-f]{3}-[89ab][0-9a-f]{3}-[0-9a-f]{12}$/i.test(str);
  },

  isStrongPassword(str) {
    if (typeof str !== 'string') return false;
    if (str.length < 8) return false;
    if (!/[A-Z]/.test(str)) return false;
    if (!/[a-z]/.test(str)) return false;
    if (!/[0-9]/.test(str)) return false;
    if (!/[^A-Za-z0-9]/.test(str)) return false;
    return true;
  }
};

module.exports = validator;
