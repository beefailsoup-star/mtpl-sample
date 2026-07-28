using System;
using System.Collections.Generic;
using System.Linq;

namespace MtplSample
{
    public class DataProcessor<TInput, TOutput>
    {
        private readonly List<Func<TInput, TInput>> _transformers = new();
        private Func<TInput, TOutput> _finalMapper;

        public DataProcessor(Func<TInput, TOutput> mapper)
        {
            _finalMapper = mapper;
        }

        public DataProcessor<TInput, TOutput> AddTransformer(Func<TInput, TInput> transformer)
        {
            _transformers.Add(transformer);
            return this;
        }

        public TOutput Process(TInput input)
        {
            var current = input;
            foreach (var transformer in _transformers)
            {
                current = transformer(current);
            }
            return _finalMapper(current);
        }

        public IEnumerable<TOutput> ProcessBatch(IEnumerable<TInput> inputs)
        {
            return inputs.Select(Process);
        }
    }
}
