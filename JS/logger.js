'use strict';

const levels = { error: 0, warn: 1, info: 2, debug: 3 };

class Logger {
  constructor(name = 'app', level = 'debug') {
    this.name = name;
    this.level = levels[level] !== undefined ? level : 'debug';
  }

  _log(level, message, meta = {}) {
    if (levels[level] > levels[this.level]) return;
    const entry = {
      timestamp: new Date().toISOString(),
      name: this.name,
      level,
      message,
      ...meta
    };
    const output = JSON.stringify(entry);
    if (level === 'error') {
      process.stderr.write(output + '\n');
    } else {
      process.stdout.write(output + '\n');
    }
  }

  error(message, meta) { this._log('error', message, meta); }
  warn(message, meta) { this._log('warn', message, meta); }
  info(message, meta) { this._log('info', message, meta); }
  debug(message, meta) { this._log('debug', message, meta); }
}

module.exports = { Logger };
