'use strict';

class PromiseQueue {
  constructor(concurrency = 1) {
    this.concurrency = Math.max(1, concurrency);
    this._queue = [];
    this._active = 0;
    this._paused = false;
  }

  add(fn) {
    return new Promise((resolve, reject) => {
      this._queue.push({ fn, resolve, reject });
      this._process();
    });
  }

  _process() {
    if (this._paused) return;
    while (this._active < this.concurrency && this._queue.length > 0) {
      const { fn, resolve, reject } = this._queue.shift();
      this._active++;
      Promise.resolve().then(() => fn())
        .then(result => {
          this._active--;
          resolve(result);
          this._process();
        })
        .catch(err => {
          this._active--;
          reject(err);
          this._process();
        });
    }
  }

  pause() {
    this._paused = true;
  }

  resume() {
    this._paused = false;
    this._process();
  }

  size() {
    return this._queue.length;
  }

  pending() {
    return this._active;
  }
}

module.exports = { PromiseQueue };
