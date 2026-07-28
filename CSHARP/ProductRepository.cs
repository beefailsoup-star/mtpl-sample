using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace MtplSample
{
    public class ProductRepository
    {
        private readonly Dictionary<Guid, Product> _store = new();

        public Task<Product> GetByIdAsync(Guid id)
        {
            _store.TryGetValue(id, out var product);
            return Task.FromResult(product);
        }

        public Task<IEnumerable<Product>> GetAllAsync()
        {
            return Task.FromResult(_store.Values.AsEnumerable());
        }

        public Task AddAsync(Product product)
        {
            if (product == null) throw new ArgumentNullException(nameof(product));
            _store[product.Id] = product;
            return Task.CompletedTask;
        }

        public Task UpdateAsync(Product product)
        {
            if (product == null) throw new ArgumentNullException(nameof(product));
            if (!_store.ContainsKey(product.Id))
                throw new KeyNotFoundException("Product not found.");
            _store[product.Id] = product;
            return Task.CompletedTask;
        }

        public Task DeleteAsync(Guid id)
        {
            _store.Remove(id);
            return Task.CompletedTask;
        }
    }

    public class Product
    {
        public Guid Id { get; set; } = Guid.NewGuid();
        public string Name { get; set; }
        public decimal Price { get; set; }
        public int Stock { get; set; }
    }
}
