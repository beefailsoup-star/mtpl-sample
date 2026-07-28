'use strict';

const crypto = require('crypto');

const cryptoUtils = {
  hashMD5(data) {
    if (typeof data !== 'string') return '';
    return crypto.createHash('md5').update(data).digest('hex');
  },

  hashSHA256(data) {
    if (typeof data !== 'string') return '';
    return crypto.createHash('sha256').update(data).digest('hex');
  },

  hashSHA512(data) {
    if (typeof data !== 'string') return '';
    return crypto.createHash('sha512').update(data).digest('hex');
  },

  randomBytes(size = 16) {
    return crypto.randomBytes(size).toString('hex');
  },

  createHMAC(data, key, algorithm = 'sha256') {
    if (typeof data !== 'string' || typeof key !== 'string') return '';
    return crypto.createHmac(algorithm, key).update(data).digest('hex');
  }
};

module.exports = cryptoUtils;
