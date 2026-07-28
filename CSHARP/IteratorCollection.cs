using System;
using System.Collections;
using System.Collections.Generic;

namespace MtplSample
{
    public class IteratorCollection<T> : IEnumerable<T>
    {
        private readonly T[] _items;
        private int _count;

        public IteratorCollection(int capacity = 10)
        {
            _items = new T[capacity];
            _count = 0;
        }

        public void Add(T item)
        {
            if (_count >= _items.Length)
                throw new InvalidOperationException("Collection is full.");
            _items[_count++] = item;
        }

        public T this[int index]
        {
            get
            {
                if (index < 0 || index >= _count)
                    throw new IndexOutOfRangeException();
                return _items[index];
            }
        }

        public int Count => _count;

        public IEnumerator<T> GetEnumerator()
        {
            for (int i = 0; i < _count; i++)
                yield return _items[i];
        }

        IEnumerator IEnumerable.GetEnumerator() => GetEnumerator();
    }

    public class EvenNumberIterator : IEnumerable<int>
    {
        private readonly int _start;
        private readonly int _end;

        public EvenNumberIterator(int start, int end)
        {
            _start = start;
            _end = end;
        }

        public IEnumerator<int> GetEnumerator()
        {
            for (int i = _start; i <= _end; i++)
            {
                if (i % 2 == 0)
                    yield return i;
            }
        }

        IEnumerator IEnumerable.GetEnumerator() => GetEnumerator();
    }
}
