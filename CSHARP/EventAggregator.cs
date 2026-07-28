using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace MtplSample
{
    public class EventAggregator
    {
        private readonly ConcurrentDictionary<Type, List<WeakReference>> _subscribers = new();

        public void Subscribe<TEvent>(IEventHandler<TEvent> handler) where TEvent : IEvent
        {
            var eventType = typeof(TEvent);
            var handlers = _subscribers.GetOrAdd(eventType, _ => new List<WeakReference>());
            lock (handlers)
            {
                handlers.Add(new WeakReference(handler));
            }
        }

        public void Unsubscribe<TEvent>(IEventHandler<TEvent> handler) where TEvent : IEvent
        {
            var eventType = typeof(TEvent);
            if (_subscribers.TryGetValue(eventType, out var handlers))
            {
                lock (handlers)
                {
                    handlers.RemoveAll(wr => wr.Target == handler || !wr.IsAlive);
                }
            }
        }

        public async Task PublishAsync<TEvent>(TEvent @event) where TEvent : IEvent
        {
            var eventType = typeof(TEvent);
            if (!_subscribers.TryGetValue(eventType, out var handlers))
                return;

            List<IEventHandler<TEvent>> active;
            lock (handlers)
            {
                active = handlers
                    .Select(wr => wr.Target)
                    .OfType<IEventHandler<TEvent>>()
                    .ToList();
            }

            foreach (var handler in active)
            {
                await handler.HandleAsync(@event);
            }
        }
    }

    public interface IEvent { }

    public interface IEventHandler<TEvent> where TEvent : IEvent
    {
        Task HandleAsync(TEvent @event);
    }
}
