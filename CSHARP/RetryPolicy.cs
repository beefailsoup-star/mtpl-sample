using System;
using System.Threading.Tasks;

namespace MtplSample
{
    public class RetryPolicy
    {
        private readonly int _maxRetries;
        private readonly TimeSpan _baseDelay;
        private readonly double _backoffMultiplier;

        public RetryPolicy(int maxRetries = 3, TimeSpan? baseDelay = null, double backoffMultiplier = 2.0)
        {
            _maxRetries = maxRetries;
            _baseDelay = baseDelay ?? TimeSpan.FromMilliseconds(200);
            _backoffMultiplier = backoffMultiplier;
        }

        public async Task<T> ExecuteAsync<T>(Func<Task<T>> action, Func<Exception, bool> shouldRetry = null)
        {
            var delay = _baseDelay;
            Exception lastException = null;

            for (int attempt = 0; attempt <= _maxRetries; attempt++)
            {
                try
                {
                    return await action();
                }
                catch (Exception ex) when (attempt < _maxRetries)
                {
                    lastException = ex;
                    if (shouldRetry != null && !shouldRetry(ex))
                        throw;

                    await Task.Delay(delay);
                    delay = TimeSpan.FromMilliseconds(delay.TotalMilliseconds * _backoffMultiplier);
                }
            }

            throw lastException ?? new InvalidOperationException("Retry policy failed.");
        }

        public async Task ExecuteAsync(Func<Task> action, Func<Exception, bool> shouldRetry = null)
        {
            await ExecuteAsync<object>(async () =>
            {
                await action();
                return null;
            }, shouldRetry);
        }
    }
}
