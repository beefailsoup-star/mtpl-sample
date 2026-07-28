using System;
using System.Collections.Generic;
using System.Threading.Tasks;

namespace MtplSample
{
    public class MiddlewarePipeline
    {
        private readonly List<Func<Func<Task>, Func<Task>>> _middlewares = new();

        public void Use(Func<Func<Task>, Func<Task>> middleware)
        {
            _middlewares.Add(middleware);
        }

        public Func<Task> Build(Func<Task> finalHandler)
        {
            Func<Task> pipeline = finalHandler;
            for (int i = _middlewares.Count - 1; i >= 0; i--)
            {
                var current = pipeline;
                var middleware = _middlewares[i];
                pipeline = () => middleware(current);
            }
            return pipeline;
        }

        public async Task ExecuteAsync(Func<Task> finalHandler)
        {
            var pipeline = Build(finalHandler);
            await pipeline();
        }
    }

    public class MiddlewareContext
    {
        public Dictionary<string, object> Items { get; } = new();
        public bool IsCancelled { get; set; }
    }
}
