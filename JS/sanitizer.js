'use strict';

const sanitizer = {
  escapeHTML(str) {
    if (typeof str !== 'string') return '';
    const map = {
      '&': '&amp;',
      '<': '&lt;',
      '>': '&gt;',
      '"': '&quot;',
      "'": '&#39;'
    };
    return str.replace(/[&<>"']/g, ch => map[ch]);
  },

  unescapeHTML(str) {
    if (typeof str !== 'string') return '';
    const map = {
      '&amp;': '&',
      '&lt;': '<',
      '&gt;': '>',
      '&quot;': '"',
      '&#39;': "'",
      '&#x27;': "'",
      '&#x2F;': '/'
    };
    return str.replace(/&(?:amp|lt|gt|quot|#39|#x27|#x2F);/g, match => map[match] || match);
  },

  stripTags(str) {
    if (typeof str !== 'string') return '';
    return str.replace(/<[^>]*>/g, '');
  },

  trimAll(str) {
    if (typeof str !== 'string') return '';
    return str.replace(/\s+/g, ' ').trim();
  },

  sanitizeFilename(str) {
    if (typeof str !== 'string') return '';
    return str
      .replace(/[<>:"/\\|?*\x00-\x1f]/g, '_')
      .replace(/^\./, '_')
      .replace(/^_+|_+$/g, '')
      .substring(0, 255);
  }
};

module.exports = sanitizer;
