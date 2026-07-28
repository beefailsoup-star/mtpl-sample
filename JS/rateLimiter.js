'use strict';

class TokenBucket {
  constructor(capacity, fillRate) {
    this.capacity = capacity;
    this.fillRate = fillRate;
    this.tokens = capacity;
    this.lastRefill = Date.now();
  }

  consume(count = 1) {
    this._refill();
    if (this.tokens >= count) {
      this.tokens -= count;
      return true;
    }
    return false;
  }

  _refill() {
    const now = Date.now();
    const elapsed = (now - this.lastRefill) / 1000;
    this.tokens = Math.min(this.capacity, this.tokens + elapsed * this.fillRate);
    this.lastRefill = now;
  }
}

class RateLimiter {
  constructor(windowMs = 60000, maxRequests = 100) {
    this.windowMs = windowMs;
    this.maxRequests = maxRequests;
    this.requests = new Map();
  }

  isAllowed(key) {
    const now = Date.now();
    const windowStart = now - this.windowMs;

    if (!this.requests.has(key)) {
      this.requests.set(key, []);
    }

    const timestamps = this.requests.get(key).filter(t => t > windowStart);
    timestamps.push(now);
    this.requests.set(key, timestamps);

    return timestamps.length <= this.maxRequests;
  }

  getRemaining(key) {
    const now = Date.now();
    const windowStart = now - this.windowMs;
    const timestamps = this.requests.has(key)
      ? this.requests.get(key).filter(t => t > windowStart)
      : [];
    return Math.max(0, this.maxRequests - timestamps.length);
  }

  reset(key) {
    this.requests.delete(key);
  }
}

module.exports = { TokenBucket, RateLimiter };
