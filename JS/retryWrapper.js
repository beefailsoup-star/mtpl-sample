function sleep(ms) {
  return new Promise(resolve => setTimeout(resolve, ms));
}

async function retry(fn, options = {}) {
  const { maxRetries = 3, baseDelay = 1000, maxDelay = 30000, onRetry = null } = options;
  let lastError;
  for (let attempt = 0; attempt <= maxRetries; attempt++) {
    try {
      return await fn(attempt);
    } catch (err) {
      lastError = err;
      if (attempt === maxRetries) break;
      const delay = Math.min(baseDelay * Math.pow(2, attempt), maxDelay);
      if (typeof onRetry === 'function') {
        onRetry({ attempt, error: err, delay });
      }
      await sleep(delay);
    }
  }
  throw lastError;
}

function retrySync(fn, options = {}) {
  const { maxRetries = 3, baseDelay = 1000, maxDelay = 30000, onRetry = null } = options;
  let lastError;
  for (let attempt = 0; attempt <= maxRetries; attempt++) {
    try {
      return fn(attempt);
    } catch (err) {
      lastError = err;
      if (attempt === maxRetries) break;
      const delay = Math.min(baseDelay * Math.pow(2, attempt), maxDelay);
      if (typeof onRetry === 'function') {
        onRetry({ attempt, error: err, delay });
      }
      const start = Date.now();
      while (Date.now() - start < delay);
    }
  }
  throw lastError;
}

module.exports = { retry, retrySync };
