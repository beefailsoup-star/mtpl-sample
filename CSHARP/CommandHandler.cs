using System;
using System.Threading.Tasks;

namespace MtplSample
{
    public interface ICommand { }

    public interface ICommandHandler<TCommand> where TCommand : ICommand
    {
        Task HandleAsync(TCommand command);
    }

    public class CommandDispatcher
    {
        private readonly IServiceProvider _serviceProvider;

        public CommandDispatcher(IServiceProvider serviceProvider)
        {
            _serviceProvider = serviceProvider;
        }

        public async Task DispatchAsync<TCommand>(TCommand command) where TCommand : ICommand
        {
            var handler = _serviceProvider.GetService(typeof(ICommandHandler<TCommand>)) as ICommandHandler<TCommand>;
            if (handler == null)
                throw new InvalidOperationException($"No handler registered for {typeof(TCommand).Name}");

            await handler.HandleAsync(command);
        }
    }

    public class CreateUserCommand : ICommand
    {
        public string Username { get; set; }
        public string Email { get; set; }
        public string Password { get; set; }
    }

    public class CreateUserCommandHandler : ICommandHandler<CreateUserCommand>
    {
        public async Task HandleAsync(CreateUserCommand command)
        {
            await Task.Delay(50);
            LoggerService.Instance.LogInfo($"User created: {command.Username}");
        }
    }
}
