using System;
using System.Threading;
using System.Threading.Tasks;

namespace MtplSample
{
    public class BulkheadIsolation
    {
        private readonly SemaphoreSlim _semaphore;

        public BulkheadIsolation(int maxConcurrent)
        {
            if (maxConcurrent <= 0)
                throw new ArgumentOutOfRangeException(nameof(maxConcurrent), "Must be greater than zero.");
            _semaphore = new SemaphoreSlim(maxConcurrent, maxConcurrent);
        }

        public int AvailableSlots => _semaphore.CurrentCount;

        public async Task<T> ExecuteAsync<T>(Func<Task<T>> action, TimeSpan? timeout = null)
        {
            var acquired = await _semaphore.WaitAsync(timeout ?? TimeSpan.FromSeconds(30));
            if (!acquired)
                throw new BulkheadFullException("Bulkhead is full. No available slots.");

            try
            {
                return await action();
            }
            finally
            {
                _semaphore.Release();
            }
        }

        public async Task ExecuteAsync(Func<Task> action, TimeSpan? timeout = null)
        {
            await ExecuteAsync<object>(async () =>
            {
                await action();
                return null;
            }, timeout);
        }
    }

    public class BulkheadFullException : Exception
    {
        public BulkheadFullException(string message) : base(message) { }
    }
}
