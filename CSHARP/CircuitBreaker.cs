using System;
using System.Threading;
using System.Threading.Tasks;

namespace MtplSample
{
    public class CircuitBreaker
    {
        private readonly int _failureThreshold;
        private readonly TimeSpan _resetTimeout;
        private int _failureCount;
        private CircuitState _state = CircuitState.Closed;
        private DateTime _lastFailureTime;
        private readonly object _lock = new();

        public CircuitBreaker(int failureThreshold = 5, TimeSpan? resetTimeout = null)
        {
            _failureThreshold = failureThreshold;
            _resetTimeout = resetTimeout ?? TimeSpan.FromSeconds(30);
        }

        public CircuitState State
        {
            get
            {
                if (_state == CircuitState.Open && DateTime.UtcNow - _lastFailureTime >= _resetTimeout)
                {
                    lock (_lock)
                    {
                        if (_state == CircuitState.Open && DateTime.UtcNow - _lastFailureTime >= _resetTimeout)
                        {
                            _state = CircuitState.HalfOpen;
                        }
                    }
                }
                return _state;
            }
        }

        public async Task<T> ExecuteAsync<T>(Func<Task<T>> action)
        {
            var currentState = State;
            if (currentState == CircuitState.Open)
                throw new CircuitBreakerOpenException("Circuit breaker is open. Request blocked.");

            try
            {
                var result = await action();
                if (currentState == CircuitState.HalfOpen)
                {
                    lock (_lock)
                    {
                        _state = CircuitState.Closed;
                        _failureCount = 0;
                    }
                }
                return result;
            }
            catch
            {
                lock (_lock)
                {
                    _failureCount++;
                    _lastFailureTime = DateTime.UtcNow;
                    if (_failureCount >= _failureThreshold)
                        _state = CircuitState.Open;
                }
                throw;
            }
        }

        public void Reset()
        {
            lock (_lock)
            {
                _state = CircuitState.Closed;
                _failureCount = 0;
            }
        }
    }

    public enum CircuitState { Closed, Open, HalfOpen }

    public class CircuitBreakerOpenException : Exception
    {
        public CircuitBreakerOpenException(string message) : base(message) { }
    }
}
