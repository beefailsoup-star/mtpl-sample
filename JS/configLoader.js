'use strict';

const fs = require('fs');
const path = require('path');

class ConfigLoader {
  constructor(options = {}) {
    this.defaults = options.defaults || {};
  }

  load(filePath) {
    const resolvedPath = path.resolve(filePath);
    const ext = path.extname(filePath).toLowerCase();

    if (ext === '.json') {
      return this._loadJSON(resolvedPath);
    }
    if (ext === '.js') {
      return this._loadJS(resolvedPath);
    }
    if (ext === '.env') {
      return this._loadENV(resolvedPath);
    }
    throw new Error(`Unsupported config file type: ${ext}`);
  }

  _loadJSON(filePath) {
    const raw = fs.readFileSync(filePath, 'utf8');
    const parsed = JSON.parse(raw);
    return { ...this.defaults, ...parsed };
  }

  _loadJS(filePath) {
    const mod = require(filePath);
    const config = mod.default || mod;
    return { ...this.defaults, ...config };
  }

  _loadENV(filePath) {
    const raw = fs.readFileSync(filePath, 'utf8');
    const config = {};
    for (const line of raw.split(/\r?\n/)) {
      const trimmed = line.trim();
      if (!trimmed || trimmed.startsWith('#')) continue;
      const eqIdx = trimmed.indexOf('=');
      if (eqIdx === -1) continue;
      const key = trimmed.slice(0, eqIdx).trim();
      let value = trimmed.slice(eqIdx + 1).trim();
      if ((value.startsWith('"') && value.endsWith('"')) ||
          (value.startsWith("'") && value.endsWith("'"))) {
        value = value.slice(1, -1);
      }
      config[key] = value;
    }
    return { ...this.defaults, ...config };
  }
}

module.exports = { ConfigLoader };
