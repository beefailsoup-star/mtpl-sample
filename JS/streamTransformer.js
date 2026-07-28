const { Transform } = require('stream');

class UpperCaseTransform extends Transform {
  _transform(chunk, encoding, callback) {
    callback(null, chunk.toString().toUpperCase());
  }
}

class LineSplitTransform extends Transform {
  constructor() {
    super({ readableObjectMode: true });
    this.buffer = '';
  }

  _transform(chunk, encoding, callback) {
    this.buffer += chunk.toString();
    const lines = this.buffer.split('\n');
    this.buffer = lines.pop();
    for (const line of lines) {
      this.push(line);
    }
    callback();
  }

  _flush(callback) {
    if (this.buffer.length > 0) {
      this.push(this.buffer);
    }
    callback();
  }
}

class BatchTransform extends Transform {
  constructor(batchSize = 10) {
    super({ readableObjectMode: true, writableObjectMode: true });
    this.batchSize = batchSize;
    this.batch = [];
  }

  _transform(chunk, encoding, callback) {
    this.batch.push(chunk);
    if (this.batch.length >= this.batchSize) {
      const batch = this.batch;
      this.batch = [];
      this.push(batch);
    }
    callback();
  }

  _flush(callback) {
    if (this.batch.length > 0) {
      this.push(this.batch);
    }
    callback();
  }
}

module.exports = { UpperCaseTransform, LineSplitTransform, BatchTransform };
