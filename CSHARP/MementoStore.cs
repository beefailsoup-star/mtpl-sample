using System;
using System.Collections.Generic;

namespace MtplSample
{
    public class Memento
    {
        public string State { get; }
        public DateTime Timestamp { get; }

        public Memento(string state)
        {
            State = state;
            Timestamp = DateTime.UtcNow;
        }
    }

    public class Originator
    {
        public string State { get; set; }

        public Memento Save()
        {
            return new Memento(State);
        }

        public void Restore(Memento memento)
        {
            State = memento.State;
        }
    }

    public class MementoStore
    {
        private readonly Stack<Memento> _history = new();
        private readonly Originator _originator;
        private readonly int _maxHistory;

        public MementoStore(Originator originator, int maxHistory = 10)
        {
            _originator = originator;
            _maxHistory = maxHistory;
        }

        public void Save()
        {
            _history.Push(_originator.Save());
            if (_history.Count > _maxHistory)
            {
                var temp = new Stack<Memento>(_history.ToArray()[^_maxHistory..]);
                _history.Clear();
                foreach (var m in temp)
                    _history.Push(m);
            }
        }

        public bool Undo()
        {
            if (_history.Count == 0)
                return false;

            _originator.Restore(_history.Pop());
            return true;
        }

        public Memento Peek() => _history.Count > 0 ? _history.Peek() : null;

        public int HistoryCount => _history.Count;
    }
}
