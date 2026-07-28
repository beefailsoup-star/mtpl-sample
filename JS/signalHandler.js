function onSignal(signal, handler) {
  process.on(signal, handler);
  return () => {
    process.removeListener(signal, handler);
  };
}

function onExit(handler) {
  process.on('exit', handler);
  return () => {
    process.removeListener('exit', handler);
  };
}

function onUncaughtException(handler) {
  process.on('uncaughtException', handler);
  return () => {
    process.removeListener('uncaughtException', handler);
  };
}

function setupGracefulShutdown(handler, options = {}) {
  const { timeout = 30000, signals = ['SIGINT', 'SIGTERM'] } = options;
  let shuttingDown = false;

  for (const signal of signals) {
    process.on(signal, async () => {
      if (shuttingDown) return;
      shuttingDown = true;
      const timer = setTimeout(() => {
        process.exit(1);
      }, timeout);
      try {
        await handler(signal);
      } catch (err) {
        console.error('Shutdown handler error:', err);
      }
      clearTimeout(timer);
      process.exit(0);
    });
  }
}

function withTimeout(fn, ms, errorMessage = 'Operation timed out') {
  return Promise.race([
    typeof fn === 'function' ? fn() : fn,
    new Promise((_, reject) => setTimeout(() => reject(new Error(errorMessage)), ms))
  ]);
}

module.exports = { onSignal, onExit, onUncaughtException, setupGracefulShutdown, withTimeout };
