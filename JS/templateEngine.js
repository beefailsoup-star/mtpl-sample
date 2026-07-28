'use strict';

const templateEngine = {
  render(template, data) {
    if (typeof template !== 'string') return '';
    return template.replace(/\{\{(\w+)\}\}/g, (match, key) => {
      if (Object.prototype.hasOwnProperty.call(data, key)) {
        return String(data[key]);
      }
      return match;
    });
  },

  compile(template) {
    const keys = [];
    const pattern = /\{\{(\w+)\}\}/g;
    let lastIndex = 0;
    let match;
    const parts = [];

    while ((match = pattern.exec(template)) !== null) {
      if (match.index > lastIndex) {
        parts.push(template.slice(lastIndex, match.index));
      }
      const key = match[1];
      keys.push(key);
      parts.push(key);
      lastIndex = pattern.lastIndex;
    }
    if (lastIndex < template.length) {
      parts.push(template.slice(lastIndex));
    }

    return function (data) {
      let result = '';
      for (const part of parts) {
        if (keys.includes(part)) {
          result += data[part] !== undefined ? String(data[part]) : '{{' + part + '}}';
        } else {
          result += part;
        }
      }
      return result;
    };
  }
};

module.exports = templateEngine;
