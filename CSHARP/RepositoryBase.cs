using System;
using System.Collections.Generic;
using System.Linq.Expressions;
using System.Threading.Tasks;

namespace MtplSample
{
    public interface IRepositoryBase<T> where T : class
    {
        Task<T> GetByIdAsync(Guid id);
        Task<IEnumerable<T>> GetAllAsync();
        Task<IEnumerable<T>> FindAsync(Expression<Func<T, bool>> predicate);
        Task AddAsync(T entity);
        Task UpdateAsync(T entity);
        Task DeleteAsync(Guid id);
    }

    public class RepositoryBase<T> : IRepositoryBase<T> where T : class
    {
        private readonly Dictionary<Guid, T> _store = new();
        private readonly Func<T, Guid> _idSelector;

        protected RepositoryBase(Func<T, Guid> idSelector)
        {
            _idSelector = idSelector ?? throw new ArgumentNullException(nameof(idSelector));
        }

        public Task<T> GetByIdAsync(Guid id)
        {
            _store.TryGetValue(id, out var entity);
            return Task.FromResult(entity);
        }

        public Task<IEnumerable<T>> GetAllAsync()
        {
            return Task.FromResult(_store.Values as IEnumerable<T>);
        }

        public Task<IEnumerable<T>> FindAsync(Expression<Func<T, bool>> predicate)
        {
            var compiled = predicate.Compile();
            var results = new List<T>();
            foreach (var entity in _store.Values)
            {
                if (compiled(entity))
                    results.Add(entity);
            }
            return Task.FromResult(results as IEnumerable<T>);
        }

        public Task AddAsync(T entity)
        {
            if (entity == null) throw new ArgumentNullException(nameof(entity));
            var id = _idSelector(entity);
            _store[id] = entity;
            return Task.CompletedTask;
        }

        public Task UpdateAsync(T entity)
        {
            if (entity == null) throw new ArgumentNullException(nameof(entity));
            var id = _idSelector(entity);
            if (!_store.ContainsKey(id))
                throw new KeyNotFoundException($"Entity with id {id} not found.");
            _store[id] = entity;
            return Task.CompletedTask;
        }

        public Task DeleteAsync(Guid id)
        {
            _store.Remove(id);
            return Task.CompletedTask;
        }
    }
}
