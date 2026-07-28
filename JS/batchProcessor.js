class BatchProcessor {
  constructor(batchSize = 10, concurrency = 1) {
    this.batchSize = batchSize;
    this.concurrency = concurrency;
  }

  async process(items, fn) {
    const results = [];
    for (let i = 0; i < items.length; i += this.batchSize) {
      const batch = items.slice(i, i + this.batchSize);
      const batchResults = await Promise.all(
        batch.map(item => fn(item))
      );
      results.push(...batchResults);
    }
    return results;
  }

  async processWithProgress(items, fn, onProgress) {
    const total = items.length;
    const results = [];
    let completed = 0;

    for (let i = 0; i < total; i += this.batchSize) {
      const batch = items.slice(i, i + this.batchSize);
      const batchResults = await Promise.all(
        batch.map(async (item) => {
          const result = await fn(item);
          completed++;
          if (typeof onProgress === 'function') {
            onProgress({ completed, total, percent: Math.round((completed / total) * 100) });
          }
          return result;
        })
      );
      results.push(...batchResults);
    }
    return results;
  }
}

module.exports = { BatchProcessor };
