using System;
using System.Collections;
using System.Collections.Generic;

namespace MtplSample
{
    public class LinkedListCustom<T> : IEnumerable<T>
    {
        private ListNode<T> _head;
        private ListNode<T> _tail;
        private int _count;

        public int Count => _count;
        public bool IsEmpty => _count == 0;

        public void AddFirst(T value)
        {
            var node = new ListNode<T>(value) { Next = _head };
            _head = node;
            if (_tail == null) _tail = node;
            _count++;
        }

        public void AddLast(T value)
        {
            var node = new ListNode<T>(value);
            if (_tail == null)
            {
                _head = _tail = node;
            }
            else
            {
                _tail.Next = node;
                _tail = node;
            }
            _count++;
        }

        public bool Remove(T value)
        {
            ListNode<T> prev = null;
            var current = _head;

            while (current != null)
            {
                if (EqualityComparer<T>.Default.Equals(current.Value, value))
                {
                    if (prev == null)
                    {
                        _head = current.Next;
                        if (_head == null) _tail = null;
                    }
                    else
                    {
                        prev.Next = current.Next;
                        if (current.Next == null) _tail = prev;
                    }
                    _count--;
                    return true;
                }
                prev = current;
                current = current.Next;
            }
            return false;
        }

        public bool Contains(T value)
        {
            var current = _head;
            while (current != null)
            {
                if (EqualityComparer<T>.Default.Equals(current.Value, value))
                    return true;
                current = current.Next;
            }
            return false;
        }

        public void Clear()
        {
            _head = _tail = null;
            _count = 0;
        }

        public IEnumerator<T> GetEnumerator()
        {
            var current = _head;
            while (current != null)
            {
                yield return current.Value;
                current = current.Next;
            }
        }

        IEnumerator IEnumerable.GetEnumerator() => GetEnumerator();
    }

    public class ListNode<T>
    {
        public T Value { get; }
        public ListNode<T> Next { get; set; }

        public ListNode(T value)
        {
            Value = value;
        }
    }
}
