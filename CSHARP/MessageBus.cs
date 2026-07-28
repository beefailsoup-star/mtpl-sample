using System;
using System.Collections.Concurrent;
using System.Threading;
using System.Threading.Channels;
using System.Threading.Tasks;

namespace MtplSample
{
    public class MessageBus
    {
        private readonly ConcurrentDictionary<string, object> _channels = new();

        public ChannelWriter<T> CreateWriter<T>(string topic = null, int capacity = 100)
        {
            topic ??= typeof(T).FullName;
            var channel = _channels.GetOrAdd(topic, _ => Channel.CreateBounded<T>(new BoundedChannelOptions(capacity)
            {
                FullMode = BoundedChannelFullMode.DropOldest
            }));
            return ((Channel<T>)channel).Writer;
        }

        public ChannelReader<T> CreateReader<T>(string topic = null)
        {
            topic ??= typeof(T).FullName;
            var channel = _channels.GetOrAdd(topic, _ => Channel.CreateBounded<T>(new BoundedChannelOptions(100)
            {
                FullMode = BoundedChannelFullMode.DropOldest
            }));
            return ((Channel<T>)channel).Reader;
        }

        public async Task PublishAsync<T>(T message, string topic = null, CancellationToken ct = default)
        {
            var writer = CreateWriter<T>(topic);
            await writer.WriteAsync(message, ct);
        }

        public async Task SubscribeAsync<T>(Func<T, Task> handler, string topic = null, CancellationToken ct = default)
        {
            var reader = CreateReader<T>(topic);
            await foreach (var message in reader.ReadAllAsync(ct))
            {
                await handler(message);
            }
        }
    }
}
