using System;
using System.Collections.Generic;
using System.Threading.Tasks;

namespace MtplSample
{
    public interface IUnitOfWork : IDisposable
    {
        Task BeginTransactionAsync();
        Task CommitAsync();
        Task RollbackAsync();
    }

    public class UnitOfWork : IUnitOfWork
    {
        private readonly Stack<Func<Task>> _actions = new();
        private bool _disposed;

        public Task BeginTransactionAsync()
        {
            _actions.Clear();
            return Task.CompletedTask;
        }

        public void RegisterAction(Func<Task> action)
        {
            _actions.Push(action);
        }

        public async Task CommitAsync()
        {
            foreach (var action in _actions)
            {
                await action();
            }
            _actions.Clear();
        }

        public Task RollbackAsync()
        {
            _actions.Clear();
            return Task.CompletedTask;
        }

        public void Dispose()
        {
            if (_disposed) return;
            _disposed = true;
            _actions.Clear();
        }
    }

    public class UnitOfWorkFactory
    {
        private readonly Dictionary<string, IUnitOfWork> _contexts = new();

        public IUnitOfWork Create(string name = "default")
        {
            if (!_contexts.ContainsKey(name))
                _contexts[name] = new UnitOfWork();
            return _contexts[name];
        }
    }
}
