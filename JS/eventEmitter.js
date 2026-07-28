'use strict';

class EventEmitter {
  constructor() {
    this._events = {};
  }

  on(event, listener) {
    if (!this._events[event]) {
      this._events[event] = [];
    }
    this._events[event].push(listener);
    return this;
  }

  off(event, listener) {
    if (!this._events[event]) return this;
    if (!listener) {
      delete this._events[event];
      return this;
    }
    this._events[event] = this._events[event].filter(l => l !== listener);
    return this;
  }

  emit(event, ...args) {
    if (!this._events[event]) return false;
    for (const listener of this._events[event]) {
      listener(...args);
    }
    return true;
  }

  once(event, listener) {
    const wrapper = (...args) => {
      listener(...args);
      this.off(event, wrapper);
    };
    return this.on(event, wrapper);
  }
}

module.exports = { EventEmitter };
