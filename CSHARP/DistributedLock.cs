using System;
using System.Collections.Concurrent;
using System.Threading;
using System.Threading.Tasks;

namespace MtplSample
{
    public class DistributedLock
    {
        private readonly ConcurrentDictionary<string, SemaphoreSlim> _locks = new();

        public async Task<IDisposable> AcquireAsync(string resourceId, TimeSpan? timeout = null)
        {
            var semaphore = _locks.GetOrAdd(resourceId, _ => new SemaphoreSlim(1, 1));
            var acquired = await semaphore.WaitAsync(timeout ?? TimeSpan.FromSeconds(30));

            if (!acquired)
                throw new TimeoutException($"Could not acquire lock for resource '{resourceId}' within the timeout period.");

            return new LockReleaser(semaphore, resourceId, _locks);
        }

        private class LockReleaser : IDisposable
        {
            private readonly SemaphoreSlim _semaphore;
            private readonly string _resourceId;
            private readonly ConcurrentDictionary<string, SemaphoreSlim> _lockStore;
            private bool _disposed;

            public LockReleaser(SemaphoreSlim semaphore, string resourceId, ConcurrentDictionary<string, SemaphoreSlim> lockStore)
            {
                _semaphore = semaphore;
                _resourceId = resourceId;
                _lockStore = lockStore;
            }

            public void Dispose()
            {
                if (_disposed) return;
                _disposed = true;
                _semaphore.Release();
            }
        }
    }
}
