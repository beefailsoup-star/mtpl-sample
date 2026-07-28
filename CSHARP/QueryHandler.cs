using System;
using System.Threading.Tasks;

namespace MtplSample
{
    public interface IQuery<TResult> { }

    public interface IQueryHandler<TQuery, TResult> where TQuery : IQuery<TResult>
    {
        Task<TResult> HandleAsync(TQuery query);
    }

    public class QueryDispatcher
    {
        private readonly IServiceProvider _serviceProvider;

        public QueryDispatcher(IServiceProvider serviceProvider)
        {
            _serviceProvider = serviceProvider;
        }

        public async Task<TResult> DispatchAsync<TQuery, TResult>(TQuery query) where TQuery : IQuery<TResult>
        {
            var handler = _serviceProvider.GetService(typeof(IQueryHandler<TQuery, TResult>)) as IQueryHandler<TQuery, TResult>;
            if (handler == null)
                throw new InvalidOperationException($"No handler registered for {typeof(TQuery).Name}");

            return await handler.HandleAsync(query);
        }
    }

    public class GetUserQuery : IQuery<UserEntity>
    {
        public Guid UserId { get; set; }
    }

    public class GetUserQueryHandler : IQueryHandler<GetUserQuery, UserEntity>
    {
        public async Task<UserEntity> HandleAsync(GetUserQuery query)
        {
            await Task.Delay(50);
            return new UserEntity
            {
                Username = "sample_user",
                Email = "user@example.com"
            };
        }
    }
}
