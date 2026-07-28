using System;
using System.Collections.Concurrent;
using System.Threading;
using System.Threading.Tasks;

namespace MtplSample
{
    public class CacheProvider
    {
        private readonly ConcurrentDictionary<string, CacheEntry> _cache = new();
        private readonly TimeSpan _defaultTtl;
        private readonly Timer _cleanupTimer;

        public CacheProvider(TimeSpan? defaultTtl = null, int cleanupIntervalSeconds = 60)
        {
            _defaultTtl = defaultTtl ?? TimeSpan.FromMinutes(5);
            _cleanupTimer = new Timer(_ => Cleanup(), null, TimeSpan.FromSeconds(cleanupIntervalSeconds), TimeSpan.FromSeconds(cleanupIntervalSeconds));
        }

        public void Set<T>(string key, T value, TimeSpan? ttl = null)
        {
            var entry = new CacheEntry
            {
                Value = value,
                ExpiresAt = DateTime.UtcNow.Add(ttl ?? _defaultTtl)
            };
            _cache[key] = entry;
        }

        public bool TryGet<T>(string key, out T value)
        {
            if (_cache.TryGetValue(key, out var entry) && entry.ExpiresAt > DateTime.UtcNow)
            {
                value = (T)entry.Value;
                return true;
            }
            _cache.TryRemove(key, out _);
            value = default;
            return false;
        }

        public T GetOrAdd<T>(string key, Func<T> factory, TimeSpan? ttl = null)
        {
            if (TryGet<T>(key, out var existing))
                return existing;

            var value = factory();
            Set(key, value, ttl);
            return value;
        }

        public async Task<T> GetOrAddAsync<T>(string key, Func<Task<T>> factory, TimeSpan? ttl = null)
        {
            if (TryGet<T>(key, out var existing))
                return existing;

            var value = await factory();
            Set(key, value, ttl);
            return value;
        }

        public void Remove(string key)
        {
            _cache.TryRemove(key, out _);
        }

        public void Clear()
        {
            _cache.Clear();
        }

        private void Cleanup()
        {
            var now = DateTime.UtcNow;
            foreach (var kvp in _cache)
            {
                if (kvp.Value.ExpiresAt <= now)
                    _cache.TryRemove(kvp.Key, out _);
            }
        }

        private class CacheEntry
        {
            public object Value { get; set; }
            public DateTime ExpiresAt { get; set; }
        }
    }
}
