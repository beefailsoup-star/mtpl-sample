using System;
using System.Collections.Concurrent;
using System.Threading;
using System.Threading.Tasks;

namespace MtplSample
{
    public class RateLimiter
    {
        private readonly int _maxRequests;
        private readonly TimeSpan _window;
        private readonly ConcurrentDictionary<string, RateLimitEntry> _entries = new();

        public RateLimiter(int maxRequests, TimeSpan window)
        {
            _maxRequests = maxRequests;
            _window = window;
        }

        public bool IsAllowed(string key)
        {
            var now = DateTime.UtcNow;
            var entry = _entries.GetOrAdd(key, _ => new RateLimitEntry { WindowStart = now, Count = 0 });

            lock (entry)
            {
                if (now - entry.WindowStart >= _window)
                {
                    entry.WindowStart = now;
                    entry.Count = 0;
                }

                if (entry.Count >= _maxRequests)
                    return false;

                entry.Count++;
                return true;
            }
        }

        public async Task<bool> WaitAsync(string key, TimeSpan? timeout = null)
        {
            var deadline = DateTime.UtcNow + (timeout ?? TimeSpan.FromSeconds(30));

            while (DateTime.UtcNow < deadline)
            {
                if (IsAllowed(key))
                    return true;
                await Task.Delay(100);
            }

            return false;
        }

        private class RateLimitEntry
        {
            public DateTime WindowStart { get; set; }
            public int Count { get; set; }
        }
    }
}
