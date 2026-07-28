using System;
using System.Collections.Generic;

namespace MtplSample
{
    public interface IObserver<T>
    {
        void Update(T data);
    }

    public interface IObservable<T>
    {
        void Attach(IObserver<T> observer);
        void Detach(IObserver<T> observer);
        void Notify(T data);
    }

    public class ObserverManager<T> : IObservable<T>
    {
        private readonly List<IObserver<T>> _observers = new();

        public void Attach(IObserver<T> observer)
        {
            if (!_observers.Contains(observer))
                _observers.Add(observer);
        }

        public void Detach(IObserver<T> observer)
        {
            _observers.Remove(observer);
        }

        public void Notify(T data)
        {
            foreach (var observer in _observers)
            {
                observer.Update(data);
            }
        }
    }

    public class ConsoleLogger<T> : IObserver<T>
    {
        public void Update(T data)
        {
            Console.WriteLine($"[Observer] Received: {data}");
        }
    }

    public class StockPriceNotifier : ObserverManager<decimal> { }
}
