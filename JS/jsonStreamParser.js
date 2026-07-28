const { Transform } = require('stream');

class JSONStreamParser extends Transform {
  constructor(options = {}) {
    super({ readableObjectMode: true, ...options });
    this.buffer = '';
    this.depth = 0;
    this.inString = false;
    this.escapeNext = false;
  }

  _transform(chunk, encoding, callback) {
    this.buffer += chunk.toString();
    const objects = [];
    let start = -1;

    for (let i = 0; i < this.buffer.length; i++) {
      const ch = this.buffer[i];

      if (this.escapeNext) {
        this.escapeNext = false;
        continue;
      }

      if (this.inString) {
        if (ch === '\\') {
          this.escapeNext = true;
        } else if (ch === '"') {
          this.inString = false;
        }
        continue;
      }

      if (ch === '"') {
        this.inString = true;
        continue;
      }

      if (ch === '{' || ch === '[') {
        if (this.depth === 0) start = i;
        this.depth++;
      } else if (ch === '}' || ch === ']') {
        this.depth--;
        if (this.depth === 0 && start >= 0) {
          try {
            const obj = JSON.parse(this.buffer.slice(start, i + 1));
            objects.push(obj);
          } catch (e) {
            // ignore partial parse errors
          }
          start = -1;
        }
      }
    }

    if (start >= 0) {
      this.buffer = this.buffer.slice(start);
    } else {
      this.buffer = '';
    }

    for (const obj of objects) {
      this.push(obj);
    }
    callback();
  }

  _flush(callback) {
    if (this.buffer.trim().length > 0) {
      try {
        const obj = JSON.parse(this.buffer);
        this.push(obj);
      } catch (e) {
        // ignore remaining incomplete data
      }
    }
    this.buffer = '';
    callback();
  }
}

module.exports = { JSONStreamParser };
