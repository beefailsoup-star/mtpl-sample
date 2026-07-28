'use strict';

const pipeCompose = {
  pipe(...fns) {
    return function (initial) {
      return fns.reduce((acc, fn) => fn(acc), initial);
    };
  },

  compose(...fns) {
    return function (initial) {
      return fns.reduceRight((acc, fn) => fn(acc), initial);
    };
  },

  curry(fn, arity) {
    arity = arity || fn.length;
    return function curried(...args) {
      if (args.length >= arity) {
        return fn(...args);
      }
      return (...more) => curried(...args, ...more);
    };
  },

  partial(fn, ...presetArgs) {
    return function (...laterArgs) {
      return fn(...presetArgs, ...laterArgs);
    };
  },

  once(fn) {
    let called = false;
    let result;
    return function (...args) {
      if (!called) {
        called = true;
        result = fn.apply(this, args);
      }
      return result;
    };
  },

  tap(fn) {
    return function (value) {
      fn(value);
      return value;
    };
  }
};

module.exports = pipeCompose;
