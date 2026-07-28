'use strict';

const urlBuilder = {
  buildURL(base, path = '', query = {}) {
    const baseClean = base.replace(/\/+$/, '');
    const pathClean = path.replace(/^\/+/, '');
    let url = baseClean;
    if (pathClean) url += '/' + pathClean;
    const queryString = this.toQueryString(query);
    if (queryString) url += '?' + queryString;
    return url;
  },

  parseQueryString(queryStr) {
    if (!queryStr) return {};
    const qs = queryStr.startsWith('?') ? queryStr.slice(1) : queryStr;
    const params = {};
    for (const pair of qs.split('&')) {
      if (!pair) continue;
      const [key, ...valParts] = pair.split('=');
      const decodedKey = decodeURIComponent(key.replace(/\+/g, ' '));
      const decodedVal = valParts.length > 0
        ? decodeURIComponent(valParts.join('=').replace(/\+/g, ' '))
        : '';
      if (Object.prototype.hasOwnProperty.call(params, decodedKey)) {
        if (!Array.isArray(params[decodedKey])) {
          params[decodedKey] = [params[decodedKey]];
        }
        params[decodedKey].push(decodedVal);
      } else {
        params[decodedKey] = decodedVal;
      }
    }
    return params;
  },

  toQueryString(params) {
    if (!params || Object.keys(params).length === 0) return '';
    return Object.entries(params)
      .map(([key, val]) => {
        if (Array.isArray(val)) {
          return val.map(v =>
            encodeURIComponent(key) + '=' + encodeURIComponent(String(v))
          ).join('&');
        }
        return encodeURIComponent(key) + '=' + encodeURIComponent(String(val));
      })
      .join('&');
  },

  normalizeURL(url) {
    if (!url) return '';
    try {
      const parsed = new URL(url);
      parsed.pathname = parsed.pathname.replace(/\/+/g, '/').replace(/\/+$/, '') || '/';
      parsed.search = parsed.search ? '?' + this.toQueryString(this.parseQueryString(parsed.search)) : '';
      return parsed.toString();
    } catch {
      return url;
    }
  }
};

module.exports = urlBuilder;
