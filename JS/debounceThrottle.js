'use strict';

const debounceThrottle = {
  debounce(fn, delay = 300) {
    let timer = null;
    return function (...args) {
      clearTimeout(timer);
      timer = setTimeout(() => fn.apply(this, args), delay);
    };
  },

  throttle(fn, interval = 300) {
    let lastTime = 0;
    return function (...args) {
      const now = Date.now();
      if (now - lastTime >= interval) {
        lastTime = now;
        fn.apply(this, args);
      }
    };
  },

  debounceLeading(fn, delay = 300) {
    let timer = null;
    let leadingCalled = false;
    return function (...args) {
      if (!leadingCalled) {
        leadingCalled = true;
        fn.apply(this, args);
      }
      clearTimeout(timer);
      timer = setTimeout(() => {
        leadingCalled = false;
      }, delay);
    };
  },

  throttleTrailing(fn, interval = 300) {
    let lastTime = 0;
    let timer = null;
    return function (...args) {
      const now = Date.now();
      const remaining = interval - (now - lastTime);
      clearTimeout(timer);
      if (remaining <= 0) {
        lastTime = now;
        fn.apply(this, args);
      } else {
        timer = setTimeout(() => {
          lastTime = Date.now();
          fn.apply(this, args);
        }, remaining);
      }
    };
  }
};

module.exports = debounceThrottle;
